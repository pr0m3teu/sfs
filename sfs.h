#ifndef SFS_H_
#define SFS_H_

#include <stddef.h>
#include <stdint.h>

#define SFSMagic 0x636967614D534653 //SFSMagic
                                    
#define MAX_FS_SIZE (1UL << 31) // 2 GB 

#define BLOCK_SIZE  1024UL

/*
 * Since SFS contains everything inside a file (on an already
 * existing file system and OS) there will be no capability of
 * booting from it. Therefore the first block will be the super
 * block and not the boot block.
 */
#define SB_OFFSET     0
#define INODES_OFFSET 1


struct superblock {
    uint64_t magic; // Must be SFSMagic
    uint64_t size;  // SFS file size
};

#define NDISK_BLOCKS 16
#define MAX_FILE_SIZE (BLOCK_SIZE * NDISK_BLOCKS)

// Inode representation inside the fs file
struct fsinode {
    uint32_t type;                // File type
    uint32_t addrs[NDISK_BLOCKS]; // Block addresses for file
};


#define MAX_INODES (BLOCK_SIZE / sizeof(fsinode))

typedef enum {
    SFS_ERR_OK,
    SFS_ERR_CREAT,
    SFS_ERR_CONTEXT,
} sfs_err;


sfs_err sfs_init(const char* pathname);

void print_sb(struct superblock sb);
#endif  // SFS_H_
