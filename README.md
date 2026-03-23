# OSC 2021

## ARMv8-Based Real-Time Microkernel
A functional microkernel implemented from scratch for Raspberry Pi 3b+, focusing on core OS concepts including memory management, preemptive scheduling, and virtual file systems.

🚀 Core Features

* **Memory Management**
  * Buddy System: Implemented a page-level allocator to manage physical memory frames, effectively mitigating external fragmentation.
  * Slab Allocator: Developed object pools for kernel-specific structures (e.g., vnodes, tasks) to enhance allocation speed and minimize internal fragmentation.

* **Process & Task Management**
  * Preemptive Scheduler: Designed a priority-based scheduler with full thread lifecycle management (Ready, Running, Blocked, Dead).
  * Resource Reclamation: Implemented an Idle Thread specifically for automated zombie process cleaning and system resource recycling.

* **File System Architecture**
  * VFS Abstraction: Architected a Virtual File System layer using C function pointers to provide a uniform interface for different file systems.
  * Tmpfs: Developed a memory-resident file system with dynamic resource allocation.
  * FAT32 Integration: Implemented FAT32 support by parsing the Master Boot Record (MBR) and partition tables.

* **System Security & Hardware Abstraction**
  * MMU Configuration: Configured ARMv8 3-level page tables (PGD, PUD, PMD) supporting 2MB block mapping for efficient address translation.
  * Isolation: Enforced strict EL0/EL1 memory isolation; utilized MAIR_EL1 to define distinct cache attributes for Normal Memory and Device MMIO.
  * Context Management: Used Trap Frames to ensure robust CPU state preservation during exception handling and context switching.

* **Implemented System Calls**
  * Supported 10+ POSIX-like syscalls (e.g., fork, exec, wait, exit, mount) via SVC exception handling.

## Author

| 學號 | GitHub 帳號 | 姓名 | Email |
| --- | ----------- | --- | --- |
|`309513017`| `ZiXunHuang` | `黃梓熏` | willie0402.eed05@nctu.edu.tw |

## How to build

```
make
```

## How to run (on QEMU)

```
make run
```
