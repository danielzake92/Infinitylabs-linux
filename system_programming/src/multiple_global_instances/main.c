
#include <stdio.h>
#include <dlfcn.h>
#include <errno.h>

extern int iii;
static void implicit_call_func_in_f1(void);
static void explicit_call_func_in_f1(void);
extern void function_in_f1_file(void);/*for the implicit usage*/

int main()
{
	/*printf("address of iii : %p\n",&iii);*/
	implicit_call_func_in_f1(); /* iii == 1     */
	explicit_call_func_in_f1(); /* iii == 2 (?) */

	printf("iii = %d\n", iii);

	return 0;
}

void implicit_call_func_in_f1(void)
{
	function_in_f1_file();
}

void explicit_call_func_in_f1(void)
{
	void *handle;

	void (*fptr)(void);

	/* will "reuse" the iii symbol from so1 if it was linked dynamically (implicit),
	 * or statically with -rdynamic flag.
	 * otherwise - the symbol iii in so1 is not visible to the dynamic linker.
	 */
	handle = dlopen("./libf1.so", RTLD_LOCAL | RTLD_LAZY);

	if(!handle)
	{
		perror("dlopen:");
	}

	fptr = dlsym(handle, "function_in_f1_file");
	(*fptr)();
}
