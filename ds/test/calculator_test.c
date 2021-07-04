#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "calculator.h"
#include "utl.h"

#define PRINT_TEST(a, b, format) \
	if ((a) == (b)) \
	{ \
		puts(GREEN"PASS"); \
	}\
	else \
	{ \
		printf("%sFAILED! Expected "format", not "format".\n", RED, (a), (b)); \
	}

void TestDanielz(void);
void TestPeleg (void);
void TestNitzan(void);

int main()
{
	printf ("%s*****************************************\n",WHITE);
	printf ("%s---------------Calculator tests---------------\n",WHITE);
	printf ("%s*****************************************\n",WHITE);

	TestDanielz();
	TestPeleg();
	TestNitzan();

	printf ("%s*****************************************\n",WHITE);
	printf ("%s---------------Calculator ended----------------\n",WHITE);
	printf ("%s*****************************************\n",WHITE);

	return 0;
}


void TestDanielz(void)
{
	double res = 0;

	Calculate("-2 + 3 * -6 + 5^3 +-2", &res); /*103*/
	printf(YELLOW"res = "GREEN"%f\n"DEFAULT,res);

	Calculate("-2.5*2.5*+2.5", &res); /*-15.625*/
	printf(YELLOW"res = "GREEN"%f\n"DEFAULT,res);

	Calculate(" 2 - -2 ^ 2 ^ 2 ^ 1 ", &res); /*-14*/
	printf(YELLOW"res = "GREEN"%f\n"DEFAULT,res);

	Calculate(" 20/-5/2*5 ", &res); /*-10*/
	printf(YELLOW"res = "GREEN"%f\n"DEFAULT,res);

	Calculate("10/2*5", &res); /*25*/
	printf(YELLOW"res = "GREEN"%f\n"DEFAULT,res);

	Calculate("4^(2^3-5)", &res);/*64*/
	printf(YELLOW"res = "GREEN"%f\n"DEFAULT,res);

	Calculate("2+2^3^2*2", &res);/*1026*/
	printf(YELLOW"res = "GREEN"%f\n"DEFAULT,res);

	Calculate("4+7*3-4*5-2", &res);/*3*/
	printf(YELLOW"res = "GREEN"%f\n"DEFAULT,res);

}

void TestPeleg(void)
{
	calc_status_t status = CALC_SUCCESS;
	double res = 0.0;
	double test_res = 0.0;

	puts(BLUE"********************VALID EXPRESSIONS********************");

	status = Calculate("2 + 1", &res);
	test_res = 3.0;
	PRINT_TEST(test_res, res, "%f");

	status = Calculate("2 * 3", &res);
	test_res = 6.0;
	PRINT_TEST(test_res, res, "%f");

	status = Calculate("2 * 3 + 1", &res);
	test_res = 7.0;
	PRINT_TEST(test_res, res, "%f");

	status = Calculate("4 + 2 * 3", &res);
	test_res = 10.0;
	PRINT_TEST(test_res, res, "%f");

	status = Calculate("4 + 2 - 3", &res);
	test_res = 3.0;
	PRINT_TEST(test_res, res, "%f");

	status = Calculate("4 ^ 2 - 3", &res);
	test_res = 13.0;
	PRINT_TEST(test_res, res, "%f");

	status = Calculate("4 ^ (2 ^ 3 - 5)", &res);
	test_res = 64.0;
	PRINT_TEST(test_res, res, "%f");

	status = Calculate("(2 ^ 3 - 5) ^ 4", &res);
	test_res = 81.0;
	PRINT_TEST(test_res, res, "%f");

	status = Calculate("(2 ^ ((3 + 12) - (5 + 7))) ^ 2", &res);
	test_res = 64.0;
	PRINT_TEST(test_res, res, "%f");

	status = Calculate("2 ^ ((3 + 12) - (5 + 7)) ^ 2", &res);
	test_res = 512.0;
	PRINT_TEST(test_res, res, "%f");

	status = Calculate("2 ^ 4 ^ 2 * 2", &res);
	test_res = 131072.0;
	PRINT_TEST(test_res, res, "%f");

	status = Calculate("1 + (1)", &res);
	test_res = 2.0;
	PRINT_TEST(test_res, res, "%f");

	status = Calculate("-1 * 4", &res);
	test_res = -4.0;
	PRINT_TEST(test_res, res, "%f");

	status = Calculate("-1 * -4", &res);
	test_res = 4.0;
	PRINT_TEST(test_res, res, "%f");

	status = Calculate("+12.5 * -23.5 - 25.5 ", &res);
	test_res = -319.25;
	PRINT_TEST(test_res, res, "%f");

	status = Calculate("-1--1--1", &res);
	test_res = 1.0;
	PRINT_TEST(test_res, res, "%f");

	status = Calculate("+1", &res);
	test_res = 1.0;
	PRINT_TEST(test_res, res, "%f");

	status = Calculate(" 2 + 2 ^ 3 ^ 2 * 2 ", &res);
	test_res = 1026.0;
	PRINT_TEST(test_res, res, "%f");

	puts(BLUE"\n********************INVALID EXPRESSIONS********************");

	status = Calculate("1 / 0", &res);
	PRINT_TEST(CALC_MATH_ERROR, status, "%d");

	status = Calculate("10 / 0 / 5", &res);
	PRINT_TEST(CALC_MATH_ERROR, status, "%d");

	status = Calculate("+ 1", &res);
	PRINT_TEST(CALC_SYNTAX_ERROR, status, "%d");

	status = Calculate("1 +", &res);
	PRINT_TEST(CALC_SYNTAX_ERROR, status, "%d");

	status = Calculate("(1 + 1", &res);
	PRINT_TEST(CALC_SYNTAX_ERROR, status, "%d");

	status = Calculate("1 + 1) + 2", &res);
	PRINT_TEST(CALC_SYNTAX_ERROR, status, "%d");

	status = Calculate("(1 + 3) + -(2 + 8 ^ 2)", &res);
	PRINT_TEST(CALC_SYNTAX_ERROR, status, "%d");

	status = Calculate("(1+3)+(2+(8^2)", &res);
	PRINT_TEST(CALC_SYNTAX_ERROR, status, "%d");

	status = Calculate("()", &res);
	PRINT_TEST(CALC_SYNTAX_ERROR, status, "%d");

	status = Calculate("() + 1", &res);
	PRINT_TEST(CALC_SYNTAX_ERROR, status, "%d");

	status = Calculate("1 + ()", &res);
	PRINT_TEST(CALC_SYNTAX_ERROR, status, "%d");

	status = Calculate("(1+3)+ -(2+8^2)", &res);
	PRINT_TEST(CALC_SYNTAX_ERROR, status, "%d");

	puts(DEFAULT);
}


