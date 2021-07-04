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
	char *ch = s2;
	size_t len = strlen(s1);
	size_t i = 0;
	size_t index = 0;
	size_t count = 0;
	if( len != strlen(s2) )
	{
		return 0; /*Not a rotation*/
	}
	if( (ch = strchr(s2, *s1)) == NULL )
	{
		return 0;
	}
	
	
	do
	{
		index = ch - s2;		
		for (i = 0; i < len ;++i, index = (i+1) % len )
		{
			
			if( ( s1[i] == s2[index] ) )
			{	
				++count;
			}
			
				
		}
		if (count == len)
		{	
			
			return 1; /*SUCCESS*/
		}
		
		++ch;
		ch = strchr(s2, *s1);
		
	}while(  ch != NULL );
	
	return 0;
		
}	
	
	
	

