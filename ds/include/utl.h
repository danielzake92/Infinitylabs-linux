
#ifndef __ILRD_UTL_H__
#define __ILRD_UTL_H__
/****************************************************************************/

# define BLACK "\033[30;1m"
# define RED "\033[31;1m"
# define GREEN "\033[32;1m"
# define YELLOW "\033[33;1m"
# define BLUE "\033[34;1m"
# define PURPLE "\033[35;1m"
# define CYAN "\033[36;1m"
# define WHITE "\033[37;1m"
# define DEFAULT "\x1b[0;0m"

# define Black "\033[30;1m"
# define Red "\033[31;1m"
# define Green "\033[32;1m"
# define Yellow "\033[33;1m"
# define Blue "\033[34;1m"
# define Purple "\033[35;1m"
# define Cyan "\033[36;1m"
# define White "\033[37;1m"
# define DEFAULT "\x1b[0;0m"


#define TRUE 1
#define FALSE 0

#define SUCCESS 0
#define FAIL 1

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define PRINT_TEST(a, b, format) \
	if ((a) == (b)) \
	{ \
		puts(GREEN"PASS"); \
	}\
	else \
	{ \
		printf("%sFAILED! Expected "format", not "format".\n", RED, (a), (b)); \
	}

#endif
