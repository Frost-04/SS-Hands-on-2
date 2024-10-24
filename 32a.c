/*
============================================================================
Name : 32a.c
Author : Gaurav Verma
Description : Write a program to implement semaphore to protect any critical section.
              a. rewrite the ticket number creation program using semaphore
              b. protect shared memory from concurrent write access
              c. protect multiple pseudo resources ( may be two) using counting semaphore
              d. remove the created semaphore 
Date: 20th Sept, 2024.
============================================================================
*/

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/sem.h>

typedef union semun {
    int val;                  
    struct semid_ds *buf;
    unsigned short int *array; // Array for GETALL, SETALL
} semun;

int main() {
    semun arg;
    key_t key = ftok(".", 331);
    int semid = semget(key, 1, IPC_CREAT | 0700); // Create semaphore
    if (semid == -1) {
        perror("Failed to create semaphore");
        return 1;
    }

    arg.val = 1; // Initialize binary semaphore
    semctl(semid, 0, SETVAL, arg);

    struct sembuf sem_op;
    sem_op.sem_num = 0; // Semaphore number
    sem_op.sem_flg = 0; // No special flags

    printf("Entering critical section...\n");

    // Lock critical section
    sem_op.sem_op = -1; // Wait operation
    semop(semid, &sem_op, 1);

    // Critical section
    printf("Inside critical section...press enter to continue\n");
    getchar();

    int data;
    int fd = open("./ticket.txt", O_RDWR | O_CREAT, S_IRWXU);
    if (fd == -1) {
        perror("Error while opening file!");
        return 1;
    }

    int n = read(fd, &data, sizeof(data));
    if (n == 0) {
        data = 1;
    } else {
        data += 1; // Increment ticket number
        lseek(fd, 0, SEEK_SET); // Reset file pointer
    }
    write(fd, &data, sizeof(data));
    printf("Ticket number is: %d\n", data);
    printf("Ticket number stored in file.\n");

    printf("Exiting critical section...\n");

    // Unlock critical section
    sem_op.sem_op = 1; // Signal operation
    semop(semid, &sem_op, 1);

    // Remove semaphore
    if (semctl(semid, 0, IPC_RMID) == -1) {
        perror("Failed to remove semaphore");
    }

    return 0;
}
