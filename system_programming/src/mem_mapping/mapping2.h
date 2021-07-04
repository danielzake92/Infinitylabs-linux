#ifndef __ILRD_MAPPING2_H__
#define __ILRD_MAPPING2_H__


/****************************************************************************/

int g_i = 20;
int bss1;
int bss2;
int bss3;
int bss4;

char *literal1 = "literal1";
char *literal2 = "literal2";

const int c_g_i = 21;

void StrRev(char *str, int n);
char* WordRev(char* str);
void SwapChars(char *a, char *b);
int Max(int x, int y);
void Vars(char **envp, char **argv);
void Funcs(void);


#endif
