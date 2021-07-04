/****************************************************************************
 *  FILENAME:  Structs.h   NAME:  Daniel Zaken    REVIEWER:   Nitzan Holems * 
 *                                                                          *
 *  POURPOSE:  Create LIB for mixed array types such as int float and       *
 *             strings                                                      *
 ****************************************************************************/
#ifndef __ILRD_STRUCTS_H__
#define __ILRD_STRUCTS_H__
/****************************************************************************/
/*Typedef describing error codes and return status of different functions of array*/
typedef enum status
{
    SUCCESS,
    ADD_INT_ERR,
    ADD_STRING_ERR,
    ADD_FLOAT_ERR,
    INITIALIZE_STRING_ERR,
    ALLOCATE_ERR
}status_t;
/* typedef and definition of struct which introduces multiple data-type 
functionality to the array, having both the data contained in a void 
pointer and functions to be applied depending on the data type */
typedef struct element element_t;

struct element
{
    void *data;
	status_t (*add)(element_t *element, int val);
    void (*print)(const element_t *element);
    void (*free_data)(element_t *element);
};

/***********************Initialization Functions*****************************/

/* Initializes elements of array to contain int */
void InitilizeInt(element_t *element, int val); 
/* Initializes elements of array to contain float */
void InitilizeFloat(element_t *element, float val);
/* Initializes elements of array to contain string */
status_t InitilizeString(element_t *element, const char *val);

/***********************Addition Functions*****************************/

/* Adds ints to int elements in array arithmetically */
status_t AddInt(element_t *element, int val);
/* Adds ints to float elements in array arithmetically */
status_t AddFloat(element_t *element, int val);
/* Adds ints to string elements in array by concatenation */
status_t AddString(element_t *element, int val);

/***********************print Functions*****************************/

/* Prints float elements to standard output */
void PrintFloat(const element_t *element);
/* Prints int elements to standard output */
void PrintInt(const element_t *element);
/* Prints string elements to standard output */
void PrintString(const element_t *element);

/***********************Freeing Functions*****************************/

/* Frees dynamically allocated string memory */
void FreeString(element_t *element);
/* Does nothing, exists to ensure function pointer for
freeing function in ints and floats is not null */
void Free(element_t *element);

#endif
