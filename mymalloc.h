#ifndef MYMALLOC_H
#define MYMALLOC_H

#include <stddef.h>
#include <stdbool.h>

#define CAPACITY 25000
#define BLOCK_SIZE sizeof(struct Block)

void instalizeFirstBlock();
void *MyMalloc(size_t size);
void MyFree(void *ptr);

#endif
