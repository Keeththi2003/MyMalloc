# 🛠️ MyMalloc: Custom Dynamic Memory Allocator in C

Welcome to **MyMalloc**, a lightweight and efficient memory allocator built from scratch in C! This project replicates the behavior of standard `malloc` and `free` functions, using a fixed memory pool and a linked list to manage memory blocks.

---

## 🚀 Features

- **Dynamic Memory Allocation**  
  Mimics `malloc` to allocate memory dynamically.
  
- **Memory Deallocation**  
  Implements a custom `free` function to reclaim memory.

- **Block Splitting and Merging**  
  Efficiently handles fragmentation by splitting large blocks and coalescing adjacent free blocks.

- **Fixed Memory Pool**  
  Uses a statically allocated array of 25,000 bytes as the memory pool.

---

## 🏗️ How It Works

The allocator uses a linked list of memory blocks to manage allocations.  
Each block contains:
- The **size** of the block.
- Whether it is **free** or allocated.
- A pointer to the **next block**.

The `MyMalloc` function searches for a suitable block to fulfill the memory request. If the block is larger than required, it splits the block and reuses the remaining memory. When freeing memory, `MyFree` merges adjacent free blocks to reduce fragmentation.

---

## 📂 File Structure

