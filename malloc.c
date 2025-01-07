#include <stdio.h>
#include <stdbool.h>
#define CAPACITY 25000
#define BLOCK_SIZE sizeof(struct Block)

char memory[CAPACITY];

struct Block
{
    size_t size;
    bool free;
    struct Block *next;
};

static struct Block *freeMemory = (struct Block *)memory;

void *MyMalloc(size_t size);
void MyFree(void *ptr);

void instalizeFirstBlock()
{
    freeMemory->size = CAPACITY - BLOCK_SIZE;
    freeMemory->free = 1;
    freeMemory->next = NULL;
}

void *MyMalloc(size_t size)
{

    if (!freeMemory->size)
    {
        // printf("Memory Instalized\n");
        // printf("%p\n", freeMemory);
        instalizeFirstBlock();
    }

    if (size == 0)
    {
        return NULL;
    }

    struct Block *current = freeMemory;

    while (current != NULL)
    {
        if (current->free && current->size >= size)
        {
            if (current->size > size + BLOCK_SIZE)
            {
                struct Block *newBlock = (struct Block *)((char *)current + size + BLOCK_SIZE);
                newBlock->free = 1;
                newBlock->next = current->next;
                newBlock->size = current->size - size - sizeof(struct Block);

                current->next = newBlock;
                current->size = size;
            }
            current->free = 0;

            return (char *)current + sizeof(struct Block);
        }

        current = current->next;
    }

    return NULL;
}

void MyFree(void *ptr)
{
    if (ptr == NULL)
        return;

    struct Block *freeBlock = (struct Block *)((char *)ptr - BLOCK_SIZE);
    freeBlock->free = 1;

    struct Block *current = freeMemory;

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

#include <stdio.h>

int main()
{
    // Print the size of the Block structure
    printf("Block structure size: %zu bytes\n", sizeof(struct Block));

    // Initialize and test allocation
    printf("\n=== Testing Allocation ===\n");
    int *ptr1 = (int *)MyMalloc(1000);
    if (ptr1)
        printf("Allocated 1000 bytes at %p\n", ptr1);
    else
        printf("Allocation failed for 1000 bytes\n");

    int *ptr2 = (int *)MyMalloc(2000);
    if (ptr2)
        printf("Allocated 2000 bytes at %p\n", ptr2);
    else
        printf("Allocation failed for 2000 bytes\n");

    int *ptr3 = (int *)MyMalloc(500);
    if (ptr3)
        printf("Allocated 500 bytes at %p\n", ptr3);
    else
        printf("Allocation failed for 500 bytes\n");

    // Free some memory
    printf("\n=== Testing Free ===\n");
    printf("Freeing memory at %p\n", ptr2);
    MyFree(ptr2);

    printf("Freeing memory at %p\n", ptr3);
    MyFree(ptr3);

    // Allocate memory after freeing
    printf("\n=== Testing Reallocation ===\n");
    int *ptr4 = (int *)MyMalloc(1500);
    if (ptr4)
        printf("Reallocated 1500 bytes at %p\n", ptr4);
    else
        printf("Reallocation failed for 1500 bytes\n");

    // Allocate memory to test block splitting
    printf("\n=== Testing Block Splitting ===\n");
    int *ptr5 = (int *)MyMalloc(700);
    if (ptr5)
        printf("Allocated 700 bytes at %p\n", ptr5);
    else
        printf("Allocation failed for 700 bytes\n");

    // Test large allocation
    printf("\n=== Testing Large Allocation ===\n");
    int *ptr6 = (int *)MyMalloc(20000);
    if (ptr6)
        printf("Allocated 20000 bytes at %p\n", ptr6);
    else
        printf("Allocation failed for 20000 bytes\n");

    // Free remaining memory
    printf("\n=== Freeing All Allocated Memory ===\n");
    MyFree(ptr1);
    printf("Freed memory at %p\n", ptr1);

    MyFree(ptr4);
    printf("Freed memory at %p\n", ptr4);

    MyFree(ptr5);
    printf("Freed memory at %p\n", ptr5);

    MyFree(ptr6);
    printf("Freed memory at %p\n", ptr6);

    // Test allocation after all memory is freed
    printf("\n=== Testing Allocation After Free ===\n");
    int *ptr7 = (int *)MyMalloc(800);
    if (ptr7)
        printf("Allocated 800 bytes at %p\n", ptr7);
    else
        printf("Allocation failed for 800 bytes\n");

    return 0;
}
