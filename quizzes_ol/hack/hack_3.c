#include <stdio.h>

void func2(void *arg) 
{
    long f2;
    printf("Enter func2\n");
 
    /* Area2 */

/*replacing ebp of func1 and func2
  and also replacing return addresses 
  (ip pointers) of func1 and func2
*/ 	

  	*(&f2 + 1) = *((long*)arg + 1); /*taking func1 return address*/ 
 	*(&f2 + 2) = *((long*)arg + 2); /*taking func1 esp*/
    
    printf("Exit func2\n");
}

void func1() 
{
    long f1;
    printf("Enter func1\n");
    func2(&f1);
    printf("Exit func1\n");
}
 
int main()
{
    const long x=1;
    long y=5;
	

    /* Area1 */
 
    printf("x=%lu\n",x);
    func1();
 
    printf("Exit main\n");
    return 0;
}


