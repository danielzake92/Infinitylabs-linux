/****************************************************************************
* FILE: hash_table.h		     PURPOSE: Define Hash Table Data Strucuture
*
* DEVELOPER: Daniel Zaken		 TEAM: Green
*
* REVIEWER:  Yael Koenig  	  	 STATUS: Review
*
****************************************************************************/

#ifndef __ILRD_HASH_TABLE_H__
#define __ILRD_HASH_TABLE_H__

/*****************************************************************************/
/************* Preprocessor Definitions and Header Includes ******************/
/*****************************************************************************/

#include <stddef.h> /* size_t */

#include "doubly_linked_list.h" /* doubly linked list API */

/*****************************************************************************/
/***************** Struct Definitions and Typedefs ***************************/
/*****************************************************************************/

typedef size_t(*hash_func_t)(const void *data, size_t table_size);

typedef int(*op_func_t)(void *key, void *param);

 /*1 == true, 0 = is false*/
typedef int(*is_match_t)(const void *lhs, const void *rhs);

typedef struct hash_table ht_t;


/*****************************************************************************/
/***************** API Function Declarations *********************************/
/*****************************************************************************/

/*
Description: Creates new empty Hash Table. and stores hash func, 
is_match_func and table size.
Parameters: 
    -hash_func: hash table hash function
    -match_func: function that defines a match in between data held in 
    table
    -table_size: size of table to be created
Return Value: pointer to new hash table
Time Complexity: O(1)
*/

ht_t *HTCreate(hash_func_t hash_func, is_match_t match_func, size_t table_size); 

/****************************************************************************/
/*
Description: Function to destroy a Hash Table.
Parameters:
    -table: pointer to hash table data structure
Return Value: N/A
Time Complexity: O(n), where n is the number of elements stored in table
*/
void HTDestroy(ht_t *table);

/****************************************************************************/
/*
Description: Inserts data into table
Parameters:
    -table: pointer to Hash Table data structure
    -data: data to be inserted into table
Return Value: (0) in case of success, and (1) in case of failure
Time Complexity: average O(1)
*/
int HTInsert(ht_t *table, const void *data);

/****************************************************************************/
/*
Description: Removes requested data.
Parameters:
    -table: pointer to hash table data structure
    -data: data to be removed from table
Return Value: N/A
Time Complexity: average O(1)
*/
void HTRemove(ht_t *table, const void *data);

/****************************************************************************/
/*
Description: Retrive data stored within the table, 
using a unique key to find data.
Parameters: 
    -table: pointer to hash table data structure
    -data: data containing same key as data to be found
Return Value: Pointer to the data including all related information.	
Time Complexity: average O(1)
*/
void *HTFind(const ht_t *table, const void *data);

/****************************************************************************/
/*
Description: calculates the number of elements held in table
Parameters:
    -table: pointer to Hash Table data structure
Return Value: number of elements held in table
Time Complexity: O(n)
*/
size_t HTSize(const ht_t *table);

/****************************************************************************/
/*
Description: Checks if Hash Table is empty.
Parameters:
    -table: pointer to hash table data structure
Return Value: Boolian Function, Returns 1 if Hash Table is empty otherwise 0. 	
Time Complexity: O(size_of_table)
*/
int HTIsEmpty(const ht_t *table);

/****************************************************************************/
/*
Description: Applies callback function to each data held in table entries. 
HTForEach will stop if callback function returns a non-zero value.
Parameters:
    -table: pointer to hash table data structure
    -callback: function to be applied to each element
    -params: parameter fed to callback during each execution
Return Value: value returned by callback during its last execution
Time Complexity: O(n)
*/
int HTForEach(ht_t *table, op_func_t callback, void *params);

/****************************************************************************/
/*
Description: Calculates Load Factor of Hash Table
Parameters:
    -table: pointer to hash table data structure
Return Value: Load Factor of table
Time Complexity: O(table_size)
*/
double HTLoadFactor(ht_t *table);

/****************************************************************************/
/*
Description: Calculates Standard Deviation of Hash Table
Parameters:
    -table: pointer to hash table data structure
Return Value: Standard Deviation of distribution of elements in table
Time Complexity: O(n)
*/
double HTStandardDeviation(const ht_t *table);

/****************************************************************************/

#endif