/****************************************************************************
 *  FILENAME:  mem.h   NAME:  Daniel Zaken    REVIEWER:                     * 
 *                                                                          *
 *  POURPOSE:  Create LIB which implementes mem functions                   *
 *                                                                          *
 ****************************************************************************/
#ifndef __ILRD_MEM_H__
#define __ILRD_MEM_H__
/****************************************************************************/

void *MemSet(void *str, int c, size_t n);
void *MemCpy(void *dest, const void * src, size_t n);
void *MemMove(void *str1, const void *str2, size_t n);

#endif
