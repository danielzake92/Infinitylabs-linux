
/*************************************************************************** 
 * Description: Testing of Implementation of AVL
 
 * Author: Nitzan Holmes
 ***************************************************************************/


#include <stdio.h>     /* printf */
#include <assert.h>    /* assert */
#include <stdlib.h>    /* rand, srand */
#include <time.h>      /* time */
#include "dhcp.h"     


/******************************************************************************/
/***                        Color Defines   		                      ***/
/******************************************************************************/
#define DEF     "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

static int test_counter_g = 0;
static int success_counter_g = 0;



#define TEST(name, real, expected) \
    do { \
        ++test_counter_g; \
        ((real) == (expected)) ? \
        ++success_counter_g : \
        printf(RED "%s, Failed on line %d, Real: %ld, Expected: %ld\n" DEF, name, __LINE__, (long) (real), (long) (expected)); \
    } while (0)

#define TESTC(name, real, expected) \
    do { \
        ++test_counter_g; \
        ((real) == (expected)) ? \
        ++success_counter_g : \
        printf(RED "%s, Failed on line %d, Real: %c, Expected: %c\n" DEF, name, __LINE__, (char) (real), (char) (expected)); \
    } while (0)

#define PASS (test_counter_g == success_counter_g) ? \
    printf(GREEN "Passed everything!\n\n" DEF) : \
    printf(RED "Failed " BOLDRED "%d/%d" RED" tests.\n\n" DEF, \
           test_counter_g - success_counter_g, test_counter_g)


#define TESTIP(name, real, expected) \
    do { \
        ++test_counter_g; \
        if ((real)[0] == (expected)[0] && (real)[1] == (expected)[1] && \
           (real)[2] == (expected)[2] && (real)[3] == (expected)[3]) \
        { \
        ++success_counter_g; \
        } \
        else \
        { \
        printf(RED "%s, Failed on line %d, Real: ", name, __LINE__); \
        PrintIP(real); \
        printf(", Expected: "); \
        PrintIP(expected); \
        printf("\n" DEF); \
        } \
    } while (0)

/************************* Tests Functions *************************/
static void PrintIP(ip_t ip)
{
	printf("%d.%d.%d.%d", (int) ip[0], (int) ip[1], 
	                      (int) ip[2], (int) ip[3]);
}

