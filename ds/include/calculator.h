
#ifndef __ILRD_CALCULATOR_H__
#define __ILRD_CALCULATOR_H__



typedef enum calc_status
{
	CALC_SUCCESS,
	CALC_SYNTAX_ERROR,
	CALC_MATH_ERROR,
	CALC_ALLOC_ERROR
}calc_status_t;

/* recieves an expression to compute and out parameter for result, returs the status */
calc_status_t Calculate(const char *math_expression, double *result);


#endif /* __ILRD_CALCULATOR_H__ */

/* END OF FILE */
