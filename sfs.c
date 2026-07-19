#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "sfs.h"

static void print_sb(struct superblock sb);

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

    struct superblock sb;
    sb.magic = SFSMagic;
    sb.size = MAX_FS_SIZE;

    uint8_t buf[BLOCK_SIZE];
    memset(buf, 0, BLOCK_SIZE);
    memcpy(buf, &sb, sizeof(sb));
    print_sb(sb);

    write_block(fd, SB_OFFSET, (uint8_t*) buf);
    
    uint8_t* read_buf = read_block(fd, SB_OFFSET);
    struct superblock read_sb;
    memcpy(&read_sb, read_buf, sizeof(read_sb)); 

    print_sb(read_sb);
    if (close(fd) < 0) return SFS_ERR_CREAT;

 
    return SFS_ERR_OK;
}


static uint8_t* read_block(int fd, uint64_t block_num)
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


static void  write_block(int fd, uint64_t block_num, uint8_t* block)
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


static void print_sb(struct superblock sb)
{
    printf("Super Block:\n");
    printf("  Magic: 0x%lX\n", sb.magic);
    printf("  Size:  %ld (bytes)\n", sb.size);
}
