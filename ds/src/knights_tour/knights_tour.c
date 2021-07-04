/*****************************************************************************
* FILE:      knights_tour.c	           PURPOSE: API for knight's tour        
* DEVELOPER: Daniel Zaken              TEAM:    Green                       
*                                                                               
* REVIEWER:  Dor Eini                  STATUS: Approved                          
******************************************************************************/

#include <stdlib.h> /*malloc*/
#include <assert.h> /*asserts*/

#include "knights_tour.h" /*my current lib*/
#include "utl.h"

/****************************************************************************
*                     defines
****************************************************************************/
#define OPTIONS 8
#define INVALID -1
#define PATH_NOT_FOUND NUM_OF_STATUS
#define FULL 0XFFFFFFFFFFFFFFFF

#define GET_Y(pos) ((pos) / ROW_NUM)
#define GET_X(pos) ((pos) - (GET_Y(pos) * ROW_NUM))
/****************************************************************************
*                     Typedefs
****************************************************************************/
typedef status_t(*tour_func_t)(bitsarray_t *arr,
						  	  char *path_board,
						      char cur_pos,
						      size_t counter,
						      time_t time_limit);
/****************************************************************************
*                 Backtrack and warnsdorf functions
****************************************************************************/
status_t Backtracking(bitsarray_t *arr,
						  char *path_board,
						  char cur_pos,
						  size_t counter,
						  time_t time_limit);

status_t Warnsdorf(bitsarray_t *arr,
						  char *path_board,
						  char cur_pos,
						  size_t counter,
						  time_t time_limit);

size_t NextStepCountValid(bitsarray_t *arr, char cur_pos);
						  
static int IsValidDest(bitsarray_t arr, int index );

/****************************************************************************
*                     LUT helper functions
****************************************************************************/
#if 0
static void InitLut(void);

static void UpdateRowAndCol(int index, int *row, int *col);

static int GetIndex(int row, int col);

static void UpdateLut(int i, int j,int row,int col);

static void Swap(int *a, int *b);

void InsertionSortComparator(int *arr, size_t arr_size);

void InsertionSort(int *arr, size_t arr_size);

static int Comparator(int a, int b);
#endif
/****************************************************************************
*                          GLOBAL LUTS
****************************************************************************/
tour_func_t g_knights_tour_lut[2] = {Backtracking, Warnsdorf};

