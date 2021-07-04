#include <stdio.h>
#include <stddef.h>
#define MAX2(a, b) ( (a) > (b) ? (a) : (b))
#define MAX3(a, b, c) ( MAX2((a), (b)) > (c) ? MAX2((a), (b)) : (c) )
#define TO_LOWER(a) ( 'A' <= a && a <= 'Z' ? a + ('a' - 'A' ) : a )
#define container_of(ptr, type, member) ({ \
                const typeof( ((type *)0)->member ) *__mptr = (ptr); \
                (type *)( (char *)__mptr - offsetof(type,member) );})
typedef struct super
{
	int num;
	char ch1;
	int *ptr;
	char ch2;
}super;  /*16byte*/

union u
{
 int num;
 char arr[5];
}u1;

typedef struct
{
	int num;
	char ch1;
}s2;

int main()
{
	super s1;
	printf("size of s1 = %lu\n", sizeof(s1));
	printf("size of s2 = %lu\n", sizeof(s2));
	printf("size of u1 = %lu\n", sizeof(u1));
	

	
	
	printf("%c\n", TO_LOWER('A'));
	
	printf("the offset is = %ld\n", offsetof(s1, num));
	
	return 0;
}
