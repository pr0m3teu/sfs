#ifndef SFS_H_
#define SFS_H_

#include <stddef.h>
#include <stdint.h>

#define SFSMagic 0x636967614D534653 //SFSMagic
                                    
#define MAX_FS_SIZE (4UL << 30) // 2 GB 

#define BLOCK_SIZE  1024UL

/*
 * Since SFS contains everything inside a file (on an already
 * existing file system and OS) there will be no capability of
 * booting from it. Therefore the first block will be the super
 * block and not the boot block.
 */
#define SB_OFFSET 0


struct superblock {
    uint64_t magic;
    uint64_t size;
};

typedef enum {
    SFS_ERR_OK,
    SFS_ERR_CREAT,
    SFS_ERR_CONTEXT,
} sfs_err;


sfs_err sfs_init(const char* pathname, size_t fs_size);

#endif  // SFS_H_
