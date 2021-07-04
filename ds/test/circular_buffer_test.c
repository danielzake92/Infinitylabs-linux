#include <stdio.h>
#include <string.h>
#include "circular_buffer.h"

typedef char flexible_array_t[1];
struct circular_buffer
{
    size_t size;
    size_t capacity;
    size_t read_from;
    flexible_array_t buffer;
};

static void PrintBufferChar(const circular_buffer_t *buffer);

static void PrintBufferInt(const circular_buffer_t *buffer);

static void PrintIntArray(const int *arr, size_t size);

static void TestChar();

static void TestInt();

int main()
{
	puts("Test with char:");
	TestChar();
	puts("\n**********************************************\n");
	puts("Test with int:");
	TestInt();
	return 0;
}

void TestChar()
{
	char src[] = "abcdef";
	char src1[] = "ghijk";
	char src2[] = "lmnop";
	char dest[11] = {0};
	circular_buffer_t *buffer = CircularBufferCreate(10);
	puts("Create a circular buffer of capacity == 10.");
	if (!buffer)
	{
		puts("Error while creating a circular buffer.");
	}
	else
	{
		puts("\nsrc, src1 and src2:");
		printf("src: %s\n", src);
		printf("src1: %s\n", src1);
		printf("src2: %s\n", src2);
		
		puts("\nCheck if the buffer is empty, should be empty:");
		if (CircularBufferIsEmpty(buffer))
		{
			puts("Buffer empty!");
		}
		else
		{
			puts("ERROR! Buffer should be empty!");
		}
		
		puts("\nWrite src and src1 to the buffer, should write 6 and 4 bytes:");
		printf("Bytes written: %ld\n", CircularBufferWrite(buffer, src, strlen(src)));
		PrintBufferChar(buffer);
		printf("Bytes written: %ld\n", CircularBufferWrite(buffer, src1, strlen(src1)));
		PrintBufferChar(buffer);
		
		puts("\nCheck if the buffer is empty, shouldn't be empty:");
		if (!CircularBufferIsEmpty(buffer))
		{
			puts("Buffer is not empty!");
		}
		else
		{
			puts("ERROR! Buffer shouldn't be empty!");
		}
		
		puts("\nSize should be 10, read_from index should be 0:");
		printf("size: %lu\n", CircularBufferBuffSiz(buffer) - 
								CircularBufferFreeSpace(buffer));
		printf("read_from: %lu\n", buffer->read_from);
		
		puts("\nRead from buffer to dest, should be 5:");
		printf("Bytes read: %ld\n", CircularBufferRead(buffer, dest, 5));
		printf("dest: %s\n", dest);
		
		puts("\nSize should be 5, read_from index should be 5:");
		printf("size: %lu\n", CircularBufferBuffSiz(buffer) - 
								CircularBufferFreeSpace(buffer));
		printf("read_from: %lu\n", buffer->read_from);
		
		puts("\nWrite src2 to the buffer, should write 5 bytes:");
		printf("Bytes written: %ld\n", CircularBufferWrite(buffer, src2, 5));
		PrintBufferChar(buffer);
		
		puts("\nRead from buffer to dest, should be 10:");
		printf("read_from: %lu\n", buffer->read_from);
		printf("Bytes read: %ld\n", CircularBufferRead(buffer, dest, CircularBufferBuffSiz(buffer)));
		printf("dest: %s\n", dest);
		
		puts("\nCheck if the buffer is empty, should be empty:");
		if (CircularBufferIsEmpty(buffer))
		{
			puts("Buffer empty!");
		}
		else
		{
			puts("ERROR! Buffer should be empty!");
		}
		puts("\nWrite src to the buffer, should write 5 bytes:");
		printf("Bytes written: %ld\n", CircularBufferWrite(buffer, src, 5));
		PrintBufferChar(buffer);
		
		CircularBufferDestroy(buffer);
	}
}

