#include <bits/stdc++.h>
using namespace std;
 
int main()
{
 
    int n = 5, m = -5;
    bitset<8> b(n);
    bitset<8> b1(m);

    size_t i = 0;

    for(i = 0; i < 256; ++i )
    {
        if(!(i % 8))
        {
            cout<< endl;
        }
        bitset<8> b(i);
        cout<< "\"" <<b<<"\",";

    }
            cout<< endl;



    return 0;
}