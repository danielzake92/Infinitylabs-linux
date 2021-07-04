/****************************************************************************
* FILE: cpp2c_test.c	            PURPOSE: Coding cpp in c
*
* DEVELOPER: Daniel Zaken						
*
* REVIEWER: Elizabeta				STATUS: Aproved
*
*
****************************************************************************/
#include <stdio.h> //printf
#include <stdlib.h> //malloc
#include "cpp2c.h" //implemented lib for oop in c


int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    (void)envp;

    mb_t m;
    CtorMB(&m);

    print_infoRMB(&m);

    pt_t temp_copy = print_infoI(3);
    DisplayPT(&temp_copy);
    DtorPT(&temp_copy);

    {//Polymorphism starts
        int i = 0;
        pt_t *array[3];

        array[0] = malloc(sizeof(mb_t));
        CtorMB((mb_t*)array[0]);

        array[1] = malloc(sizeof(tx_t));
        CtorTX((tx_t*)array[1]);

        array[2] = malloc(sizeof(mb_t));
        CtorMB((mb_t*)array[2]);

        for(i = 0; i < 3; ++i)
        {
            ((pt_vtbl_t*)(array[i]->vptr))->display(array[i]);
        }

        for(i = 0; i < 3; ++i)
        {
            ((pt_vtbl_t*)(array[i]->vptr))->dtor(array[i]);
            free(array[i]);
        }
    }//Polymorphism ends

    pt_t arr2[3];
    
    {//Traverse by value starts
        int i = 0;

        mb_t mb_temp;
        CtorMB(&mb_temp);

        CctorPT((pt_t*)arr2, &mb_temp.pt);
        DtorMB(&mb_temp);

        tx_t tx_temp;
        CtorTX(&tx_temp);
        CctorPT((pt_t*)(arr2 + 1), &tx_temp.pt);
        DtorTX(&tx_temp);

        CtorPT(arr2 + 2);

        for( i = 0; i < 3; ++i)
        {
            DisplayPT(arr2 + i);
        }

    }//Traverse by value ends

    print_infoRPT(arr2);
    PrintCountPT();


    mb_t m2;
    CtorMB(&m2);

    PrintCountPT();    


    mb_t arr3[4];

    int i = 0;
    for(i = 0; i < 4; ++i)
    {
        CtorMB(arr3 + i);
    }

    tx_t *arr4 = (tx_t*)malloc(sizeof(tx_t) * 4 + sizeof(size_t));
    *((size_t*)arr4) = 4;
    
    for(i = 0; i < 4; ++i)
    {
        CtorTX( ((tx_t*)((size_t*)arr4 + 1)) + i);
    }

    for(i = *((size_t*)arr4) - 1; 0 <= i; --i)
    {
        ((tx_vtbl_t*)((((tx_t*)((size_t*)arr4 + 1))[i].pt).vptr))->
        dtor(((tx_t*)((size_t*)arr4 + 1)) + i);
    }
    free(arr4);

    printf("%d\n%d\n",IMax(1,2),IMax(1, (int)2.0f));

    stx_t st;
    CtorSTX(&st);

    tx_t tx_temp;
    CctorTX(&tx_temp,&st.tx );
    taxi_displayTX(tx_temp);
    DtorTX(&tx_temp);
    
    {//destruction part
        DtorSTX(&st);

        for(i = 3; 0 <= i; --i)
        {
            DtorMB(arr3 + i);
        }

        DtorMB(&m2);

        for( i = 2; 0 <= i; --i)
        {
            ((pt_vtbl_t*)(arr2[i].vptr))->dtor(arr2 + i);
        }

        DtorMB(&m);
    }//end of destruction part

    return 0;
}