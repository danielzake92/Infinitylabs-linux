/****************************************************************************/
#include <cstddef>
#include <cassert> /*assert required*/
#include <cstring>
#include <cstdio>
#include <cstdlib> //qsort
#include <vector>
#include <iostream>
#include <climits>
/*************************************************************/
int coinChange(std::vector<int>& coins, int amount) 
{
	std::vector<int> dp(amount + 1,INT_MAX -1);
	//dp[i] stores the minimum number of coins needed to reach amount i
	dp[0] = 0;

	for(int i = 0; i < coins.size(); i++)      //looping through each coin
	{
		for(int j = coins[i]; j < dp.size(); j++)      
		{
			dp[j] = std::min(dp[j], dp[j - coins[i]] + 1);     //checking whether adding the current coin produces min coins
		}
	}

	if(dp[amount] == (INT_MAX - 1))
		return - 1;
	else
		return dp[amount];
}

int main()
{
	std::vector<int> coins;

	coins.push_back(5);
	coins.push_back(2);

	int res = coinChange(coins, 23);

	std::cout<< "res = "<<res<<std::endl;



	return 0;
}














// int cmpfunc (const void * a, const void * b) 
// {
//    return *(int*)b - *(int*)a;
// }


// size_t CoinRecHelper(int *arr, size_t arr_size, int sum)
// {
	
// 	if(0 == sum)
// 	{
// 		return 1;
// 	}
	
// 	if( 0 > sum )	
// 	{
// 		return 0;
// 	}

// 	size_t i = 0;
// 	size_t counter = 0;

// 	for(; i < arr_size; ++i)
// 	{
// 		CoinRecHelper(arr, arr_size, sum - arr[i]);
// 	}

// 	return CoinRecHelper(arr, arr_size, sum - arr[i]) + CoinRecHelper(arr, arr_size, sum - arr[i]);

// }
// size_t CoinRec(int *arr, size_t arr_size, int sum)
// {
// 	qsort(arr, arr_size, sizeof(arr[0]), cmpfunc);

// 	size_t counter = 0;

// 	// CoinRecHelper(arr, arr_size, sum, &counter);
// 	CoinRecHelper(arr, arr_size, sum);

// 	return counter;
// }




// int main()
// {
// 	int arr[2] = {5, 2};

// 	size_t arr_size = 2;

// 	int sum = 10;

// 	size_t res = CoinRec(arr, arr_size, sum);

// 	printf("\nres = %lu\n", res);

// 	// printf("%d, %d, %d", arr[0], arr[1], arr[2]);

// 	return 0;
// }


// #include <stdio.h>
// #include <string.h>
 
// /* Function to swap values at two pointers */
// void swap(char *x, char *y)
// {
//     char temp = *x;;
//     *x = *y;
//     *y = temp;
// }
 
// void Permute(char *arr, int left, int right)
// {
// 	int i = left;
// 	if (left == right)
// 	{	
// 		printf("%s\n", arr);
// 		return;
// 	}
// 	for (i = left; i <= right; i++)
// 	{
// 		swap(&arr[left], &arr[i]);
// 		Permute(arr ,left + 1 , right);
// 		swap(&arr[left], &arr[i]);
// 	}
// }
 
// int main()
// {
//     char str[] = "ABC";
//     int n = strlen(str);
//     Permute(str, 0, n-1);
//     return 0;
// }
