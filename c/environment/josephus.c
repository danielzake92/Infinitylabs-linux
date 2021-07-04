/********************************************************************************
 *  FILENAME:  Josephus problem  NAME:  Daniel Zaken  REVIEWER:  Liad oz        *
 *                                                                              *
 *  POURPOSE:  Solution for J problem				       	                    *
 *                                                                              *
 ********************************************************************************/
 
#include <stdio.h>   /*standart outpu */
#include <stdlib.h>  /*Allocating */
#include <assert.h>  /*assert needed */

/*PROTOTYPE*/
int josephus(int *);
int *InitGrp(int*, int);


int main()
{	
	int num = 0 ;
	int *group = NULL;
		
	/*input from user*/
	puts("how many soldiers");
	scanf("%d", &num);
	
	/*group initializing*/
	group = (int*)malloc(num * sizeof(int));
	
	if (!group)
	{
		puts("Allocation failed");
		return 0;
	}
	
	group = InitGrp(group, num);
		
	/*ans and free*/
	josephus(group);
	puts("");
	free(group);
	return 0;
}

int josephus(int *grp)
{
	int index_to_kill = 1;
	int location = 0;
	int res = 0;
	
	assert(grp);
		
	while(location != -1)
	{
		grp[location] = grp[index_to_kill];
		grp[index_to_kill] = -1;
		res = location + 1;
		location = grp[location];
		index_to_kill = grp[location];						
	}	
	
	printf("\n%d",res);
	return res;
}


int *InitGrp(int *grp, int num)
{
	int *start = grp;
	int i = 1;
	
	assert(grp);
	
	while (i < num)
	{
		*grp = i;
		++i;
		++grp;
	}
	*grp = 0;
	return start;
}