void TestInt()
{
	int src[] = {1, 2, 3, 4, 5, 6};
	int src1[] = {7, 8, 9, 10, 11};
	int src2[] = {12, 13, 14, 15, 16};
	int dest[10] = {0};
	circular_buffer_t *buffer = CircularBufferCreate(10 * sizeof(int));
	puts("Create a circular buffer of capacity == 40.");
	if (!buffer)
	{
		puts("Error while creating a circular buffer.");
	}
	else
	{
		puts("\nsrc, src1 and src2:");
		printf("src: ");
		PrintIntArray(src, 6);
		printf("src1: ");
		PrintIntArray(src1, 5);
		printf("src2: ");
		PrintIntArray(src2, 5);
		
		puts("\nCheck if the buffer is empty, should be empty:");
		if (CircularBufferIsEmpty(buffer))
		{
			puts("Buffer empty!");
		}
		else
		{
			puts("ERROR! Buffer should be empty!");
		}
		
		puts("\nWrite src and src1 to the buffer, should write 24 and 16 bytes:");
		printf("Bytes written: %ld\n", CircularBufferWrite(buffer, src, sizeof(src)));
		PrintBufferInt(buffer);
		printf("Bytes written: %ld\n", CircularBufferWrite(buffer, src1, sizeof(src1)));
		PrintBufferInt(buffer);
		
		puts("\nCheck if the buffer is empty, shouldn't be empty:");
		if (!CircularBufferIsEmpty(buffer))
		{
			puts("Buffer is not empty!");
		}
		else
		{
			puts("ERROR! Buffer shouldn't be empty!");
		}
		
		puts("\nSize should be 40, read_from index should be 0:");
		printf("size: %lu\n", CircularBufferBuffSiz(buffer) - 
								CircularBufferFreeSpace(buffer));
		printf("read_from: %lu\n", buffer->read_from);
		
		puts("\nRead from buffer to dest, should be 20:");
		printf("Bytes read: %ld\n", CircularBufferRead(buffer, dest, 5 * sizeof(int)));
		printf("dest: ");
		PrintIntArray(dest, 5);
		
		puts("\nSize should be 20, read_from index should be 20:");
		printf("size: %lu\n", CircularBufferBuffSiz(buffer) - 
								CircularBufferFreeSpace(buffer));
		printf("read_from: %lu\n", buffer->read_from);
		
		puts("\nWrite src2 to the buffer, should write 20 bytes:");
		printf("Bytes written: %ld\n", CircularBufferWrite(buffer, src2, 5 * sizeof(int)));
		PrintBufferInt(buffer);
		
		puts("\nRead from buffer to dest, should be 40:");
		printf("read_from: %lu\n", buffer->read_from);
		printf("Bytes read: %ld\n", CircularBufferRead(buffer, dest, CircularBufferBuffSiz(buffer)));
		printf("dest: ");
		PrintIntArray(dest, 10);
		
		puts("\nCheck if the buffer is empty, should be empty:");
		if (CircularBufferIsEmpty(buffer))
		{
			puts("Buffer empty!");
		}
		else
		{
			puts("ERROR! Buffer should be empty!");
		}
		puts("\nWrite src to the buffer, should write 20 bytes:");
		printf("Bytes written: %ld\n", CircularBufferWrite(buffer, src, 5 * sizeof(int)));
		PrintBufferInt(buffer);
		
		CircularBufferDestroy(buffer);
	}
}

void PrintBufferChar(const circular_buffer_t *buffer)
{
	size_t i = 0;
	size_t index = buffer->read_from;
	const char *ptr = buffer->buffer;
	for (i = 0; i < buffer->size; i++)
	{
		printf("%c ", ptr[index]);
		index = (index + 1) % buffer->capacity;
	}
	puts("");
}

void PrintBufferInt(const circular_buffer_t *buffer)
{
	size_t i = 0;
	size_t index = buffer->read_from / sizeof(int);
	const int *ptr = (const int *)buffer->buffer;
	for (i = 0; i < buffer->size; i += sizeof(int))
	{
		printf("%d ", ptr[index]);
		index = (index + 1) % (buffer->capacity / sizeof(int));
	}
	puts("");
}

void PrintIntArray(const int *arr, size_t size)
{
	size_t i = 0;
	for (i = 0; i < size; i++)
	{
		printf("%d ", arr[i]);
	}
	puts("");
}
