/*****************************************************************************
* FILE:      ext2_test.c   			   PURPOSE: ext2 file system
* DEVELOPER: Daniel Zaken              TEAM:    RD100
*
* REVIEWER:  Itamar Aron               STATUS: Impl
******************************************************************************/
#include <stdio.h> 
# include "ext2.h"

#define RAM0_PATH "/dev/ram0"

int main(int argc, char *argv[])
{
    (void)argc;
    DisplayFile(RAM0_PATH, argv[1]);
    return 0;
}
