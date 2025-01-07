#include "mymalloc.h"

// Define memory
char memory[CAPACITY];

// Structure for memory block
typedef struct Block
{
    size_t size;
    bool free;
    struct Block *next;
} Block;

// Pointer to the head of the list
static Block *freeMemory = (Block *)memory;

// Install first free memory block
void instalizeFirstBlock()
{
    freeMemory->size = CAPACITY - BLOCK_SIZE;
    freeMemory->free = 1;
    freeMemory->next = NULL;
}

void *MyMalloc(size_t size)
{
    // Install first block if not already installed
    if (!freeMemory->size)
    {
        instalizeFirstBlock();
    }
    // If size is 0 return null
    if (size == 0)
    {
        return NULL;
    }

    Block *current = freeMemory;

    while (current != NULL)
    {
        if (current->free && current->size >= size)
        {
            // If there enoufspace split the block to required block and free block
            if (current->size > size + BLOCK_SIZE)
            {
                Block *newBlock = (Block *)((char *)current + size + BLOCK_SIZE);
                newBlock->free = 1;
                newBlock->next = current->next;
                newBlock->size = current->size - size - BLOCK_SIZE;

                current->next = newBlock;
                current->size = size;
            }
            current->free = 0;

            return (char *)current + BLOCK_SIZE; // Return pointer of the data part
        }

        current = current->next;
    }

    return NULL; // If memory not allocted return Null
}

void MyFree(void *ptr)
{
    // If ptr is null return
    if (ptr == NULL)
        return;

    // Free the required block
    Block *freedBlock = (Block *)((char *)ptr - BLOCK_SIZE);
    freedBlock->free = 1;
    // Link free memory list to freeblocks
    Block *current = freeMemory;
    while (current != NULL)
    {
        if (current->next != NULL && current->free && current->next->free)
        {
            current->size += current->next->size + BLOCK_SIZE;
            current->next = current->next->next;
        }
        else
        {
            current = current->next;
        }
    }
}
