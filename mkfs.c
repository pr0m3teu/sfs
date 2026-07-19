#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "sfs.h"


extern uint8_t* read_block(int fd, uint64_t block_num);
extern void  write_block(int fd, uint64_t block_num, uint8_t* block);

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        fprintf(stderr, "ERROR: You need to provide a file name and file size!\n");
        fprintf(stderr, "USAGE: mkfs <filename> <fs_size>\n");
        exit(1);
    }

    char* pathname = argv[1];
    size_t size = (size_t) atoi(argv[2]);

    if (size > MAX_FS_SIZE || size <= BLOCK_SIZE) size = MAX_FS_SIZE;

    const int fd = open(pathname, O_CREAT | O_RDWR, 0600);
    if (fd < 0)
    {
        return -SFS_ERR_CREAT;
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
    if (close(fd) < 0) return -SFS_ERR_CREAT;
    return SFS_ERR_OK;
}