void TestNitzan()
{
	char *s1 = "(5+7+8)";
	char *s2 = "5+5+6-4-3+4";
	char *s3 = "5+7/0";
	char *s4 = "(5+4/2+4*1)*(3+2*4/2)";
	char *s5 = "(5+4/2+4*1*((((1+3)+2)/2)))";
	char *s6 = "2^3-1+4^2/4+1";
	char *s7 = "24/2/2+1";
	double res = 0;
	printf(WHITE"*******************************************************\n"DEFAULT);
	printf(WHITE"*******************TEST FOR CALCULATOR*****************\n"DEFAULT);
	printf(WHITE"*******************************************************\n"DEFAULT);


	printf(BLUE"TEST 1- SIMPLE CASE (5+7+8)\n"DEFAULT);
	Calculate(s1,&res);
	if(res == 20)
	{
		printf(GREEN"SUCCES!! should be 20 you got %f%s\n",res,DEFAULT);
	}
	else
	{
		printf(RED"FAILURE!! should be 20 you got %f%s\n",res, DEFAULT);
	}


	printf(BLUE"TEST 2- SIMPLE CASE WITH MINUS (5+5+6-4-3+4)\n"DEFAULT);

	Calculate(s2,&res);
	if(res == 13)
	{
		printf(GREEN"SUCCES!! should be 13 you got %f%s\n",res,DEFAULT);
	}
	else
	{
		printf(RED"FAILURE!! should be 13 you got %f%s\n",res, DEFAULT);
	}


	printf(BLUE"TEST 3- DIVIDE BY ZERO (5+7/0)\n"DEFAULT);
	res = 0;
	Calculate(s3,&res);
	if(res == 0)
	{
		printf(GREEN"SUCCES!! should be 0 you got %f%s\n",res,DEFAULT);
	}
	else
	{
		printf(RED"FAILURE!! should be 0 you got %f%s\n",res, DEFAULT);
	}

	printf(BLUE"TEST 4- parenthesis times parenthesis (5+4/2+4*1)*(3+2*4/2)\n"DEFAULT);
	res = 0;
	Calculate(s4,&res);
	if(res == 77)
	{
		printf(GREEN"SUCCES!! should be 77 you got %f%s\n",res,DEFAULT);
	}
	else
	{
		printf(RED"FAILURE!! should be 77 you got %f%s\n",res, DEFAULT);
	}

	printf(BLUE"TEST 5- parenthesis in parenthesis (5+4/2+4*1*((((1+3)+2)/2)))\n"DEFAULT);
	res = 0;
	Calculate(s5,&res);
	if(res == 19)
	{
		printf(GREEN"SUCCES!! should be 19 you got %f%s\n",res,DEFAULT);
	}
	else
	{
		printf(RED"FAILURE!! should be 19 you got %f%s\n",res, DEFAULT);
	}

	printf(BLUE"TEST 6- simple power 2^3-1+4^2/4+1\n"DEFAULT);
	res = 0;
	Calculate(s6,&res);
	if(res == 12)
	{
		printf(GREEN"SUCCES!! should be 20 you got %f%s\n",res,DEFAULT);
	}
	else
	{
		printf(RED"FAILURE!! should be 20 you got %f%s\n",res, DEFAULT);
	}

	printf(BLUE"TEST 7- division in division 24/2/2+1\n"DEFAULT);
	res = 0;
	Calculate(s7,&res);
	if(res == 7)
	{
		printf(GREEN"SUCCES!! should be 7 you got %f%s\n",res,DEFAULT);
	}
	else
	{
		printf(RED"FAILURE!! should be 7 you got %f%s\n",res, DEFAULT);
	}


}
