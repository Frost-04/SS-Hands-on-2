/*
============================================================================
Name : 2.c
Author : Gaurav Verma
Description :   Write a program to print the system resource limits. Use getrlimit system call. 

Date: 16th Sept, 2024.
============================================================================
*/
#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>
void print(char *text, rlim_t current, rlim_t maxlim, char *unit)
{
    printf("%s - \n", text);

    printf("\tSoft Limit: ");
    if (current == RLIM_INFINITY)
        printf("Unlimited\n");
    else
        printf("%ld %s\n", current, unit);

    printf("\tHard Limit: ");
    if (maxlim == RLIM_INFINITY)
        printf("Unlimited\n");
    else
        printf("%ld %s\n", maxlim, unit);
}

void main()
{
    int status;                   // Determines the success of the `getrlimit` call
    struct rlimit resLim; // Holds the hard & soft limits for a resource

    // RLIMIT_AS -> This  is  the maximum size of the process's virtual memory (address space).
    status = getrlimit(RLIMIT_AS, &resLim);
    if (status == -1)
        perror("Error while getting RLIMIT_AS!");
    else
        print("Max size of process's virtual memory", resLim.rlim_cur, resLim.rlim_max, "bytes");

    // RLIMIT_CORE -> Max size of a core file
    status = getrlimit(RLIMIT_CORE, &resLim);
    if (status == -1)
        perror("Error while getting RLIMIT_CORE!");
    else
        print("Max size of a core file", resLim.rlim_cur, resLim.rlim_max, "bytes");

    // RLIMIT_CPU -> Amount of CPU time that the process can consume
    status = getrlimit(RLIMIT_CPU, &resLim);
    if (status == -1)
        perror("Error while getting RLIMIT_CPU!");
    else
        print("Max CPU time that the process can consume", resLim.rlim_cur, resLim.rlim_max, "seconds");

    // RLIMIT_DATA -> Maximum size of the process's data segment
    status = getrlimit(RLIMIT_DATA, &resLim);
    if (status == -1)
        perror("Error while getting RLIMIT_DATA!");
    else
        print("Max size of process's data segement", resLim.rlim_cur, resLim.rlim_max, "bytes");

    // RLIMIT_FSIZE -> Maximum size of files that  the  process  may  create
    status = getrlimit(RLIMIT_FSIZE, &resLim);
    if (status == -1)
        perror("Error while getting RLIMIT_FSIZE!");
    else
        print("Max size of files that  the  process  may  create", resLim.rlim_cur, resLim.rlim_max, "bytes");

    // RLIMIT_LOCKS -> Maximum number of locks that a process may establish
    status = getrlimit(RLIMIT_LOCKS, &resLim);
    if (status == -1)
        perror("Error while getting RLIMIT_LOCKS!");
    else
        print("Max number of locks that a process may establish", resLim.rlim_cur, resLim.rlim_max, "");

    // RLIMIT_MEMLOCK -> Maximum number of bytes of memory that may be locked into RAM
    status = getrlimit(RLIMIT_MEMLOCK, &resLim);
    if (status == -1)
        perror("Error while getting RLIMIT_MEMLOCK!");
    else
        print("Max number of bytes of memory that may be locked into RAM", resLim.rlim_cur, resLim.rlim_max, "bytes");

    // RLIMIT_MSGQUEUE -> Maximum number of bytes that can be allocated for POSIX message queues
    status = getrlimit(RLIMIT_MSGQUEUE, &resLim);
    if (status == -1)
        perror("Error while getting RLIMIT_MSGQUEUE!");
    else
        print("Max number of bytes of that can be allocated for POSIX message queues", resLim.rlim_cur, resLim.rlim_max, "bytes");

    // RLIMIT_NICE -> Ceiling of the process's nice value
    status = getrlimit(RLIMIT_NICE, &resLim);
    if (status == -1)
        perror("Error while getting RLIMIT_NICE!");
    else
        print("Ceiling of the process's nice value", resLim.rlim_cur, resLim.rlim_max, "");

    // RLIMIT_NOFILE -> specifies a value one greater than the maximum file descriptor number that can be opened by this process
    status = getrlimit(RLIMIT_NOFILE, &resLim);
    if (status == -1)
        perror("Error while getting RLIMIT_NOFILE!");
    else
        print("Max file descriptor", resLim.rlim_cur, resLim.rlim_max, "bytes");

    // RLIMIT_NPROC -> Limit on the number of threads
    status = getrlimit(RLIMIT_NPROC, &resLim);
    if (status == -1)
        perror("Error while getting RLIMIT_NPROC!");
    else
        print("Limit on the number of threads", resLim.rlim_cur, resLim.rlim_max, "");

    // RLIMIT_RSS -> Limit on the number of virtual pages resident in the RAM
    status = getrlimit(RLIMIT_RSS, &resLim);
    if (status == -1)
        perror("Error while getting RLIMIT_RSS!");
    else
        print("Limit on the  number of virtual pages resident in the RAM", resLim.rlim_cur, resLim.rlim_max, "bytes");

    // RLIMIT_RTPRIO -> a ceiling on the real-time priority
    status = getrlimit(RLIMIT_RTPRIO, &resLim);
    if (status == -1)
        perror("Error while getting RLIMIT_RTPRIO!");
    else
        print("Ceiling on the real-time priority", resLim.rlim_cur, resLim.rlim_max, "");

    // RLIMIT_RTTIME -> Amount of CPU time that a  process scheduled  under a real-time scheduling policy may consume without making a blocking system call.
    status = getrlimit(RLIMIT_RTTIME, &resLim);
    if (status == -1)
        perror("Error while getting RLIMIT_RTTIME!");
    else
        print("Amount of CPU time that a  process scheduled  under a real-time scheduling policy", resLim.rlim_cur, resLim.rlim_max, "ms");

    // RLIMIT_SIGPENDING ->The number of signals that may be queued
    status = getrlimit(RLIMIT_SIGPENDING, &resLim);
    if (status == -1)
        perror("Error while getting RLIMIT_SIGPENDING!");
    else
        print("The number of signals that may be queued", resLim.rlim_cur, resLim.rlim_max, "");

    // RLIMIT_STACK -> Maximum  size of the process stack
    status = getrlimit(RLIMIT_SIGPENDING, &resLim);
    if (status == -1)
        perror("Error while getting RLIMIT_STACK!");
    else
        print("Maximum  size of the process stack", resLim.rlim_cur, resLim.rlim_max, "bytes");
}