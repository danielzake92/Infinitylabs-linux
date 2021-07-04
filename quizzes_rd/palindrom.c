#include <stdio.h>

int IsPalindromContained(const char *src)
{
	if(!(*(src + 1)))
	{
		return 0;
	}
	if(*src == *(src + 1))
	{
		return 1;
	}

	src += 2;

	while(*src)
	{
		if(*src == *(src - 1) ||
		  (*src == *(src - 2)))
		{
			return 1;
		}
		++src;
	}

	return 0;
}


int main()
{
	char str1[3] = "ll";
	char str2[3] = "dl";
	char str3[4] = "ldl";
	char str4[6] = "hldlh";
	char str5[7] = "hhhhll";
	char str6[7] = "abcdll";

	printf("%s->%d\n",str1, IsPalindromContained(str1));
	printf("%s->%d\n",str2 ,IsPalindromContained(str2));
	printf("%s->%d\n",str3 ,IsPalindromContained(str3));
	printf("%s->%d\n",str4 ,IsPalindromContained(str4));
	printf("%s->%d\n",str5 ,IsPalindromContained(str5));
	printf("%s->%d\n",str6 ,IsPalindromContained(str6));
	printf("alladin->%d\n", IsPalindromContained("alladin"));
	printf("aladin->%d\n", IsPalindromContained("aladin"));
	printf("daniel->%d\n", IsPalindromContained("daniel"));
	printf("l->%d\n", IsPalindromContained("l"));


	return 0;
}

