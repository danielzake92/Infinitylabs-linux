/****************************************************************************
* FILE: calculator.c  Purpose: library for calculator
*
* DEVELOPER:   Daniel Zaken				TEAM: Green
*
* REVIEWER:    Elizabeta				STATUS: Approved
*
****************************************************************************/
#include <stdlib.h> /*for strtod and malloc functions*/
#include <assert.h> /*asserts*/
#include <ctype.h> /* isdigit, isalpha*/
#include <string.h> /*strlen*/
#include <stdio.h>

#include "calculator.h" /*my current lib*/
#include "stack.h"

#define STATES 4
#define KEYS 128

typedef enum calc_states
{
	WAIT_FOR_NUM = 0,
	WAIT_FOR_OP = 1,
	CALC_FAILURE = 2,
	DONE = 3
}calc_states_t;

static union converter
{
	void *v;
	double d;
	char c;
}g_converter;

static double VtoD(void *data);
static void* DtoV(double data);

static char VtoC(void *data);
static void* CtoV(char data);
/****************************************************************************/


/*
Math functions
*/
static calc_status_t Add(double left,double right, double *res);
static calc_status_t Subtract(double left,double right, double *res);
static calc_status_t Multiply(double left,double right, double *res);
static calc_status_t Divide(double left,double right, double *res);
static calc_status_t Pow(double base,double exp, double *res);
/*math function typedef*/
typedef calc_status_t(*math_func_t)(double left,double right, double *res);
/*
An operation function which takes the last operator in the
s_operator and operates it with the two last operands #include
s_operand stack
*/
static calc_status_t Operate(stack_t *s_operator,stack_t *s_operand);

/*
State function which invokes when i wait for an operation
works with all ops but the power one.
both functions these and the power one check if the
prev operator has higer precedence than the cur operator
if does it operate the previous operation
*/
static calc_states_t InWaitForOp(calc_states_t cur_state,calc_status_t *status,
	 				stack_t *s_operator, stack_t *s_operand, char **math_exp);
/*
Special state function for power operation
*/
static calc_states_t InWaitForOpPow(calc_states_t cur_state,calc_status_t *status,
	 				stack_t *s_operator, stack_t *s_operand, char **math_exp);
/*
State function for waiting to number, uses strtod
*/
static calc_states_t InWaitForNum(calc_states_t cur_state,calc_status_t *status,
					stack_t *s_operator, stack_t *s_operand, char **math_exp);
/*
State function for spacing in case of space detection
*/
static calc_states_t Space(calc_states_t cur_state,calc_status_t *status,
					stack_t *s_operator, stack_t *s_operand, char **math_exp);
/*
State function for open paranthesis
*/
static calc_states_t ParanOpen(calc_states_t cur_state,calc_status_t *status,
					stack_t *s_operator, stack_t *s_operand, char **math_exp);
/*
State function for close paranthesis
*/
static calc_states_t ParanClose(calc_states_t cur_state,calc_status_t *status,
					stack_t *s_operator, stack_t *s_operand, char **math_exp);
/*
State function to indicate that the forward traverse is done
*/
static calc_states_t Done(calc_states_t cur_state,calc_status_t *status,
					stack_t *s_operator, stack_t *s_operand, char **math_exp);
/*
State function to move us to error state and also changes status to syntax_error
*/
static calc_states_t SyntaxError(calc_states_t cur_state,calc_status_t *status,
					stack_t *s_operator, stack_t *s_operand, char **math_exp);

/*State function typedef*/
typedef calc_states_t (*state_func_t)(calc_states_t cur_state,calc_status_t *status,
					stack_t *operator_stack, stack_t *operand_stack, char **math_exp);

static void InitLut(void);

/*LUTS*/
static state_func_t g_states_lut[STATES][KEYS] = {NULL};
static math_func_t g_op_lut['^' + 1] = {NULL}; /*'^' = 94*/
static unsigned char g_precedence_lut['^' + 1] = {0};