static void TestCreateDestroy(void)
{
	unsigned int subnet_size = 24;
	ip_t my_ip = {196, 77, 89, 0};
	dhcp_t *dh = DHCPCreate(my_ip, subnet_size);
	
	DHCPDestroy(dh);
	
	printf(BOLDGREEN "Completed TestCreateDestroy\n" DEF);
}
/*Easy test for mask size of 24 */
static void Test1(void)
{
	ip_t network = {196, 77, 89, 0};
	unsigned int subnet_size = 24;
	ip_t ip1 = {196, 77, 89, 4};
	ip_t ip2= {196, 77, 89, 252};
	ip_t ip8= {196, 255, 255, 0};
	ip_t ip9= {196, 77, 89, 0};
	ip_t ip10 = {196, 77, 89, 22};
	ip_t ip11 = {196, 77, 89, 23};
	ip_t ip12 = {196, 77, 89, 24};
	ip_t should1 = {196, 77, 89, 5};
	ip_t should2 = {196, 77, 89, 6};
	ip_t should3 = {196, 77, 89, 7};
	ip_t should4 = {196, 77, 89, 8};
	ip_t should5= {196, 77, 89, 253};
	ip_t should7= {196, 77, 89, 1};
	ip_t zeros = {0,0,0,0};
	
	ip_t res = {0,0,0, 0};
	size_t count = 0;
	
	dhcp_t *dh = DHCPCreate(network, subnet_size);
	count = DHCPCountFree(dh);
	TEST("size", 253, count);
	
	DHCPAllocateNewIP(dh, ip1, res);
	count = DHCPCountFree(dh);
	
	TEST("size", 252, count);
	TESTIP("alloc",res, ip1);
	
	DHCPAllocateNewIP(dh, ip1, res);
	count = DHCPCountFree(dh);
	
	TEST("size", 251, count);
	TESTIP("alloc",res, should1);
	
	DHCPAllocateNewIP(dh, ip1, res);
	count = DHCPCountFree(dh);
	
	TEST("size", 250, count);
	TESTIP("alloc",res, should2);
	
	DHCPAllocateNewIP(dh, ip1, res);
	count = DHCPCountFree(dh);
	
	TEST("size", 249, count);
	TESTIP("alloc",res, should3);
	
	DHCPAllocateNewIP(dh, ip1, res);
	count = DHCPCountFree(dh);
	
	TEST("size", 248, count);
	TESTIP("alloc",res, should4);
	
	DHCPAllocateNewIP(dh, ip2, res);
	count = DHCPCountFree(dh);
	
	TEST("size", 247, count);
	TESTIP("alloc",res, ip2);
	
	DHCPAllocateNewIP(dh, ip2, res);
	count = DHCPCountFree(dh);
	
	TEST("size", 246, count);
	TESTIP("alloc",res, should5);
	
	DHCPAllocateNewIP(dh, ip2, res); /*insert 254*/
	count = DHCPCountFree(dh);
	
	TEST("size", 246, count);
	TESTIP("alloc",res, zeros);
	

	
	
	DHCPAllocateNewIP(dh, ip8, res);
	count = DHCPCountFree(dh);
	
	TEST("size", 246, count);
	TESTIP("alloc",res, res);
	
	DHCPAllocateNewIP(dh, ip9, res);
	count = DHCPCountFree(dh);
	
	TEST("size", 245, count);
	TESTIP("alloc",res, should7);
	
	DHCPAllocateNewIP(dh, ip10, res);
	count = DHCPCountFree(dh);
	
	TEST("size", 244, count);
	TESTIP("alloc",res, ip10);
	
	DHCPAllocateNewIP(dh, ip10, res);
	count = DHCPCountFree(dh);
	
	TEST("size", 243, count);
	TESTIP("alloc",res, ip11);
	
	DHCPAllocateNewIP(dh, ip10, res);
	count = DHCPCountFree(dh);
	
	TEST("size", count, 242);
	TESTIP("alloc",res, ip12);
	
	DHCPDestroy(dh);
	
	printf(BOLDGREEN "Completed Test1- mask size 24 only insert\n" DEF);
}
/*Test with mask 24 including remove*/
static void Test2(void)
{
	ip_t network = {196, 77, 89, 0};
	unsigned int subnet_size = 24;
	ip_t ip1 = {196, 77, 89, 4};
	
	ip_t rem1 = {196, 77, 89, 6};
	ip_t rem2 = {196, 77, 89, 27};
	ip_t rem3 = {196, 77, 81, 27};
	
	ip_t should1 = {196, 77, 89, 5};
	ip_t should2 = {196, 77, 89, 6};
	ip_t should3 = {196, 77, 89, 7};
	ip_t should4 = {196, 77, 89, 8};
	ip_t should7 = {196, 77, 89, 1};
	ip_t zeros = {0,0,0,0};

	ip_t res = {0,0,0, 0};
	size_t count = 0;
	
	dhcp_t *dh = DHCPCreate(network, subnet_size);
	count = DHCPCountFree(dh);
	TEST("size", 253, count);
	
	DHCPAllocateNewIP(dh, ip1, res);
	count = DHCPCountFree(dh);
	
	TEST("size", 252, count);
	TESTIP("alloc",res, ip1);
	
	DHCPAllocateNewIP(dh, ip1, res);
	count = DHCPCountFree(dh);
	
	TEST("size", 251, count);
	TESTIP("alloc",res, should1);
	
	DHCPAllocateNewIP(dh, ip1, res);
	count = DHCPCountFree(dh);
	
	TEST("size", 250, count);
	TESTIP("alloc",res, should2);
	
	DHCPAllocateNewIP(dh, ip1, res);
	count = DHCPCountFree(dh);
	
	TEST("size", 249, count);
	TESTIP("alloc",res, should3);
	
	DHCPAllocateNewIP(dh, ip1, res);
	count = DHCPCountFree(dh);
	
	TEST("size", 248, count);
	TESTIP("alloc",res, should4);
	
	DHCPFreeIP(dh, rem1);
	count = DHCPCountFree(dh);
	
	TEST("size", 249, count);
	
	DHCPFreeIP(dh, rem1);
	count = DHCPCountFree(dh);
	
	TEST("size", 249, count);

	DHCPAllocateNewIP(dh, should1, res);
	count = DHCPCountFree(dh);
	
	TEST("size", 248, count);
	TESTIP("alloc",res, rem1);
	
	DHCPFreeIP(dh, rem2);
	count = DHCPCountFree(dh);
	
	TEST("size", 248, count);
	
	DHCPFreeIP(dh, rem3);
	count = DHCPCountFree(dh);
	
	TEST("size", 248, count);
	
	DHCPAllocateNewIP(dh, zeros, res);
	count = DHCPCountFree(dh);
	
	TEST("size", count, 247);
	TESTIP("alloc",should7, res);
	
	DHCPDestroy(dh);
	
	printf(BOLDGREEN "Completed Test2- mask size 24 insert and remove\n" DEF);
}
/*NOT EASY PEASY LEMON SQUEEZY TEST - MASK IS 26*/
static void Test3(void)
{
	
	ip_t network = {196, 77, 89, 192}; /* |196|77|89|10-000000*/
	unsigned int subnet_size = 26;
	ip_t ip1 = {196, 77, 89, 150}; 
	ip_t ip2 = {196, 77, 89, 200}; 
	ip_t should1 = {196, 77, 89, 201};
	ip_t should2 = {196, 77, 89, 202};
	ip_t should3 = {196, 77, 89, 203};
	ip_t should4 = {196, 77, 89, 204};
	

	ip_t zeros = {0,0,0,0};
	ip_t res = {0,0,0, 0};
	size_t count = 0;

	
	dhcp_t *dh = DHCPCreate(network, subnet_size);
	count = DHCPCountFree(dh);
	TEST("size", 61, count);
	
	DHCPAllocateNewIP(dh, ip2, res);
	count = DHCPCountFree(dh);
	
	TEST("size", 60, count);
	TESTIP("alloc",res, ip2);
	
	DHCPAllocateNewIP(dh, ip1, res);
	count = DHCPCountFree(dh);
	
	TEST("size", 60, count);
	TESTIP("alloc",zeros, res);
	
	DHCPAllocateNewIP(dh, ip2, res);
	count = DHCPCountFree(dh);
	
	TEST("size", 59, count);
	TESTIP("alloc",res, should1);
	
	DHCPAllocateNewIP(dh, ip2, res);
	count = DHCPCountFree(dh);
	
	TEST("size", 58, count);
	TESTIP("alloc",res, should2);
	
	DHCPAllocateNewIP(dh, ip2, res);
	count = DHCPCountFree(dh);
	
	TEST("size", 57, count);
	TESTIP("alloc",res, should3);
	
	DHCPAllocateNewIP(dh, ip2, res);
	count = DHCPCountFree(dh);
	
	TEST("size", 56, count);
	TESTIP("alloc",res, should4);
	
	DHCPFreeIP(dh, should3);
	count = DHCPCountFree(dh);
	
	TEST("size", 57, count);
	
	DHCPFreeIP(dh, should3);
	count = DHCPCountFree(dh);
	
	TEST("size", 57, count);
	
	DHCPAllocateNewIP(dh, should2, res);
	count = DHCPCountFree(dh);
	
	TEST("size", 56, count);
	TESTIP("alloc",res, should3);
	
	DHCPDestroy(dh);
	printf(BOLDGREEN "Completed Test3- mask size 26 insert and remove\n" DEF);
}

