/*
============================================================================
Name : 34aserver.c
Author : Gaurav Verma
Description :  Write a program to create a concurrent server.
               a. use fork
               b. use pthread_create
Date: 21th Sept, 2024.
============================================================================
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <unistd.h>
void main()
{
    int socktd = socket(AF_INET, SOCK_STREAM, 0);
    if (socktd == -1)
    {
        perror("Error when creating socket");
    }
    printf("server Socket created\n");

    // server info
    struct sockaddr_in server, client;
    server.sin_addr.s_addr = htonl(INADDR_ANY); // host to network long
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);

    int bindS = bind(socktd, (struct sockaddr *)&server, sizeof(server));
    if (bindS == -1)
    {
        perror("Error while binding name to socket!");
        _exit(0);
    }
    printf("Binding to server socket was successful!\n");

    // listen for connection
    int listenS = listen(socktd, 3);
    if (listenS == -1)
    {
        perror("Error while trying to listen to Connections");
        _exit(0);
    }
    printf("Listning from Connection \n");

    while (1)
    {
        int client_size = (int)sizeof(client);
        int connectionfd = accept(socktd, (struct sockaddr *)&client, &client_size);
        if (connectionfd == -1)
        {
            perror("Error while accepting Connection\n");
            _exit(0);
        }
        else
        {
            if (fork() == 0)
            {
                // In child
                char buf[100];
                printf("Write massage form server to client: \n");
                scanf("%[^\n]", buf);
                // write fron server to connection fd
                write(connectionfd, buf, sizeof(buf));

                read(connectionfd, buf, 100);
                printf("Data from client : %s\n",buf);
            }
            else
            {
                // parent
                // close connectionfd for client
                close(connectionfd);
            }
        }
    }

    // closing socket
    close(socktd);
}