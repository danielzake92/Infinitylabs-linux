#include <stdio.h>
#include <stdlib.h>
#include "word2.h" /*My implemented lib*/
#define _POSIX_C_SOURCE 200809L

/****************************************************************************/

static void AtoiBase10Test(char *str);
/*void ItoaTest(int value, int base);*/

int main()
{
	
	
    char str1[20];
    char str2[20];
    char str3[20];
    char str4[20];
    char str5[20];
    
    char phrase1[10] = "AB4CD";
    char phrase2[10] = "DCEF4";					   
    char phrase3[10] = "ABGD6";
    
    char phrase4[25] = "ABCDEFGHAIJKLMNOP";
    char phrase5[25] = "GHIJKLMNOPQRASTUVWXYZ";
    char phrase6[20] = "LMNO";
        
/*************************************************************************/		
	printf ("\033[34;1mAtoi - TEST\033[0m \n");/*blue msg*/	
	
	printf("my_imp : %d source : %d \n",Atoi_base("00ZZA", 36), 46630);
	printf("my_imp : %d source : %d \n",Atoi_base("00FFA", 16), 4090);
	AtoiBase10Test("1234d45");
	AtoiBase10Test("-023004d45");
	AtoiBase10Test("00234D45");
	printf("my_imp : %d     source : %d \n",Atoi_base("-FF", 16), -255);
	printf("my_imp : %d    source : %d \n",Atoi_base("-ZZ", 36), -1295);
/*************************************************************************/		
	printf ("\033[34;1mItoa - TEST\033[0m \n");/*blue msg*/	
	
	Itoa_base(123456, str1, 10);
    printf("my_imp : %s    source : %s \n",str1, "123456");
    
    Itoa_base(-123456, str2, 10);
    printf("my_imp : %s   source : %s \n",str2, "-123456");
    
    Itoa_base(203, str3, 2);
    printf("my_imp : %s  source : %s \n",str3, "11001011");
    
    Itoa_base(12000, str4, 16);
	printf("my_imp : %s      source : %s \n",str4, "2EE0");
	
	Itoa_base(282, str5, 16);
	printf("my_imp : %s       source : %s \n",str5, "11A");
/*************************************************************************/		
	PrintMagicPhrase(phrase1, phrase2, phrase3);
	PrintMagicPhrase(phrase4, phrase5, phrase6);	
/*************************************************************************/	
	EndianCheck();
	
	printf("%d\n",IS_LITTLE);
	
	return 0;
}

/*
	
*/



void AtoiBase10Test(char *str)
{
	int res1 = atoi(str);
	int res2 = Atoi_base(str, 10);

	printf("source :\033[33;1m %d \033[0m my_imp :\033[33;1m %d \033[0m -",	res1, res2);
	
	if ( res1 == res2 )
	{
		printf ("\033[32;1m OK \033[0m\n");/*grn msg*/
	}
	else
	{
		printf ("\033[31;1m NOT OK \033[0m\n");/*red msg*/
	}
	
}




