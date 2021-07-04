/****************************************************************************
* FILE: hash_table.c		     PURPOSE: Define Hash Table Data Strucuture
*
* DEVELOPER: Daniel Zaken		 TEAM: Green
*
* REVIEWER:  Yael Koenig  	  	 STATUS: Review
*
****************************************************************************/
/*INCLUDES*/
#include <assert.h>/*Required for assert function*/
#include <stdlib.h>/*Required for dynamic memory allocation functions*/
#include <stdio.h> /*Required for dynamic memory allocation functions*/
#include <math.h>  /*required for square root*/

#include "doubly_linked_list.h"
#include "hash_table.h"
#include "utl.h"

struct hash_table
{
    dll_t **array;
    hash_func_t hash_func;
    is_match_t is_match_func;
    size_t table_size;
};

/*****************************************************************************/
/*static double SpecialLoadFactor(ht_t *table);*/
/*****************************************************************************/
ht_t *HTCreate(hash_func_t hash_func, is_match_t match_func, size_t table_size)
{
    ht_t *table = NULL;
    int i = 0;

    assert(hash_func);
    assert(match_func);

    table = (ht_t *)malloc(sizeof(ht_t));
    if (NULL == table)
    {
        return NULL;
    }

    table->array = (dll_t **)malloc(sizeof(dll_t *) * table_size);
    if (NULL == table->array)
    {
        free(table);
        return NULL;
    }

    for (i = 0; (size_t)i < table_size; ++i)
    {
        (table->array)[i] = DoublyLinkedListCreate();
        if (NULL == (table->array)[i])
        {
            --i;
            for (; i >= 0; --i)
            {
                DoublyLinkedListDestroy((table->array)[i]);
            }

            free(table->array);
            table->array = NULL;
            free(table);
            return NULL;
        }
    }

    table->hash_func = hash_func;
    table->is_match_func = match_func;
    table->table_size = table_size;

    return table;
}
/*****************************************************************************/
void HTDestroy(ht_t *table)
{
    size_t i = 0;

    assert(table);

    while (table->table_size > i)
    {
        DoublyLinkedListDestroy((table->array)[i]);
        (table->array)[i] = NULL;
        ++i;
    }

    free(table->array);
    table->array = NULL;
    table->hash_func = NULL;
    table->is_match_func = NULL;
    free(table);
}
/*****************************************************************************/
int HTInsert(ht_t *table, const void *data)
{
    size_t index = 0;
    dll_iterator_t node = NULL;
    dll_t *list = NULL;

    assert(table);

    index = (table->hash_func)(data, table->table_size);

    list = (table->array)[index];

    node = DoublyLinkedListPushFront(list, (void *)data);
    if (DoublyLinkedListIsMatchNode(DoublyLinkedListEnd(list), node))
    {
        return FAIL;
    }

    return SUCCESS;
}
/*****************************************************************************/
void HTRemove(ht_t *table, const void *data)
{
    size_t index = 0;
    dll_t *list = NULL;
    dll_iterator_t to_remove = NULL;

    assert(table);

    index = (table->hash_func)(data, table->table_size);
    list = (table->array)[index];

    to_remove = DoublyLinkedListFind(table->is_match_func,
                                     DoublyLinkedListBegin(list),
                                     DoublyLinkedListEnd(list), data);

    DoublyLinkedListRemove(to_remove);
}
/*****************************************************************************/
void *HTFind(const ht_t *table, const void *data)
{
    size_t index = 0;
    dll_t *list = NULL;
    dll_iterator_t to_find = NULL;

    assert(table);

    index = (table->hash_func)(data, table->table_size);
    list = (table->array)[index];

    to_find = DoublyLinkedListFind(table->is_match_func,
                                   DoublyLinkedListBegin(list),
                                   DoublyLinkedListEnd(list), data);

    if (DoublyLinkedListIsMatchNode(DoublyLinkedListEnd(list), to_find))
    {
        return NULL;
    }
    /* cache data at beggining of list if it is not already there */
    DoublyLinkedListSplice(DoublyLinkedListBegin(list),
                           to_find, DoublyLinkedListNext(to_find));

    return DoublyLinkedListGetData(to_find);
}
/*****************************************************************************/
size_t HTSize(const ht_t *table)
{
    size_t count = 0;
    size_t i = 0;

    assert(table);

    while (i < table->table_size)
    {
        count += DoublyLinkedListCount((table->array)[i]);
        ++i;
    }
    return count;
}
/*****************************************************************************/
int HTIsEmpty(const ht_t *table)
{
   assert(table);

   return(0 == HTSize(table));
}
/*****************************************************************************/
int HTForEach(ht_t *table, op_func_t callback, void *params)
{
    size_t i = 0;
    size_t size = 0;
    int status = SUCCESS;
    dll_t *list = NULL;

    assert(table);
    assert(callback);

    size = table->table_size;

    for (; i < size && SUCCESS == status; ++i)
    {
        list = (table->array)[i];
        status = DoublyLinkedListForEach(callback, DoublyLinkedListBegin(list),
                                         DoublyLinkedListEnd(list), params);

        if (SUCCESS != status)
        {
            return status;
        }
    }
    return status;
}
/*****************************************************************************/
double HTLoadFactor(ht_t *table)
{
    assert(table);

    return ((double)HTSize(table) / (double)(table->table_size));
}  
/*****************************************************************************/
double HTStandardDeviation(const ht_t *table)
{
    size_t i = 0;
    double avg = 0.0;
    double x_i = 0.0;
    double sum = 0.0;

    assert(table);

    avg = (double)HTSize(table) / (double)(table->table_size);

    for (; i < table->table_size; ++i)
    {
        x_i = DoublyLinkedListCount((table->array)[i]);
        sum += pow(x_i - avg, 2.0);
    }
    sum /= (double)(table->table_size);
    return sqrt(sum);
}
/*****************************************************************************/
#if 0
static double SpecialLoadFactor(ht_t *table)
{
    size_t count_full = 0;
    size_t i = 0;

    assert(table);

    for( ; i < table->table_size; ++i)
    {
        count_full += ( FALSE == DoublyLinkedListIsEmpty((table->array)[i]));
    }

    return ((double)count_full / (double)(table->table_size));

}
#endif