/****************************************************************************/
calc_status_t Calculate(const char *math_expression, double *result)
{
	size_t len = 0;
	stack_t *s_operator = NULL;
	stack_t *s_operand = NULL;
	calc_states_t cur_state = WAIT_FOR_NUM;
	calc_status_t status = CALC_SUCCESS;
	char *runner = (char*)math_expression;

	assert(math_expression);
	assert(result);

	*result = 0;

	len = strlen(math_expression);

	/*creation of operator stack*/
	s_operator = StackCreate(len);
	if( NULL == s_operator )
	{
		return CALC_ALLOC_ERROR;
	}

	/*creation of operand stack*/
	s_operand = StackCreate(len);
	if( NULL == s_operand )
	{
		StackDestroy(s_operator);
		return CALC_ALLOC_ERROR;
	}

	InitLut();

	/*forward running with evaluation*/
	while( DONE != cur_state && CALC_FAILURE != cur_state )
	{
		cur_state = g_states_lut[cur_state][(int)(*runner)]
							(cur_state,&status, s_operator, s_operand, &runner);
	}
	/*stus ended check*/
	if( CALC_FAILURE == cur_state )
	{
		StackDestroy(s_operator);
		StackDestroy(s_operand);
		return status;
	}
	/*backwerds evaluation*/
	while( !StackIsEmpty(s_operator) && CALC_SUCCESS == status )
	{
		if( '(' == VtoC(StackPeek(s_operator)) )
		{
			StackDestroy(s_operator);
			StackDestroy(s_operand);
			return CALC_SYNTAX_ERROR;
		}

		status = Operate(s_operator, s_operand);
	}
	/*get the valid result*/
	*result = VtoD(StackPeek(s_operand));

	StackDestroy(s_operator);
	StackDestroy(s_operand);
	return status;
}
/****************************************************************************/
static void InitLut(void)
{
	int i = 0;
	int j = 0;

	g_op_lut['+'] = Add;
    g_op_lut['-'] = Subtract;
    g_op_lut['*'] = Multiply;
    g_op_lut['/'] = Divide;
    g_op_lut['^'] = Pow;

	g_precedence_lut['+'] = 1;
    g_precedence_lut['-'] = 1;
    g_precedence_lut['*'] = 2;
    g_precedence_lut['/'] = 2;
    g_precedence_lut['^'] = 3;

	for(i = 0; i < STATES; ++i )
	{
		for(j = 0; j < KEYS; ++j)
		{
			g_states_lut[i][j] = SyntaxError;
		}
	}

	g_states_lut[WAIT_FOR_NUM]['('] = ParanOpen;
	g_states_lut[WAIT_FOR_NUM][' '] = Space;
	g_states_lut[WAIT_FOR_NUM]['-'] = InWaitForNum;
	g_states_lut[WAIT_FOR_NUM]['+'] = InWaitForNum;
	g_states_lut[WAIT_FOR_NUM]['\0'] = SyntaxError;
	g_states_lut[WAIT_FOR_NUM][')'] = SyntaxError;

	/*waiting for num table*/
	for(i = '0' ; i <= '9'; ++i)
	{
		g_states_lut[WAIT_FOR_NUM][i] = InWaitForNum;
	}


	/*waiting for operation table*/
	g_states_lut[WAIT_FOR_OP]['+'] = InWaitForOp;
	g_states_lut[WAIT_FOR_OP]['-'] = InWaitForOp;
	g_states_lut[WAIT_FOR_OP]['*'] = InWaitForOp;
	g_states_lut[WAIT_FOR_OP]['/'] = InWaitForOp;
	g_states_lut[WAIT_FOR_OP]['^'] = InWaitForOpPow;
	g_states_lut[WAIT_FOR_OP]['('] = SyntaxError;

	g_states_lut[WAIT_FOR_OP][')'] = ParanClose;
	g_states_lut[WAIT_FOR_OP][' '] = Space;
	g_states_lut[WAIT_FOR_OP]['\0'] = Done;

}
/****************************************************************************/
/*************************STATE FUNCTIONS************************************/
/****************************************************************************/
static calc_states_t InWaitForOp(calc_states_t cur_state,calc_status_t *status,
	 				stack_t *s_operator, stack_t *s_operand, char **math_exp)
{
	char cur_operator = 0;
	char prev_operator = 0;
	(void)cur_state;
	assert(s_operand);
	assert(s_operator);
	assert(math_exp);

	cur_operator = **math_exp;

	if( !StackIsEmpty(s_operator) )
	{
		prev_operator = (VtoC(StackPeek(s_operator)));

		while(g_precedence_lut[(int)prev_operator] >=
		 		g_precedence_lut[(int)cur_operator] &&
				!StackIsEmpty(s_operator) )
		{
		    *status = Operate(s_operator, s_operand);
		    if( CALC_SUCCESS != *status)
		    {
		        return CALC_FAILURE;
		    }

			if( !StackIsEmpty(s_operator) )
			{
				prev_operator = (VtoC(StackPeek(s_operator)));
			}
		}
	}
	StackPush(s_operator, CtoV(cur_operator));

	++(*math_exp);

	return WAIT_FOR_NUM;
}
/****************************************************************************/
static calc_states_t InWaitForOpPow(calc_states_t cur_state,calc_status_t *status,
	 					stack_t *s_operator, stack_t *s_operand, char **math_exp)
{
	char cur_operator = 0;
	char prev_operator = 0;
	(void)cur_state;
	assert(s_operand);
	assert(s_operator);
	assert(math_exp);

	cur_operator = **math_exp;

	if( !StackIsEmpty(s_operator) )
	{
		prev_operator = (VtoC(StackPeek(s_operator)));

		if(g_precedence_lut[(int)prev_operator] > g_precedence_lut[(int)cur_operator] )
		{
		    *status = Operate(s_operator, s_operand);
		    if( CALC_SUCCESS != *status)
		    {
		        return CALC_FAILURE;
		    }
		}
	}

	StackPush(s_operator, CtoV(cur_operator));

	++(*math_exp);

	return WAIT_FOR_NUM;
}
/****************************************************************************/
static calc_states_t InWaitForNum(calc_states_t cur_state,calc_status_t *status,
						stack_t *s_operator, stack_t *s_operand, char **math_exp)
{
	double num = 0;
	char *end = NULL;

	assert(s_operand);
	assert(s_operator);
	assert(math_exp);
	(void)status;
	(void)s_operator;

	num = strtod(*math_exp, &end);

	if( end == *math_exp )
	{
		*status = CALC_SYNTAX_ERROR;
		return CALC_FAILURE;
	}

	*math_exp = end;
	StackPush(s_operand, DtoV(num));

	cur_state = WAIT_FOR_OP;

	return cur_state;
}
/****************************************************************************/
static calc_states_t SyntaxError(calc_states_t cur_state,calc_status_t *status,
						stack_t *s_operator, stack_t *s_operand, char **math_exp)
{
	(void)s_operator;
	(void)s_operand;
	(void)math_exp;
	(void)cur_state;
	*status = CALC_SYNTAX_ERROR;

	return CALC_FAILURE;
}
/****************************************************************************/
static calc_states_t Done(calc_states_t cur_state,calc_status_t *status,
				stack_t *s_operator, stack_t *s_operand, char **math_exp)
{
	(void)s_operator;
	(void)s_operand;
	(void)math_exp;
	(void)cur_state;
	(void)status;

	if( WAIT_FOR_NUM == cur_state )
	{
		*status = CALC_SYNTAX_ERROR;
		return CALC_FAILURE;
	}

	return DONE;
}
/****************************************************************************/
static calc_states_t Space(calc_states_t cur_state,calc_status_t *status,
				stack_t *s_operator, stack_t *s_operand, char **math_exp)
{
	(void)s_operator;
	(void)s_operand;
	(void)math_exp;
	(void)status;

	++(*math_exp);

	return cur_state;
}
/****************************************************************************/
static calc_states_t ParanOpen(calc_states_t cur_state,calc_status_t *status,
					stack_t *s_operator, stack_t *s_operand, char **math_exp)
{
	assert(s_operand);
	assert(s_operator);
	assert(math_exp);

	(void)status;
	(void)s_operand;

	StackPush(s_operator, CtoV(**math_exp));

	++(*math_exp);

	cur_state = WAIT_FOR_NUM;
	return cur_state;
}
/****************************************************************************/
static calc_states_t ParanClose(calc_states_t cur_state,calc_status_t *status,
					stack_t *s_operator, stack_t *s_operand, char **math_exp)
{
	assert(s_operand);
	assert(s_operator);
	assert(math_exp);

	while( !StackIsEmpty(s_operator) && '(' != VtoC(StackPeek(s_operator)) )
	{
		*status = Operate(s_operator, s_operand);
		if( *status != CALC_SUCCESS )
		{
			return CALC_FAILURE;
		}
	}

	if( StackIsEmpty(s_operator) )
	{
		*status = CALC_SYNTAX_ERROR;
		return CALC_FAILURE;
	}

	StackPop(s_operator);

	++(*math_exp);

	cur_state = WAIT_FOR_OP;
	return cur_state;
}
/****************************************************************************/
/*************************CALC FUNCTIONS WITH status RETURNED****************/
/****************************************************************************/
static calc_status_t Add(double left,double right, double *res)
{
	assert(res);

	*res = left + right;
	return CALC_SUCCESS;
}
/****************************************************************************/
static calc_status_t Subtract(double left,double right, double *res)
{
	assert(res);

	*res = left - right;
	return CALC_SUCCESS;
}
/****************************************************************************/
static calc_status_t Multiply(double left,double right, double *res)
{
	assert(res);

	*res = left * right;
	return CALC_SUCCESS;
}
/****************************************************************************/
static calc_status_t Divide(double left,double right, double *res)
{
	assert(res);

	if ( 0 == right )
	{
		return CALC_MATH_ERROR;
	}

	*res = left / right;
	return CALC_SUCCESS;
}
/****************************************************************************/
static calc_status_t Pow(double base,double exp, double *res)
{
	int i = 0;

	assert(res);

	*res = 1;  /*float for negetive exponent*/

	/*if the exponent is negetive we need to inverse base*/
	if(0 > exp)
	{
		exp = -exp;
		base = 1 / base;
	}

	for(i = 0; i < exp; ++i)
	{
		*res *= base;
	}


	return CALC_SUCCESS;
}
/****************************************************************************/
static calc_status_t Operate(stack_t *s_operator,stack_t *s_operand)
{
	double left = 0;
	double right = 0;
	double res = 0;
	calc_status_t status = 0;
	char operator = 0;

	assert(s_operator);
	assert(s_operand);

	right = VtoD(StackPeek(s_operand));
	StackPop(s_operand);

	left = VtoD(StackPeek(s_operand));
	StackPop(s_operand);

	operator = VtoC(StackPeek(s_operator));
	StackPop(s_operator);

	status = g_op_lut[(int)operator](left,right,&res);

	StackPush(s_operand, DtoV(res));
	return status;
}
/****************************************************************************/
/*************************CONVERSION FUNCTIONS*******************************/
/****************************************************************************/
static double VtoD(void *data)
{
	g_converter.v = data;
	return(g_converter.d);
}
static void* DtoV(double data)
{
	g_converter.d = data;
	return(g_converter.v);
}
static char VtoC(void *data)
{
	g_converter.v = data;
	return(g_converter.c);
}
static void* CtoV(char data)
{
	g_converter.c = data;
	return(g_converter.v);
}
