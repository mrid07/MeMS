# MeMS: Memory Management System

## Overview

MeMS is a custom memory management system designed to efficiently manage and allocate memory using the C programming language. It leverages system calls like `mmap` and `munmap` for memory allocation and deallocation, adhering to stringent constraints and requirements.

## Features and Functions

### Initialization

- **Function:** `void mems_init()`
- **Description:** Initializes the MeMS system by setting up essential parameters, including the head of the free list and starting MeMS virtual address.

### Memory Allocation

- **Function:** `void* mems_malloc(size_t size)`
- **Description:** Allocates the specified amount of memory. It attempts to reuse segments from the free list that are large enough. If no appropriate segment is found, it uses `mmap` to request more memory from the OS and updates the free list accordingly.
- **Parameters:**
  - `size`: The size of the memory to be allocated.
- **Returns:** MeMS Virtual address created and managed by MeMS.

### Memory Deallocation

- **Function:** `void mems_free(void* ptr)`
- **Description:** Frees the memory block pointed to by the given MeMS virtual address, marking the corresponding sub-chain node in the free list as a HOLE, making it available for future allocations.
- **Parameters:**
  - `ptr`: MeMS Virtual address to be freed.
- **Returns:** None

### Print Memory Statistics

- **Function:** `void mems_print_stats()`
- **Description:** Prints comprehensive statistics on the memory usage, including the total number of mapped pages, unused memory, and details on each node and segment in the main and sub-chains.
- **Parameters:** None
- **Returns:** None (outputs the stats to STDOUT)

### Address Translation

- **Function:** `void* mems_get(void* v_ptr)`
- **Description:** Converts a MeMS virtual address to the corresponding MeMS physical address that was mapped using `mmap`.
- **Parameters:**
  - `v_ptr`: MeMS Virtual address to be converted.
- **Returns:** MeMS Physical address mapped to the given virtual address.

### Cleanup and Finish

- **Function:** `void mems_finish()`
- **Description:** Cleans up and unmaps all allocated memory, ensuring that all resources are properly released using the `munmap` system call.
- **Parameters:** None
- **Returns:** None

## Real-Life Use Cases

### Embedded Systems Development
- **Scenario:** In embedded systems, memory resources are limited. MeMS can efficiently manage memory allocation for different components, ensuring optimal memory usage and preventing fragmentation.

### Custom Application Development
- **Scenario:** Applications with specialized memory management needs can benefit from the tailored memory allocation strategies provided by MeMS, enabling fine-tuned control over memory usage.

### Research and Development
- **Scenario:** Researchers working on custom memory management algorithms or optimizations can use MeMS as a foundational system to test and implement their approaches.

### Educational Purposes
- **Scenario:** MeMS can be used as an educational tool for understanding memory management concepts, system calls, and data structures in a practical and hands-on manner.

---

For more details and to explore the implementation, visit the [MeMS GitHub repository](https://github.com/Rahul-Agrawal-09/MeMS-Skeleton-code).

