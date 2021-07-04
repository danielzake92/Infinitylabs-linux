/********************************************************************************
 *  FILENAME:  Bitarray.h  DEVELOPER: Daniel Zaken  TEAM: Blue                  * 
 *                                                                              *
 *  REVIEWER:  Daniel Benedik                                                   * 
 *                                                                              *
 *  PURPOSE:  LIB for Modifying Bit - Array                                     *
 *                                                                              *
 *******************************************************************************/
#ifndef __ILRD_BIT_ARRAY_H__
#define __ILRD_BIT_ARRAY_H__
/****************************************************************************/


#include <stddef.h> /*for size_t data type*/

/*Macros used for program*/
#define BITS_IN_WORD sizeof(bitsarray_t) * CHAR_BIT
#define MSB sizeof(bitsarray_t) * CHAR_BIT - 1

typedef size_t bitsarray_t;



/****************************************************************************************************************/
/*Purpose: function that sets a bit in arr according to index given
  Parameters: arr- bit array
  		      index- index of bit to set
  Return value: bit arr after setting bit in index defined
  Complexity: O(1)
*/
bitsarray_t BitsArrSetOn( bitsarray_t arr, size_t index ); 
/****************************************************************************************************************/





/****************************************************************************************************************/
/*Purpose: function that unsets a bit in arr according to index given
  Parameters: arr- bit array
  		      index- index of bit to unset
  Return value: bit array after unsetting bit in index defined
  Complexity: O(1)
*/
bitsarray_t BitsArrSetOff( bitsarray_t arr, size_t index ); 
/****************************************************************************************************************/





/****************************************************************************************************************/
/*Purpose:    function that unsets or sets a bit according to set value in arr at index given
  Parameters: arr- bit array
  		      index- index of bit to set/unset. 
  		      set- a boolean variable that determines if set(1) or unset(0)
  Return value: bit array after setting/unsetting bit
  Complexity: O(1)
*/
bitsarray_t BitsArrSetBit( bitsarray_t arr, size_t index, int set ); 
/****************************************************************************************************************/





/****************************************************************************************************************/
/*Purpose:    function that determines whether bit at index is set or unset. 
  Parameters: arr- bit array
  		      index- index of bit to check
  Return value: boolean true(1) false(0) 
  Complexity: O(1)
*/
int BitsArrGetBit( bitsarray_t arr, size_t index ); 
/****************************************************************************************************************/





/****************************************************************************************************************/
/*Purpose: function that sets all bits (1)
  Parameters: arr- bit array
  Return Value: bit array after setting all bits
  Complexity: O(1)
*/
bitsarray_t BitsArrSetAll( bitsarray_t arr ); 
/****************************************************************************************************************/






/****************************************************************************************************************/
/*Purpose: function that unsets all bits (0)
  Parameters: arr- bit array
  Return value: bit array after unsetting all bits
  Complexity: O(1)
*/
bitsarray_t BitsArrClearAll(bitsarray_t bits); 
/****************************************************************************************************************/





/****************************************************************************************************************/
/*Purpose: function that returns number of set bits
  Parameters: arr- bit array
  Return value: number of set bits in bit array
  Complexity: O(n), n = number of set bits
*/
size_t BitsArrCountOn( bitsarray_t arr );
/****************************************************************************************************************/





/****************************************************************************************************************/
/*Purpose: function that returns number of unset bits
  Parameters: arr- bit array
  Return value: number of unset bits in bit array
  Complexity: O(n), n = number of unset bits
*/
size_t BitsArrCountOff( bitsarray_t arr ); 
/****************************************************************************************************************/





/****************************************************************************************************************/
/*Purpose: function that toggles bit in given index
  Parameters: arr- bit array
  			  index- index of bit to set.
  Return Value: bit array after toggling bit 
  Complexity: O(1)
*/
bitsarray_t BitsArrFlip( bitsarray_t arr, size_t index );
/****************************************************************************************************************/





/****************************************************************************************************************/
/*Purpose: function that coppies binary format of arr to a string
  Parameters: arr- bit array
  			  str- buffer parameter to input string
  			  ***PLEASE USE FUNCTION X TO DYNAMICALLY ALLOCATE SPACE TO str***
  Return value: pointer to string
  Complexity: O(n), n = size of array bit
*/
char *BitsArrToString( bitsarray_t arr, char *str ); 
/****************************************************************************************************************/




/****************************************************************************************************************/
/*Purpose: function that shifts bits left num times. logical shift: pushing zeros on right side
  Parameters: arr- bit array
  			  num- number of times to shift
  Return Value: bit array after shift
  Complexity: O(1)
*/
bitsarray_t BitsArrLeftShift(bitsarray_t bits, size_t num);
/****************************************************************************************************************/




/****************************************************************************************************************/
/*Purpose: function that shifts bits right num times. logical shift: pushing zeros on left side
  Parameters: arr- bit array
  			  num- number of times to shift
  Return Value: bit array after shift
  Complexity: O(1)
*/
bitsarray_t BitsArrRightShift(bitsarray_t bits, size_t num);
/****************************************************************************************************************/





/****************************************************************************************************************/
/*Purpose: function that returns a mirrored version of arr
  Parameters: arr- bit array
  Return value: mirrored array	  
  Complexity: O(n), n = size of bit array
*/
bitsarray_t BitsArrMirror(bitsarray_t bits);
/****************************************************************************************************************/





/****************************************************************************************************************/
/*Purpose: function that return number of set bits using LUT
  Parameters: arr- bit array
  Return value: number of set bits
  Complexity: O(1)
*/
size_t BitsArrLutCountOn(bitsarray_t arr);
/****************************************************************************************************************/





/****************************************************************************************************************/
/*Purpose: function that returns a mirrored version of arr using LUT
  Parameters: arr- bit array
  Return value: bit array after mirroring  
  Complexity: O(1)
*/
bitsarray_t BitsArrLutMirror(bitsarray_t bits);
/****************************************************************************************************************/






/****************************************************************************************************************/
/*Purpose: helper function for malloc to allocat BitArrayStr function
  Return Value: pointer to allocated memory	  
  Complexity: O(1)
*/
char *MallocToBitsArrayStr();
/****************************************************************************************************************/

#endif
