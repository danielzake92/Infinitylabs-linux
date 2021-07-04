/****************************************************************************
 *  FILENAME:  Structs.C   NAME:  Daniel Zaken    REVIEWER:  Nitzan Holems  *
 *                                                                          *
 *  POURPOSE:  Create LIB for mixed array types such as int float and       *
 *             strings                                                      *
 ****************************************************************************/
/*INCLUDES*/
#include <stdio.h> /*printf required*/
#include "structs.h" /*header decleration required*/
#include <assert.h> /*assert required*/
#include <string.h> /*strcpy required*/
#include <stdlib.h> /*realloc required*/
/*DEFINE*/
#define SIZE 11 /*integer max size*/
/****************************INT*******************************/
/*************************************************************/

static int HowManyDigits (int num);

void InitilizeInt(element_t *element, int val)
{	
	assert(element);
	
	element->data = (void*)( (size_t)val );
	element->add = AddInt;
	element->print = PrintInt;
	element->free_data = Free;
}

void PrintInt(const element_t *element)
{	
	assert(element);
	printf("%d\n", (int)((size_t)element->data));
}

status_t AddInt(element_t *element, int val)
{	
	int temp = 0;
	
	assert(element);
	
	temp = (int)((size_t)element->data) + val;
	element->data = (void*)( (size_t)temp );
	
	return SUCCESS;
}

/***************************FLOAT******************************/
/*************************************************************/
void InitilizeFloat(element_t *element, float val)
{	
	assert(element);
	element->data =  (void*)(*(size_t*)(&val));
	element->add = AddFloat;
	element->print = PrintFloat;
	element->free_data = Free;
}


void PrintFloat(const element_t *element)
{	
	size_t temp = 0;
	assert(element);
				
	temp = (size_t)element->data;
	printf("%f\n", *((float*)&temp));
}	

status_t AddFloat(element_t *element, int val)
{
	size_t t_temp = 0;
	float f_temp = 0;
	
	assert(element);
	
	t_temp = (size_t)element->data;
	f_temp = *((float*)&t_temp) + val;
	
	element->data = (void*)(*(size_t *)(&f_temp)) ;
	
	return SUCCESS;
}

void Free(element_t *element)
{	
	assert(element);
	(void)element;
}

/*************************STRING******************************/
/*************************************************************/
status_t InitilizeString(element_t *element, const char *val)
{
	assert(element);
	assert(val);
		
	element->data = malloc( ( strlen(val) + 1 ) * sizeof(char) );
	
	if( !element->data )
	{
		return ALLOCATE_ERR;
	}
	
	if ( (strcpy(element->data, (void*)val)) == NULL) 
	{
		return INITIALIZE_STRING_ERR;
	}
		
	element->add = AddString;
	element->print = PrintString;
	element->free_data = FreeString;
	
	return SUCCESS;
}

void PrintString(const element_t *element)
{
	assert(element);
	printf("%s\n", (char*)element->data);	
}

status_t AddString(element_t *element, int val)
{
	/*New size for string reallocation*/
	int len = strlen(element->data) + HowManyDigits(val) + 1 ;
	/*buffer for int max SIZE = 9*/
	char buffer[SIZE] = "";
	
	assert(element);
	
	element->data = realloc( element->data, ( len * sizeof(char) ));
	
	if( !element->data )
	{
		return ALLOCATE_ERR;
	}
	/*inserting int to buffer as string*/
	if ( ( sprintf(buffer, "%d", val) ) < 0 )
	{
		return INITIALIZE_STRING_ERR;
	}
	/*concatinating the new int string to the old string*/
	if ( (strcat(element->data, (void*)buffer)) == NULL) 
	{
		return INITIALIZE_STRING_ERR;
	}	
		
	return SUCCESS;
}

void FreeString(element_t *element)
{	
	assert(element);
	free( element->data );
	element->data = NULL;
}

static int HowManyDigits (int num)
{
	int count = 0;
	
	while(num)
	{
		++count;
		num /= 10;
	}
	return count;	
}



