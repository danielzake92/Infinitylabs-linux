#include <stdio.h>
#include <string.h>

int IsRotation(char *s1, char *s2);

int main()
{
	
	
	printf("%d\n", IsRotation("12345", "45123"));

	printf("%d\n", IsRotation("12345", "451234"));
	
	printf("%d\n", IsRotation("abcdefg", "cdefgab"));
			
	printf("%d\n", IsRotation("121234", "123412"));
	
	return 0;
}
int IsRotation(char *s1, char *s2)
{
	char *ch1 = s1;
	char *ch2 = s2;
	size_t len = strlen(s1);
	
	if( len != strlen(s2) )
	{
		return 1; /*Not a rotation*/
	}
	if( (ch2 = strchr(s2, *s1)) == NULL )
	{
		return 1;
	}
	
	--len; /*first place already checked*/
	
	while(len)
	{
		++ch1;
		++ch2;
		if( ( *ch1 != *ch2 ) && ( *ch2 != '\0' ) )
		{
			return 1;
		}
		if( *ch2 == '\0' )
		{
			ch2 = s2;
			if( *ch1 != *ch2 )
			{
				return 1;
			}
		}
		--len;
	}
	
	return 0; /*SUCCESS*/
}
