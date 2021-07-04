/*****************************************************************************
* FILE:      knights_tour.h	           PURPOSE: API for knight's tour        
* DEVELOPER: Daniel Zaken              TEAM:    Green                       
*                                                                               
* REVIEWER:  Dor Eini                  STATUS: Imp tested                          
******************************************************************************/

#ifndef __ILRD_KNIGHTS_TOUR_H__
#define __ILRD_KNIGHTS_TOUR_H__

#include <time.h>   /*time*/
#include <stddef.h> /*size_t*/
#include "bitarray.h" /*ds to use*/

#define ROW_NUM 8
#define BOARD_SIZE ROW_NUM * ROW_NUM

typedef enum status
{
    SUCCESS = 0,
    FAIL_TIMEOUT = 1,
    ALLOC_ERROR = 2,
    NUM_OF_STATUS = 3
} status_t;

typedef enum algo
{
    BACKTRACKING = 0,
    HEURISTIC = 1
} algo_t;

/*****************************************************************************

* Description: implementation of knight's tour, 
            user can chose dependin on algo_t approuch
            the start_position should be at board range position(0-63)
            path_board is the output board represent the knight's tour path.
            time_limit is the max time require for succesess
*Return value: returns a ALLOC_ERROR in case of dynamic allocation failure
                FAIL_TIMEOUT if doesnt succesess find full path at time limit
                otherwise return SUCCSESS
* Time Complexity: O()

*****************************************************************************/
status_t KnightsTour(char *path_board,
					 size_t start_position,
					 algo_t approach,
                     time_t time_limit);

#endif