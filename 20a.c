/*
============================================================================
Name : 20a.c
Author : Gaurav Verma
Description :  Write two programs so that both can communicate by FIFO -Use one way communication.


Date: 19th Sept, 2024.
============================================================================
*/
#include <sys/types.h> // Import for `mkfifo` & `open`
#include <sys/stat.h>  // Import for `mkfifo` & `open`
#include <fcntl.h>     // Import for `open`
#include <unistd.h>    // Import for `write`
#include <stdio.h>     // Import for `perror`

void main()
{
    char *s; // Data to be sent through the buffer
    int fd;  // File descriptor of the FIFO file
    long int size = 100;
    char *file = "./20-fifo";
    mkfifo(file, S_IRWXU);
    while (1)
    {
        fd = open(file, O_WRONLY);
        if (fd == -1)
            perror("Error");
        else
        {
            printf("Write message here: ");
            int l = getline(&s, &size, stdin);
            write(fd, s, l);
            printf("\n");
            close(fd);
        }
    }
}