/*NOT EASY PEASY LEMON SQUEEZY TEST - MASK IS 22*/
static void Test4(void)
{

	ip_t network = {196, 77, 252, 0}; /* |196|77|89|10-000000*/
	unsigned int subnet_size = 22;  /*11111100-00000000*/
	ip_t ip1 = {196, 77, 252, 150};
	ip_t ip2 = {196, 77, 252, 151};
	ip_t should1 = {196, 77, 253, 150};
	ip_t should2 = {196, 77, 254, 1};
	ip_t should3 = {196, 77, 248, 150};
	ip_t should4 = {196, 77, 89, 204};


	ip_t zeros = {0,0,0,0};
	ip_t res = {0,0,0, 0};
	size_t count = 0;

	dhcp_t *dh = DHCPCreate(network, subnet_size);
	count = DHCPCountFree(dh);
	TEST("size", 1021, count);

	DHCPAllocateNewIP(dh, ip1, res);
	count = DHCPCountFree(dh);

	TEST("size", 1020, count);
	TESTIP("alloc",res, ip1);

	DHCPAllocateNewIP(dh, ip1, res);
	count = DHCPCountFree(dh);

	TEST("size", 1019, count);
	TESTIP("alloc",res, ip2);

	DHCPAllocateNewIP(dh, should1, res);
	count = DHCPCountFree(dh);

	TEST("size", 1018, count);
	TESTIP("alloc",res, should1);

	DHCPAllocateNewIP(dh, should2, res);
	count = DHCPCountFree(dh);

	TEST("size", 1017, count);
	TESTIP("alloc",res, should2);

	DHCPAllocateNewIP(dh, should3, res);
	count = DHCPCountFree(dh);

	TEST("size", 1017, count);
	TESTIP("alloc",zeros, res);

	DHCPAllocateNewIP(dh, should4, res);
	count = DHCPCountFree(dh);

	TEST("size", 1017, count);
	TESTIP("alloc",zeros, res);

	DHCPFreeIP(dh, should3);
	count = DHCPCountFree(dh);

	TEST("size", 1017, count);

	DHCPFreeIP(dh, ip2);
	count = DHCPCountFree(dh);

	TEST("size", 1018, count);

	DHCPAllocateNewIP(dh, ip1, res);
	count = DHCPCountFree(dh);

	TEST("size", 1017, count);
	TESTIP("alloc",res, ip2);




	DHCPDestroy(dh);
	printf(BOLDGREEN "Completed Test4- mask size 22 insert and remove\n" DEF);
}

/************************* main function *************************/

int main(void)
{
	
	/* just create and destroy */
	TestCreateDestroy();
	
	/* push and pop, and check size and peek */
	Test1();
	
	/* now with remove */
	Test2();
	
	/* test with a big loop */
	Test3();

	Test4();
	
	PASS;
	
	return 0;
}
