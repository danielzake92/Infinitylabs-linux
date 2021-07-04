#ifndef STRING_ILRD_H
#define STRING_ILRD_H
/*INCLUDE*/
#define _POSIX_C_SOURCE 200809L /*for strdup*/
#include <stdio.h>  /*Required Standart input output*/
#include <string.h> /*Required standart string functions to check implementations*/
#include <strings.h> /*Required standart string functions to check implementations*/
#include <ctype.h> /*To lower function is required*/
#include <stdlib.h> /*for malloc*/
#include <assert.h>  /*for assert*/
/*DECELERATION*/
size_t StrLen(const char *);
int StrCmp(const char *, const char *);
int StrCaseCmp(const char *, const char *);
char* StrCpy(char *, const char *);
char *StrnCpy(char *, const char *, size_t);
char* StrChr(const char *, int );
char *StrDup(const char *);
char *StrCat(char *, const char *);
char *StrnCat(char *, const char *, size_t);
char *StrStr(const char *, const char *);
size_t StrSpn(const char *, const char *);
#endif

