/****************************************************************************
 *  FILENAME:  WORD2.h   NAME:  Daniel Zaken    REVIEWER:  Daniel Bnedik    * 
 *                                                                          *
 *  POURPOSE:  Create LIB which implementes mem functions                   *
 *                                                                          *
 ****************************************************************************/
#ifndef __ILRD_WORD2_H__
#define __ILRD_WORD2_H__
#define IS_LITTLE __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ /*ex4*/
/****************************************************************************/

int Atoi_base(const char * str, size_t base);
void Itoa_base(int num, char * str, size_t base);

void PrintMagicPhrase(char *str1, char *str2, char *str3);

void EndianCheck(void);

#endif
