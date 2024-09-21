/*
============================================================================
Name : 19.c
Author : Gaurav Verma
Description : Create a FIFO file by
                a. mknod command
                b. mkfifo command
                c. use strace command to find out, which command (mknod or mkfifo) is better.
                c. mknod system call
                d. mkfifo library function


Date: 19th Sept, 2024.
============================================================================
*/


#include <stdio.h>
#include <sys/stat.h>
int main()
{
    int o = mkfifo("./mkfifo_syscall", S_IRWXU);
    if (o == 0)
    {
        printf("fifo special file is created\n");
    }

    int f = mknod("./fifo_using_mknode_sys_call", S_IRWXU | S_IFIFO, 0);
    if (f == 0)
    {
        printf("fifo special file is created\n");
    }
}