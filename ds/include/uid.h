#ifndef __ILRD_UID_H__
#define __ILRD_UID_H__

#include <stddef.h> /*required for size_t type*/ 
#include <time.h>
#include <sys/types.h>/*required for pid_t*/
/****************************************************************************/

typedef struct
{
   pid_t pid;
   time_t creation_time;
   size_t counter;
} ilrd_uid_t;

/****************************************************************************/
/*
Description: Creates UID
Parameters: 
Return Value: returns an instance of a uid_t structure
Time Complexity: O(1)
*/
ilrd_uid_t UIDCreate();
/****************************************************************************/
/*
Description: Compares id1 and id2
Parameters: 

				id1 - > uid to be compared
				id2 - > uid to be compared				

Return Value:  returns 1 if the uid is the same, else returns 0
Time Complexity: O(1)
*/

int UIDIsSame(ilrd_uid_t id1,ilrd_uid_t id2);
/****************************************************************************/
/*
Description: Get the default value of a bad UID.
Parameters: 
Return Value: returns a bad uid 
Time Complexity: O(1)
*/
ilrd_uid_t UIDGetBadUID();
/****************************************************************************/


#endif
