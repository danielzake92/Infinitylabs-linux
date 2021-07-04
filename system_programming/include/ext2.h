/*****************************************************************************
* FILE:      ext2.h	       			   PURPOSE: ext2 file system
* DEVELOPER: Daniel Zaken              TEAM:    RD100
*
* VERSION:  0            
******************************************************************************/

#ifndef __ILRD_EXT2_H__
#define __ILRD_EXT2_H__


#include <stddef.h> /*size_t*/




#define RAM0_PATH "/dev/ram0"

typedef enum ext2_status
{
    EXT2_SUCCESS = 0,
    EXT2_DEVICE_NOT_EXIST = 1,
    EXT2_FILE_NOT_EXIST = 2,
    EXT2_SEEK_ERROR = 3,
    EXT2_READ_ERROR = 4,
    EXT2_CLOSE_ERR = 5
}ext2_status_t;

ext2_status_t DisplayFile(const char *device_name, const char *file_name);


#endif
