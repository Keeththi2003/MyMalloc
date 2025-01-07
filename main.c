#include "mymalloc.h"
#include <stdio.h>

int main()
{

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
