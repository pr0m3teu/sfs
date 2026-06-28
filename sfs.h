#ifndef SFS_H_
#define SFS_H_

#include <stddef.h>

#define MAX_FS_SIZE (2UL << 30) // 2 GB 
#define MAX_INODES  30 // this essentially limits the ammount of files to 30, remove/change this later

#define BLOCK_SIZE  1024UL
#define BLOCK_START_ADDR 1024

typedef enum {
    SFS_ERR_OK,
    SFS_ERR_CREAT,

} sfs_err;


typedef struct {
    int nr;
    int attr;
} inode;


sfs_err sfs_init(const char* pathname, size_t fs_size);

#endif  // SFS_H_
