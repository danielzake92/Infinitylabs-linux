/****************************************************************************
 *  FILENAME:  ex3.c   NAME:  Daniel Zaken    REVIEWER: NitzanHolmes        * 
 *                                                                          *
 *  POURPOSE:  Implementation Endiancheack                                  *
 *                                                                          *
 ****************************************************************************/
#include <stdio.h> /*printf required*/
#include "word2.h" /*My implemented lib*/
/****************************************************************************/
void EndianCheck(void)
{
    unsigned int i = 0x01;
    char *c = (char*)&i;
    
    if (*c)
    {
        printf("\nSystem is Little Endian\n");
    }
    else
    {
        printf("\nSystem is Big Endian\n");
    }
}
