#include <stdio.h>
#include <iostream>

const int i = 3;
int z = 3;

inline void foo();

int main()
{
    const int j = 100;
    int arr[j] = {0};

    foo();

    return 0;
}

inline void foo()
{
    std::cout << "kkk\n";
}