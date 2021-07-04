#include <stdio.h>/*Required for standard input ouput*/
#include <assert.h>/*Required for assert function*/
#include <stdlib.h>/*Required for dynamic memory allocation functions*/
#include "dynamic_vector.h"/*Required for our library functions*/

void TestDynamicVector();

int main()
{
	TestDynamicVector();
	return 0;
}


void TestDynamicVector()
{

    int a = 987;
    char b = 'b';
    float f = -124.3;
    void *ptr = &f;
    
    dynamic_vector_t *test_vector = DynamicVectorCreate( 10 );
    
    printf ("\033[34;1mDynamicVectorCreate - TEST\033[0m \n");/*blue msg*/	
	printf("Get size - %lu expected size - %d\n", DynamicVectorGetSize(test_vector), 0);
	printf("Get capaciry - %lu expected capacity - %d\n", DynamicVectorGetCapacity(test_vector), 10);       
    if(test_vector && DynamicVectorGetSize(test_vector) == 0 && DynamicVectorGetCapacity(test_vector) == 10 )
    {
    	printf("\033[32;1mSUCCESS \033[0m\n");
    }
    else
    {
    	printf("\033[31;1mFAILED \033[0m\n");
    }
    
    DynamicVectorPushBack( test_vector, &a );
    DynamicVectorPushBack( test_vector, &b );
    DynamicVectorPushBack( test_vector, &f );
    DynamicVectorPushBack( test_vector, &ptr);  
    DynamicVectorPushBack( test_vector, &f );
    DynamicVectorPushBack( test_vector, &ptr);
    DynamicVectorPushBack( test_vector, &f );
    DynamicVectorPushBack( test_vector, &ptr);
    DynamicVectorPushBack( test_vector, &f );
    DynamicVectorPushBack( test_vector, &ptr);
    DynamicVectorPushBack( test_vector, &ptr);
    
    printf ("\033[34;1mDynamicVectorPushBack - TEST\033[0m \n");/*blue msg*/	
    printf("Get size - %lu expected size - %d\n", DynamicVectorGetSize(test_vector), 11);
	printf("Get capaciry - %lu expected capacity - %d\n", DynamicVectorGetCapacity(test_vector), 20);     
    if(DynamicVectorGetCapacity(test_vector) == 20 && DynamicVectorGetSize(test_vector) == 11)
    {
    	printf("\033[32;1mSUCCESS \033[0m\n");
    }
    else
    {
    	printf("\033[31;1mFAILED \033[0m\n");
    }
    
    DynamicVectorPopBack(test_vector);
    DynamicVectorPopBack(test_vector);
    DynamicVectorPopBack(test_vector);
    DynamicVectorPopBack(test_vector);
    
    
    printf ("\033[34;1mDynamicVectorPopBack - TEST\033[0m \n");/*blue msg*/	
    printf("Get size - %lu expected size - %d\n", DynamicVectorGetSize(test_vector), 7);
	printf("Get capaciry - %lu expected capacity - %d\n", DynamicVectorGetCapacity(test_vector), 20);   
    if(DynamicVectorGetCapacity(test_vector) == 20 && DynamicVectorGetSize(test_vector) == 7)
    {
    	printf("\033[32;1mSUCCESS \033[0m\n");
    }
    else
    {
    	printf("\033[31;1mFAILED \033[0m\n");
    }
    
   
    DynamicVectorShrinkToFit( test_vector);
    printf ("\033[34;1mDynamicVectorShrinkToFit - TEST\033[0m \n");/*blue msg*/	
    printf("Get size - %lu expected size - %d\n", DynamicVectorGetSize(test_vector), 7);
	printf("Get capaciry - %lu expected capacity - %d\n", DynamicVectorGetCapacity(test_vector), 7); 
    if(DynamicVectorGetCapacity(test_vector) == 7 && DynamicVectorGetSize(test_vector) == 7)
    {
    	printf("\033[32;1mSUCCESS \033[0m\n");
    }
    else
    {
    	printf("\033[31;1mFAILED \033[0m\n");
    }
    
    DynamicVectorReserve( test_vector, 20 );
    
    printf ("\033[34;1mDynamicVectorReserve/GetSize/GetCapacity - TEST\033[0m \n");/*blue msg*/	
    printf("Get size - %lu expected size - %d\n", DynamicVectorGetSize(test_vector), 7);
	printf("Get capaciry - %lu expected capacity - %d\n", DynamicVectorGetCapacity(test_vector), 20); 
    if(DynamicVectorGetCapacity(test_vector) == 20 && DynamicVectorGetSize(test_vector) == 7)
    {
    	printf("\033[32;1mSUCCESS \033[0m\n");
    	printf("\033[32;1mSUCCESS \033[0m\n");
    	printf("\033[32;1mSUCCESS \033[0m\n");
    }
    else
    {
    	printf("\033[31;1mFAILED \033[0m\n");
    	printf("\033[31;1mFAILED \033[0m\n");
    	printf("\033[31;1mFAILED \033[0m\n");
    }
    
    DynamicVectorSetAt( test_vector ,3, 0);
    printf ("\033[34;1mDDynamicVectorGetAt/SetAt - TEST\033[0m \n");/*blue msg*/	
    /*printf("Get at - %lu expected at - %d\n", DynamicVectorGetAt( test_vector , 3), 0);*/
    if(DynamicVectorGetAt( test_vector , 3) == 0)
    {
     	printf("\033[32;1mSUCCESS \033[0m\n");
     	printf("\033[32;1mSUCCESS \033[0m\n");
    }
    else
    {
    	printf("\033[31;1mFAILED \033[0m\n");
    	printf("\033[31;1mFAILED \033[0m\n");
    }
   
    DynamicVectorPopBack(test_vector);
    DynamicVectorPopBack(test_vector);
    DynamicVectorPopBack(test_vector);
    DynamicVectorPopBack(test_vector);

    DynamicVectorSetAll( test_vector , NULL);
    if(DynamicVectorGetAt( test_vector , 0) == NULL && DynamicVectorGetAt( test_vector , 1) == NULL && DynamicVectorGetAt( test_vector , 2) == NULL)
    {
        printf("\033[32;1mDynamicVectorSetAll SUCCESS \033[0m\n");
    }
    else
    {
        printf("\033[31;1mDynamicVectorSetAll FAILED \033[0m\n");
    }
     
    
    
    DynamicVectorDestroy(test_vector );
    printf ("\033[34;1m--------END--------\033[0m \n");/*blue msg*/	
}
