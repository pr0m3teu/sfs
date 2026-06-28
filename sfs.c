#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

#include "sfs.h"
#define LL_IMPLEMENTATION
#include "ll.h"

sfs_err sfs_init(const char* pathname, size_t size)
{
    if (size > MAX_FS_SIZE) size = MAX_FS_SIZE;

    const int fd = open(pathname, O_CREAT | O_RDWR, 0600);
    if (fd < 0)
    {
        return SFS_ERR_CREAT;
    }

    ll_t *free_inodes = (ll_t*) malloc(sizeof(ll_t));
    ll_t *free_blocks = (ll_t*) malloc(sizeof(ll_t)); 
    
    // TODO: Round size to the closest, greater power of 2
    const uint64_t total_blocks = size / BLOCK_SIZE;

    init_ll(free_inodes, sizeof(uint32_t));
    init_ll(free_blocks, sizeof(uint32_t));


    for (int i = 0; i < MAX_INODES; ++i)
    {
        uint32_t *p = malloc(sizeof(uint32_t));
        *p = i;
        insert_ll(free_inodes, p); 
    }


    for (uint64_t i = 0; i < total_blocks; ++i)
    {
        uint32_t *p = malloc(sizeof(uint32_t));
        *p = i;
        insert_ll(free_blocks, p);
    }

    node_t *node = free_blocks->head;

       
    char buf[] = "SFSMagic";
    int bytes = write(fd, buf, sizeof(buf) - 1); 

    if (bytes < 0)
    {
        return bytes;
    }

    close(fd);


 
    return SFS_ERR_OK;
}
