#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "sfs.h"

void print_sb(struct superblock sb);

uint8_t* read_block(int fd, uint64_t block_num);
void  write_block(int fd, uint64_t block_num, uint8_t* block);

void read_sb(int fd);

static struct superblock sb;

sfs_err sfs_init(const char* pathname)
{
    const int fd = open(pathname, O_RDWR, 0600);
    if (fd < 0)
    {
        return -SFS_ERR_CREAT;
    }

    read_sb(fd);

    print_sb(sb);
    
    return 0;
}


void read_sb(int fd)
{
    uint8_t *block = read_block(fd, SB_OFFSET); 
    memcpy(&sb, block, sizeof(sb));
}


uint8_t* read_block(int fd, uint64_t block_num)
{   
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


void  write_block(int fd, uint64_t block_num, uint8_t* block)
{
    
    off_t offset = lseek(fd, block_num * BLOCK_SIZE, SEEK_SET);
    if (offset < 0)
    {
        fprintf(stderr, "ERROR: could not find block %ld\n", block_num);
    }

    // TODO: If writing the new block somehow fails,try write back the previous block
    ssize_t bytes = write(fd, block, BLOCK_SIZE);

    if (bytes < 0)
    {
        fprintf(stderr, "ERROR: could not read block from sfs\n");
        exit(1);
    }
}


void print_sb(struct superblock sb)
{
    printf("Super Block:\n");
    printf("  Magic: 0x%lX\n", sb.magic);
    printf("  Size:  %ld (bytes)\n", sb.size);
}
