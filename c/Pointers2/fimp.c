/****************************************************************************
 *  FILENAME:  Tese-Strings  NAME:  Daniel Zaken  REVIEWER:  Nitzan Holmes  *
 *                                                                          *
 *  POURPOSE:  tesitngs					                                    *
 *                                                                          *
 ****************************************************************************/

#include "String.h"  /*Implemented string library*/

/*PROTOTYPE*/
void StrLenTest (char *);
void StrCmpTest (char *, char *);
void StrChrTest (char *, char);
void StrCaseCmpTest (char *, char *);
void StrCpyTest(char*);

int main()
{
	/*strlen and strcmp strings*/
	char str1[]="Hello world";
	char str2[]="hello world";
	char str3[]="Hell";
	
	/*strcpy and strncpy strings*/	
	char dest1[25]; 
	char dest2[25];
	/*strchr strings*/	
	char chrchr[]="Hello world";
	
	/*strcat strings*/
	char start1 [25] = "hello";
	char start2 [25] = "hello";
	char *end = "world 1234";
	
	/*strncat strings*/
	char start3 [25] = "hello";
	char start4 [25] = "hello";
	/*StrStr strings*/
	char *ret1 = NULL; 
	char *ret2 = NULL; 	
	/*StrSpn strings*/
	size_t res = 0;
	size_t res2 = 0;
				
	puts("");
			    	
	/*STRLEN TESTS*/
	StrLenTest(str1);
	puts("");
	
	/*STRCMPTEST TESTS*/
	StrCmpTest(str1, str2);
	StrCmpTest(str2, str1);
	StrCmpTest(str1, str3);
	puts("");
	
	/*STRCASECMP TESTS*/
	StrCaseCmpTest(str1, str2);
	StrCaseCmpTest(str2, str1);
	StrCaseCmpTest(str1, str3);
	puts("");
			
	/*STRCPY TESTS*/
	printf ("\033[34;1m STRCPY\033[0m ");/*blue msg*/
	printf(" origin -\033[32;1m %s \033[0m my_imp -\033[32;1m %s \033[0m\n",
	strcpy(dest1, "hell"), StrCpy(dest1, "hell"));
	
	printf ("\033[34;1m STRCPY\033[0m ");/*blue msg*/
	printf(" origin -\033[32;1m %s \033[0m my_imp -\033[32;1m %s \033[0m\n",
	strcpy(dest2, "hell boy"), StrCpy(dest2, "hell boy"));
	puts("");
	
	
						
	/*STRCHR TESTS*/
	StrChrTest(chrchr, 'H');
	StrChrTest(chrchr, 'e');
	StrChrTest(chrchr, 'l');
	StrChrTest(chrchr, 'w');
	puts("");
	
	/*STRCAT TESTS*/
	printf ("\033[34;1m STRCAT\033[0m ");/*blue msg*/
	printf("origin -\033[32;1m %s \033[0m my_imp -\033[32;1m %s \033[0m\n",
	strcat(start1, end), StrCat(start2, end));
	puts("");
	
	/*STRNCAT TESTS*/
	printf ("\033[34;1m STRNCAT\033[0m ");/*blue msg*/
	printf("origin -\033[32;1m %s \033[0m my_imp -\033[32;1m %s \033[0m\n",
	strncat(start3, end, 5), StrnCat(start4, end, 5));
	puts("");
			
	
	/*STRSTR TESTS*/
	ret1 = StrStr("abimbambom", "bom");
	ret2 = strstr("abimbambom", "bom");
	printf ("\033[34;1m STRSTR\033[0m ");/*blue msg*/
	printf("source -\033[32;1m %s \033[0m my_imp -\033[32;1m %s \033[0m\n",
	ret2, ret1);
	
	ret1 = StrStr("abimbambom", "bam");
	ret2 = strstr("abimbambom", "bam");
	printf ("\033[34;1m STRSTR\033[0m ");/*blue msg*/
	printf("source -\033[32;1m %s \033[0m my_imp -\033[32;1m %s \033[0m\n",
	ret2, ret1);
	puts("");
	/*STRSPN TESTS*/
	
	res = StrSpn("abcdefgh", "abXXcdeZZh");
	res2 = strspn("abcdefgh", "abXXcdeZZh");
	printf ("\033[34;1m STRSPN\033[0m ");/*blue msg*/
	printf("source -\033[32;1m %lu \033[0m my_imp -\033[32;1m %lu \033[0m\n",
	res2, res);
	puts("");
	
	return 0;	
}







void StrLenTest (char *str)
{
	int origin = strlen(str), my_imp = StrLen(str);
	
	printf ("\033[34;1m STRLEN \033[0m ");/*blue msg*/
			
	if (origin == my_imp)
	{
		printf ("origin - %d  my_imp - %d  ", origin, my_imp);
		printf ("\033[32;1m OK \033[0m\n");/*grn msg*/
	}
	else
	{
		printf ("origin - %d  my_imp - %d  ", origin, my_imp);
		printf ("\033[31;1m NOT OK \033[0m\n");/*red msg*/
	}
}

void StrCmpTest (char *s1, char *s2)
{
	int origin = strcmp(s1,s2), my_imp = StrCmp(s1,s2);
	
	printf ("\033[34;1m STRCMP \033[0m ");/*blue msg*/
			
	if (origin == my_imp || origin*my_imp >= 0 )
	{
		printf ("origin - %d  my_imp - %d  ", origin, my_imp);
		printf ("\033[32;1m OK \033[0m\n");/*grn msg*/
	}
	else
	{
		printf ("origin - %d  my_imp - %d  ", origin, my_imp);
		printf ("\033[31;1m NOT OK \033[0m\n");/*red msg*/
	}
}

void StrCaseCmpTest (char *s1, char *s2)
{
	int origin = strcasecmp(s1,s2), my_imp = StrCaseCmp(s1,s2);
	
	printf ("\033[34;1m STRCASECMP \033[0m ");/*blue msg*/
			
	if (origin == my_imp || origin*my_imp >= 0)
	{
		printf ("origin - %d  my_imp - %d  ", origin, my_imp);
		printf ("\033[32;1m OK \033[0m\n");/*grn msg*/
	}
	else
	{
		printf ("origin - %d  my_imp - %d  ", origin, my_imp);
		printf ("\033[31;1m NOT OK \033[0m\n");/*red msg*/
	}
}



void StrChrTest (char *str , char ch)
{	
	
	char *origin = strchr(str, ch);
	char *my_imp = StrChr(str, ch);
	
	printf ("\033[34;1m STRCHR \033[0m ");/*blue msg*/
			
	if (*origin == *my_imp)
	{
		printf ("origin - %s  my_imp - %s  ", origin, my_imp);
		printf ("\033[32;1m OK \033[0m\n");/*grn msg*/
	}
	else
	{
		printf ("origin - %s  my_imp - %s  ", origin, my_imp);
		printf ("\033[31;1m NOT OK \033[0m\n");/*red msg*/
	}
}





