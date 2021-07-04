#include <stdio.h>


int SumTo10(const char *str);

int main()
{
	char str1[6] = "12391";
	char str2[2] = "1";
	char str3[3] = "28";
	char str4[3] = "22";
	char str5[6] = "12345";
	char str6[3] = "55";
	char str7[11] = "1111111111"; 
	char str8[6] = "22222"; 

	printf("%s -> %d\n",str1, SumTo10(str1));
	printf("%s -> %d\n",str2, SumTo10(str2));
	printf("%s -> %d\n",str3, SumTo10(str3));
	printf("%s -> %d\n",str4, SumTo10(str4));
	printf("%s -> %d\n",str5, SumTo10(str5));
	printf("%s -> %d\n",str6, SumTo10(str6));
	printf("%s -> %d\n",str7, SumTo10(str7));
	printf("%s -> %d\n",str8, SumTo10(str8));

	return 0;
}

int SumTo10(const char *str)
{
	int StringBool[10] = {0};
	char c = 0;

	while(*str)
	{
		c = *str - '0';
		if( StringBool[(10 - c)])
		{
			return 0;
		}

		StringBool[(int)c] = 1;

		++str;
	}

	return 1;
}

#if 0

int g_table[10] = 
{
	0, 1, 2, 3, 4, 5,
	4, 3, 2, 1
};

int SumTo10(const char *str)
{
	char c = 0;
	size_t i = 0;
	int sum[6] = {0};

	while(*str)
	{
		c = *str - '0';
		sum[(int)g_table[(int)c]] += c;
		++str;
	}

	for( i = 1; i < 6; ++i)
	{
		if( sum[i] >= 10 )
		{
			return 0;
		}
	}

	return 1;

}
#endif