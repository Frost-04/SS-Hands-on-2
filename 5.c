/*
============================================================================
Name : 5.c
Author : Gaurav Verma
Description :   Write a program to print the system limitation of
                a. maximum length of the arguments to the exec family of functions.
                b. maximum number of simultaneous process per user id.
                c. number of clock ticks (jiffy) per second.
                d. maximum number of open files
                e. size of a page
                f. total number of pages in the physical memory
                g. number of currently available pages in the physical memory

Date: 16th Sept, 2024.
============================================================================
*/
#include<unistd.h>
#include<stdio.h>
void main()
{
    long value_buffer;
    // _SC_ARG_MAX -  Maximum length of the arguments to the exec family of functions.
    value_buffer=sysconf(_SC_ARG_MAX);
    printf("Maximum length of the arguments to the exec family of functions - %ld\n", value_buffer);

    // _SC_CHILD_MAX -  Maximum number of simultaneous process per user id.
    value_buffer = sysconf(_SC_CHILD_MAX);
    printf("Maximum number of simultaneous process per user id - %ld\n", value_buffer);

    // _SC_CLK_TCK -  Number of clock ticks (jiffy) per second.
    value_buffer = sysconf(_SC_CLK_TCK);
    printf("Number of clock ticks (jiffy) per second - %ld\n", value_buffer);

    // _SC_OPEN_MAX -  Maximum number of open files
    value_buffer = sysconf(_SC_OPEN_MAX);
    printf("Maximum number of open files - %ld\n", value_buffer);

    // _SC_PAGESIZE -  Size of a page
    value_buffer = sysconf(_SC_PAGESIZE);
    printf("Size of a page - %ld bytes\n", value_buffer);

    // _SC_PHYS_PAGES -  Total number of pages in the physical memory
    value_buffer = sysconf(_SC_PHYS_PAGES);
    printf("Total number of pages in the physical memory - %ld\n", value_buffer);

    // _SC_AVPHYS_PAGES -  Number of  currently available pages in the physical memory.
    value_buffer = sysconf(_SC_AVPHYS_PAGES);
    printf("Number of  currently available pages in the physical memory - %ld\n", value_buffer);
}