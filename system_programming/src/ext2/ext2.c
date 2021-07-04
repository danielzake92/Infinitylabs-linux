/*****************************************************************************
* FILE:      ext2.c	       			   PURPOSE: ext2 file system
* DEVELOPER: Daniel Zaken              TEAM:    RD100
*
* REVIEWER:  Itamar Aron              STATUS: Impl
******************************************************************************/
#include "ext2_util.h" /*holds al the structs needed */
#include "ext2.h" /*user api*/
/*****************************************************************************/
/*****************************************************************************/
static ext2_status_t InitSuperBlock(data_t *data, int fd);
static ext2_status_t InitGroupDescriptor(data_t *data, int fd);
static ext2_status_t InitData(data_t *data, int fd);
static ext2_status_t ReadBlock(data_t *data, int fd ,size_t block_num);
static ext2_status_t ReadInode(data_t *data, ext2_inode_t *inode, int fd ,size_t inode_num);
ext2_status_t CopyFileContentToBuff(data_t *data, int fd);

char *GetSubPath(char *remain_path, char *buff);
static const char *NStrStr(const char *haystack, const char *needle, size_t n);
/*****************************************************************************/
/*****************************************************************************/
static ext2_status_t InitSuperBlock(data_t *data, int fd)
{
	data->block_size = 1;
	if(0 > lseek(fd, sizeof(ext2_super_block_t), SEEK_SET))
	{
		return EXT2_SEEK_ERROR;
	}
	if(0 > read(fd, &(data->super_block),sizeof(ext2_super_block_t) ))
	{
		return EXT2_READ_ERROR;
	}

	data->block_size <<= (data->super_block.s_log_block_size + 10); /* 4096*/
	data->inode_size = data->super_block.s_inode_size;

	return EXT2_SUCCESS;
}
/*****************************************************************************/
static ext2_status_t InitGroupDescriptor(data_t *data, int fd)
{
	if(0 > lseek(fd, data->block_size, SEEK_SET))
	{
		return EXT2_SEEK_ERROR;
	}
	if(0 > read(fd, &(data->descriptors),sizeof(ext2_group_des_t) ))
	{
		return EXT2_READ_ERROR;
	}
	return EXT2_SUCCESS;
}
/*****************************************************************************/
static ext2_status_t ReadBlock(data_t *data, int fd ,size_t block_num)
{
	if(0 > lseek(fd, (data->block_size)*(data->root_inode.i_block)[block_num], SEEK_SET) )
	{
		return EXT2_SEEK_ERROR;
	}
	if(0 > read(fd, data->block_buff,data->block_size))
	{
		return EXT2_READ_ERROR;
	}
	return EXT2_SUCCESS;
}
/*****************************************************************************/
static ext2_status_t ReadInode(data_t *data, ext2_inode_t *inode, int fd ,size_t inode_num)
{
	if(0 > lseek(fd, (data->block_size)*(data->descriptors.addr_inode_table) +
		  (inode_num - 1)*(data->inode_size), SEEK_SET))
	{
		return EXT2_SEEK_ERROR;
	}		  
	if(0 > read(fd, inode,sizeof(ext2_inode_t)))
	{
		return EXT2_READ_ERROR;
	}
	return EXT2_SUCCESS;
}
/*****************************************************************************/
static ext2_status_t InitData(data_t *data, int fd)
{
	ext2_status_t status = EXT2_SUCCESS;
	status = InitSuperBlock(data, fd);
	if(EXT2_SUCCESS != status)
	{
		return status;
	}
	status = InitGroupDescriptor(data, fd);
	if(EXT2_SUCCESS != status)
	{
		return status;
	}
	return EXT2_SUCCESS;
}	
/*****************************************************************************/
static const char *NStrStr(const char *haystack, const char *needle, size_t n)
{
	size_t needle_size = strlen(needle);
    while(n >= needle_size)
    {
        if(*haystack == *needle)
        {
            if (!strncmp(haystack, needle, needle_size))
            {
                return haystack;
            }
        }
        ++haystack;
        --n;
    }
    return NULL;
}
/*****************************************************************************/
ext2_status_t DisplayFile(const char *device_name, const char *file_name)
{
	int fd;
	size_t i = 0;
	char *block_buff_ptr = NULL;
	unsigned int data_inode = ROOT_INODE_INDEX;
	char sub_path_name[EXT2_NAME_LEN + 1];
	char *remain_path = (char*)file_name;
	ext2_status_t status = EXT2_SUCCESS;
	data_t data = {0};

	fd = open(device_name, O_RDONLY);    
	if( 0 > fd )
	{
		return EXT2_DEVICE_NOT_EXIST;
	}
	/*****************************************************************************/

	status = InitData(&data, fd);
	if(EXT2_SUCCESS != status)
	{
		return status;
	}

	if( 0 > ReadInode(&data, &(data.root_inode), fd, data_inode))
	{
		return EXT2_READ_ERROR;
	}

	while(remain_path)
	{
		remain_path = GetSubPath(remain_path, sub_path_name);
		for( i = 0, block_buff_ptr = NULL;
			 NULL == block_buff_ptr && i < EXT2_N_BLOCKS;
			 ++i)
		{
			status = ReadBlock(&data, fd, i);
			if(EXT2_SUCCESS != status)
			{
				return status;
			}

			block_buff_ptr = (char*)(NStrStr(data.block_buff, sub_path_name, data.block_size));
		}
		if(NULL == block_buff_ptr)
		{
			return EXT2_FILE_NOT_EXIST;
		}

		data_inode = *((unsigned int*)(block_buff_ptr - sizeof(__int64_t)));

		status = ReadInode(&data, &(data.root_inode), fd, data_inode);
		if(EXT2_SUCCESS != status)
		{
			return status;
		}
	}

	CopyFileContentToBuff(&data, fd);
	if(EXT2_SUCCESS != status)
	{
		return status;
	}


	printf("%s\n",data.text );

/*****************************************************************************/
	if(0 > close(fd))
	{
		return EXT2_CLOSE_ERR;
	}

	return EXT2_SUCCESS;
}
/*****************************************************************************/
ext2_status_t CopyFileContentToBuff(data_t *data, int fd)
{
	size_t i = 0;
	ext2_status_t status = EXT2_SUCCESS;
	for(i = 0; i < EXT2_N_BLOCKS; ++i)
	{
		status = lseek(fd, data->root_inode.i_block[i] * data->block_size, SEEK_SET);
		status = read(fd, data->text + i * data->block_size,data->block_size );
		if(EXT2_SUCCESS != status)
		{
			return status;
		}
	}
	return EXT2_SUCCESS;
}


char *GetSubPath(char *remain_path, char *buff)
{
	char *start = remain_path;

	remain_path = strchr(remain_path, '/');
	if(!remain_path)
	{
		strcpy(buff, start);
		return NULL;
	}
	memset(buff, 0, 256);
	strncpy(buff, start, remain_path - start);
	return (remain_path + 1);
}

