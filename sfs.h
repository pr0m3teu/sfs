#ifndef SFS_H_
#define SFS_H_

#include <stddef.h>

#define MAX_FS_SIZE (2UL << 30) // 2 GB 

#define BLOCK_SIZE  1024UL
#define SB_OFFSET 0


typedef enum {
    SFS_ERR_OK,
    SFS_ERR_CREAT,
    SFS_ERR_CONTEXT,
} sfs_err;


sfs_err sfs_init(const char* pathname, size_t fs_size);

#endif  // SFS_H_
