/*
============================================================================
Name : 4.c
Author : Gaurav Verma
Description :   Write a program to measure how much time is taken to execute 100 getppid ( )
                system call. Use time stamp counter.

Date: 16 Sept, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

// using time stamp counter
unsigned long long rdtsc()
{
    unsigned long long dst;
    __asm__ __volatile__("rdtsc": "=A"(dst));
    return dst;
}

void main()
{
    long long int begin, end;

    begin = rdtsc();
    int iterations = 1;
    while (iterations <= 1000)
    {
        getppid();
        iterations += 1;
    }

    end = rdtsc();

    printf("time required : %llu\n", end - begin);
}