#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "sfs.h"

static uint8_t* read_block(int fd, uint64_t block_num);
static void  write_block(int fd, uint64_t block_num, uint8_t* block);

sfs_err sfs_init(const char* pathname, size_t size)
{
    if (size > MAX_FS_SIZE) size = MAX_FS_SIZE;

    const int fd = open(pathname, O_CREAT | O_RDWR, 0600);
    if (fd < 0)
    {
        return SFS_ERR_CREAT;
    }

    char super_block[BLOCK_SIZE] = {0};
    strcpy(super_block, "Hello SFS!\0");
    write_block(fd, SB_OFFSET, (uint8_t*)super_block);
    
    uint8_t* sb = read_block(fd, SB_OFFSET);
    printf("%s\n", (char*) sb);

    if (close(fd) < 0) return SFS_ERR_CREAT;

 
    return SFS_ERR_OK;
}


static uint8_t* read_block(int fd, uint64_t block_num)
{
    if (block_num < 0)
    {
        fprintf(stderr, "ERROR: Cannot access negative block:  %ld!\n", block_num);
        exit(1);
    }

    off_t offset = lseek(fd, block_num * BLOCK_SIZE, SEEK_SET);
    if (offset < 0)
    {
        fprintf(stderr, "ERROR: Could not find block %ld\n", block_num);
        exit(1);
    }

    uint8_t* buf = (uint8_t*) malloc(sizeof(uint8_t) * BLOCK_SIZE);
    ssize_t bytes = read(fd, buf, BLOCK_SIZE);
    if (bytes < 0) 
    {
        fprintf(stderr, "ERROR: Could not read block from sfs\n");
        free(buf);
        exit(1);
    }
    
    return buf;
}


static void  write_block(int fd, uint64_t block_num, uint8_t* block)
{
    if (block_num < 0)
    {
        fprintf(stderr, "ERROR: Cannot access negative block:  %ld!\n", block_num);
        exit(1);
    }
    off_t offset = lseek(fd, block_num * BLOCK_SIZE, SEEK_SET);
    if (offset < 0)
    {
        fprintf(stderr, "ERROR: could not find block %ld\n", block_num);
    }

    ssize_t bytes = write(fd, block, BLOCK_SIZE);

    if (bytes < 0)
    {
        fprintf(stderr, "ERROR: could not read block from sfs\n");
        exit(1);
    }
}
