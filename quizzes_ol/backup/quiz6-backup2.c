#include <stdio.h>
#include <string.h>

int IsRotation(char *s1, char *s2);

int main()
{
	
	
	printf("%d\n", IsRotation("12345", "45123")); /*1*/

	printf("%d\n", IsRotation("12345", "451234")); /*0*/
	
	printf("%d\n", IsRotation("abcdefg", "cdefgab")); /*1*/
			
	printf("%d\n", IsRotation("121234", "123412")); /*1*/
	
	printf("%d\n", IsRotation("1212312", "1212123")); /*1*/
	
	return 0;
}
int IsRotation(char *s1, char *s2)
{
	char *ch1 = s1;
	char *ch2 = s2;
	size_t len = strlen(s1);
	size_t i = len;
	int flag = 1;
	if( len != strlen(s2) )
	{
		return 0; /*Not a rotation*/
	}
	
	while( (ch2 = strchr(s2, *s1)) != NULL )
	{
		
		i = len - 1; /*first place already checked*/
		flag = 1;
		
		while(i)
		{
			++ch1;
			++ch2;
			if( ( *ch1 != *ch2 ) && ( *ch2 != '\0' ) )
			{
				flag = 0;
				break;
			}
			if( *ch2 == '\0' )
			{
				ch2 = s2;
				if( *ch1 != *ch2 )
				{
					flag = 0;
					break;
				}
			}
			--i;
		}
		
		if (flag)
		{
			return 1; /*SUCCESS*/
		}
	}
	
	return 0;
		
}
