/*INCLUDE*/
#include <stdio.h> /*required printf*/
#include <string.h> /*reqiured original memset*/
#include "mem.h" /*my implemented lib*/


void MemSetTest(char *s1, char *s2, int c, size_t n);

int main()
{
	int i = 0;
	/*memset*/
	char str1[20] = "good morning daniel";
	char str2[20] = "good morning daniel";
	char str3[20] = "good morning daniel";
	char str4[20] = "good morning daniel";
	/*memcpy*/
	char str5[40] = "good morning daniel good morning daniel";
	char str6[40] = "good morning daniel good morning daniel";
	/*memmove*/
	char str7[40] = "123456789";
	char str8[40] = "123456789";
	char str9[40] = "123456789";
    char str10[40] = "123456789";
	char str11[100] = "\0\0\0\0\0\0\0abcdefghijklmnopqrstuvwxyz";
	char str12[2] = "S";
	char str13[2] = "S";
	
	/*memset*/	
	MemSetTest(str1, str2, 85, 7);
	MemSetTest(str3 + 3, str4 + 3, 88, 16);
	MemSetTest(str12, str13, 90, 1);
	/*memcpy*/
	printf ("\033[34;1mMEMCPY - TEST\033[0m \n");/*blue msg*/	
	printf("Before (original) = %s || (my_imp) = %s\n",str5, str6);
	memcpy(str5+2, str5+5, 20);
	MemCpy(str6+2, str6+5, 20);
	printf(" after (original) = %s || (my_imp) = %s\n",str5, str6);
		
	/*memmove - 1*/
	printf ("\033[34;1mMEMMOVE - TEST1\033[0m \n");/*blue msg*/	
	printf("Before (original) = %s || (my_imp) = %s\n",str7, str8);
	memmove(str7+2, str7+5, 9);
	MemMove(str8+2, str8+5, 9);
	printf(" after (original) = %s || (my_imp) = %s\n",str7, str8);
	/*memmove - 2*/
	printf ("\033[34;1mMEMMOVE - TEST2\033[0m \n");/*blue msg*/	
	printf("Before (original) = %s || (my_imp) = %s\n",str9, str10);
	memmove(str9+3, str9+1, 9);
	MemMove(str10+3, str10+1, 9);
	printf(" after (original) = %s || (my_imp) = %s\n",str9, str10);
	
	/*memmove - 3*/
	printf ("\033[34;1mMEMMOVE - TEST3\033[0m \n");/*blue msg*/	
    MemMove((void*)(str11),(void*)(str11+7),10);
    for ( i= 0; i<100 ; ++i)
    {
        printf("%c",str11[i]);
    }
	puts("");
		
	return 0;
}

void MemSetTest(char *s1, char *s2, int c, size_t n)
{
	printf ("\033[34;1mMEMSET - TEST\033[0m \n");/*blue msg*/	
	printf("Before (original) = %s || (my_imp) = %s\n",s1, s2);
	memset(s1, c, n);
	MemSet(s2, c, n);
	printf(" after (original) = %s || (my_imp) = %s\n",s1, s2);
}






