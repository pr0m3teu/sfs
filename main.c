#include <stdio.h>
#include "sfs.h"

int main(void) 
{
    char file_name[] = "sfs.txt";
    sfs_init(file_name, MAX_FS_SIZE); 

    
    return 0;
}
