Author Information:
George Allison
George.Allison@Colorado.edu

File Information:
addtest.c - This C program is used to test the system call that I created.
Makefile - This makefile informs the system about the system call.
simple_add.c This C file makes up the functionality of the system call.
syscall_64.tbl - This is the system table for the kernel. 
syscalls.h - This is the system call header file.
syslog - This is the system log for the operating system.

File Locations in Build Tree:
simple_add.c, Makefile, and syscall_64.tbl are located within the "arch/x86" directory due to their nature as system files that make up the system call. Within that directory, Makefile and simple_add.c are in the "kernel" directory because it is referenced by the kernel when compiled and referenced. Deeper into the build tree, in directory "entry/syscall" is syscall_64.tbl. syscalls.h falls under "include/linux", and the syslog file is outside of the build tree, closer to the operating system's rro, at "var/log".

Building and Running:
To build the environment, the system call must be listed in the appropriate locations in the build tree, and the kernel must be compiled in order to reference the new information. The addtest.c can be used to test if the system call functions properly. use ">sudo gcc addtest.c" to compile, then ">./a.out" to run the program. The program will print the result to the terminal, and the result of the system call can be seen in the system logs by using ">dmesg".