const int g_lut_options[BOARD_SIZE][OPTIONS] = 
{
	{17, 10, -1, -1, -1, -1, -1, -1 },
	{16, 11, 18, -1, -1, -1, -1, -1 },
	{8, 17, 12, 19, -1, -1, -1, -1 },
	{13, 9, 20, 18, -1, -1, -1, -1 },
	{14, 10, 21, 19, -1, -1, -1, -1 },
	{15, 22, 11, 20, -1, -1, -1, -1 },
	{23, 12, 21, -1, -1, -1, -1, -1 },
	{22, 13, -1, -1, -1, -1, -1, -1 },
	{2, 25, 18, -1, -1, -1, -1, -1 },
	{24, 3, 26, 19, -1, -1, -1, -1 },
	{16, 4, 0, 25, 20, 27, -1, -1 },
	{5, 1, 17, 26, 21, 28, -1, -1 },
	{6, 2, 22, 29, 18, 27, -1, -1 },
	{23, 7, 3, 30, 19, 28, -1, -1 },
	{31, 4, 29, 20, -1, -1, -1, -1 },
	{5, 30, 21, -1, -1, -1, -1, -1 },
	{1, 33, 10, 26, -1, -1, -1, -1 },
	{32, 2, 0, 11, 34, 27, -1, -1 },
	{24, 8, 3, 1, 33, 12, 35, 28 },
	{4, 2, 25, 13, 9, 34, 29, 36 },
	{5, 3, 30, 14, 10, 37, 26, 35 },
	{31, 15, 6, 4, 38, 11, 36, 27 },
	{39, 7, 5, 12, 37, 28, -1, -1 },
	{6, 38, 13, 29, -1, -1, -1, -1 },
	{41, 9, 34, 18, -1, -1, -1, -1 },
	{40, 8, 10, 42, 19, 35, -1, -1 },
	{32, 16, 41, 11, 9, 43, 20, 36 },
	{33, 17, 12, 10, 44, 42, 37, 21 },
	{38, 22, 13, 11, 45, 43, 34, 18 },
	{39, 23, 46, 14, 12, 44, 19, 35 },
	{47, 15, 13, 45, 20, 36, -1, -1 },
	{46, 14, 37, 21, -1, -1, -1, -1 },
	{49, 17, 42, 26, -1, -1, -1, -1 },
	{48, 16, 50, 43, 18, 27, -1, -1 },
	{40, 24, 51, 49, 17, 44, 19, 28 },
	{52, 50, 41, 25, 45, 29, 20, 18 },
	{53, 51, 46, 30, 42, 26, 21, 19 },
	{47, 31, 54, 52, 22, 43, 20, 27 },
	{55, 23, 53, 44, 21, 28, -1, -1 },
	{54, 22, 45, 29, -1, -1, -1, -1 },
	{57, 50, 25, 34, -1, -1, -1, -1 },
	{58, 56, 24, 51, 26, 35, -1, -1 },
	{59, 57, 48, 32, 52, 25, 36, 27 },
	{60, 58, 53, 49, 33, 37, 26, 28 },
	{61, 59, 54, 50, 38, 34, 29, 27 },
	{62, 60, 55, 39, 51, 30, 35, 28 },
	{63, 61, 31, 52, 29, 36, -1, -1 },
	{62, 53, 30, 37, -1, -1, -1, -1 },
	{58, 33, 42, -1, -1, -1, -1, -1 },
	{59, 32, 43, 34, -1, -1, -1, -1 },
	{60, 56, 40, 33, 44, 35, -1, -1 },
	{61, 57, 41, 45, 34, 36, -1, -1 },
	{62, 58, 46, 42, 37, 35, -1, -1 },
	{63, 59, 47, 38, 43, 36, -1, -1 },
	{60, 39, 44, 37, -1, -1, -1, -1 },
	{61, 38, 45, -1, -1, -1, -1, -1 },
	{50, 41, -1, -1, -1, -1, -1, -1 },
	{40, 51, 42, -1, -1, -1, -1, -1 },
	{48, 52, 41, 43, -1, -1, -1, -1 },
	{53, 49, 44, 42, -1, -1, -1, -1 },
	{54, 50, 45, 43, -1, -1, -1, -1 },
	{55, 51, 46, 44, -1, -1, -1, -1 },
	{47, 52, 45, -1, -1, -1, -1, -1 },
	{53, 46, -1, -1, -1, -1, -1, -1 }
};
/****************************************************************************
*                          API AND MAIN FUNC IMP
****************************************************************************/
status_t KnightsTour(char *path_board,
					 size_t start_position,
					 algo_t approach,
                     time_t time_limit)
{
	bitsarray_t bit_arr = 0;
	size_t counter = 1;
	time_limit += time(NULL);	

	assert(path_board);

	return g_knights_tour_lut[approach](&bit_arr,
								      path_board,
									  start_position,
									  counter,
									  time_limit);

}
/******************************************************************************/
status_t Backtracking(bitsarray_t *arr,
						  char *path_board,
						  char cur_pos,
						  size_t counter,
						  time_t time_limit)
{
	int i = 0;
	int dest_index = 0;
	status_t status = PATH_NOT_FOUND;

	assert(arr);
	assert(path_board);

    if ( time(NULL) >= time_limit )
    {
        return FAIL_TIMEOUT;
    }

	path_board[(int)cur_pos] = counter;

	*arr = BitsArrSetOn(*arr, cur_pos);

	if( FULL == *arr )
	{
		return SUCCESS;
	}

	for( i = 0; i < OPTIONS  ; ++i)
	{
		dest_index = g_lut_options[(int)cur_pos][i];	
		if( IsValidDest(*arr,dest_index) )
		{
			status = Backtracking(arr, path_board, dest_index,counter + 1, time_limit);
			
			if( PATH_NOT_FOUND != status)
			{
				return status;
			}
		}
	}
	
	*arr = BitsArrSetOff(*arr, cur_pos);
	path_board[(int)cur_pos] = 0;

	return PATH_NOT_FOUND;
}
/******************************************************************************/
status_t Warnsdorf(bitsarray_t *arr,
						  char *path_board,
						  char cur_pos,
						  size_t counter,
						  time_t time_limit)
{
	int i = 0;
	int dest_index = 0;
	int chosen_dest_index = 0;
	size_t valid_counted = 0;
	size_t min = OPTIONS;
	status_t status = PATH_NOT_FOUND;

	assert(arr);
	assert(path_board);

    if ( time(NULL) >= time_limit )
    {
        return FAIL_TIMEOUT;
    }

	path_board[(int)cur_pos] = counter;

	*arr = BitsArrSetOn(*arr, cur_pos);

	if( FULL == *arr )
	{
		return SUCCESS;
	}

	for( i = 0; i < OPTIONS  ; ++i)
	{
		dest_index = g_lut_options[(int)cur_pos][i];	
		if( IsValidDest(*arr,dest_index) )
		{
			valid_counted = NextStepCountValid(arr, dest_index);
			if(valid_counted <= min )
			{
				min = valid_counted;
				chosen_dest_index = dest_index;
			}	
		}
	}

	status = Warnsdorf(arr, path_board, chosen_dest_index,counter + 1, time_limit);
			
	return status;
}
/****************************************************************************
*                          UTIL FUNC IMP
****************************************************************************/
static int IsValidDest(bitsarray_t arr, int index )
{
	return( (INVALID != index) && (0 == BitsArrGetBit(arr, index)) );
}
/******************************************************************************/
size_t NextStepCountValid(bitsarray_t *arr,char cur_pos)
{
	int i = 0;
	size_t counter = 0;
	int dest_index = 0;	

	for( i = 0; i < OPTIONS  ; ++i)
	{
		dest_index = g_lut_options[(int)cur_pos][i];	
		counter += IsValidDest(*arr, dest_index);
	}
	return counter;
}
/******************************************************************************/
#if 0
static void InitLut(void)
{
	int i = 0;
	int j = 0;
	int row = 0;
	int col = 0;
	size_t count_valid = 0;

	for(i = 0; i < BOARD_SIZE; ++i)
	{
		UpdateRowAndCol(i, &row, &col);
		UpdateLut(i, 0, row - 2, col + 1);
		UpdateLut(i, 1, row - 2, col - 1);

		UpdateLut(i, 2, row + 2, col + 1);
		UpdateLut(i, 3, row + 2, col - 1); 
		
		UpdateLut(i, 4, row + 1, col - 2);
		UpdateLut(i, 5, row - 1, col - 2);

		UpdateLut(i, 6, row + 1, col + 2);
		UpdateLut(i, 7, row - 1, col + 2);

		InsertionSort(g_lut_options[i], OPTIONS);

		for( j = 0; j < ROW_NUM ; ++j )
		{
			if(g_lut_options[i][j] != INVALID )
			{
				++count_valid;
			}
		}
		InsertionSortComparator(g_lut_options[i], count_valid);
		count_valid = 0;
	}
}
/******************************************************************************/
static void UpdateRowAndCol(int index, int *row, int *col)
{
	*row = index / ROW_NUM;
	*col = index - *row * ROW_NUM;
}
/******************************************************************************/
static int GetIndex(int row, int col)
{
	return(row * ROW_NUM + col );
}
/******************************************************************************/
static void UpdateLut(int i, int j,int row,int col)
{
	if( row < 0 || col < 0 ||
		row > ROW_NUM -1 || col > ROW_NUM -1 )
	{
		g_lut_options[i][j] = INVALID;
	}
	else
	{
		g_lut_options[i][j] = GetIndex(row, col);
	}
}
/******************************************************************************/
void InsertionSortComparator(int *arr, size_t arr_size)
{
	size_t i = 0;
	size_t j = 0;
	assert(arr);

	for( i = 1 ; i < arr_size ; ++i )
	{
		for( j = i - 1 ; Comparator(arr[j], arr[j + 1]) > 0 && (j + 1) > 0 ; --j)
		{
			Swap(arr + j, arr + j + 1);
		}
	}
}
/******************************************************************************/
void InsertionSort(int *arr, size_t arr_size)
{
	size_t i = 0;
	size_t j = 0;
	assert(arr);

	for( i = 1 ; i < arr_size ; ++i )
	{
		for( j = i - 1 ; arr[j] < arr[j + 1]  && (j + 1) > 0 ; --j)
		{
			Swap(arr + j, arr + j + 1);
		}
	}
}
/******************************************************************************/
static void Swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
/******************************************************************************/
static int Comparator(int a, int b)
{
    int a_x = 0, a_y = 0, b_x = 0, b_y = 0;

    a_y = GET_Y(a);
    a_x = GET_X(a);

    b_y = GET_Y(b);
    b_x = GET_X(b);

    a_x = MIN(a_x, (7 - a_x));
    b_x = MIN(b_x, (7 - b_x));

    a_y = MIN(a_y, (7 - a_y));
    b_y = MIN(b_y, (7 - b_y));

    a =  MIN(a_x, a_y);
    b =  MIN(b_x, b_y);

    return (a - b);
}
/******************************************************************************/
void PrintLut()
{
  int i = 0, j = 0;
  InitLut();	

  for (i = 0; i < BOARD_SIZE ; ++i)
  {
	printf("{");

    for (j = 0; j < ROW_NUM ; ++j)
    {
	  if( j == 7 )
	  {
		 printf("%d ", g_lut_options[i][j]);
		 continue; 
	  }
      printf("%d, ", g_lut_options[i][j]);
    }
	printf("},");
    printf("\n");
  }
}
#endif
/******************************************************************************/
