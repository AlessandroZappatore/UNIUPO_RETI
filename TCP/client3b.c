#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    int simpleSocket = 0;
    int simplePort = 0;
    int returnStatus = 0;
    char buffer[256] = "";
    struct sockaddr_in simpleServer;

    if (1 != argc)
    {

        fprintf(stderr, "Usage: %s <server> <port>\n", argv[0]);
        exit(1);
    }

    /* create a streaming socket      */
    simpleSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (simpleSocket == -1)
    {

        fprintf(stderr, "Could not create a socket!\n");
        exit(1);
    }
    else
    {
        fprintf(stderr, "Socket created!\n");
    }

    /* retrieve the port number for connecting */
    simplePort = 12345;

    /* setup the address structure */
    /* use the IP address sent as an argument for the server address  */
    // bzero(&simpleServer, sizeof(simpleServer));
    memset(&simpleServer, '\0', sizeof(simpleServer));
    simpleServer.sin_family = AF_INET;
    // inet_addr(argv[2], &simpleServer.sin_addr.s_addr);
    simpleServer.sin_addr.s_addr = inet_addr("127.0.0.1");
    simpleServer.sin_port = htons(simplePort);

    /*  connect to the address and port with our socket  */
    returnStatus = connect(simpleSocket, (struct sockaddr *)&simpleServer, sizeof(simpleServer));

    if (returnStatus == 0)
    {
        fprintf(stderr, "Connect successful!\n");
    }
    else
    {
        fprintf(stderr, "Could not connect to address!\n");
        close(simpleSocket);
        exit(1);
    }

    int x;
    char stringa[1024];

    printf("Inserire il numero di iterazioni: ");
    if (scanf("%d", &x) != 1) {
        fprintf(stderr, "Invalid input for number of iterations.\n");
        close(simpleSocket);
        exit(1);
    }

    write(simpleSocket, &x, sizeof(x));
    for (int i = 0; i < x; i++)
    {
        memset(buffer, '\0', sizeof(buffer));

        printf("Inserire la stringa numero %d: ", i + 1);
        scanf("%s", stringa);
        write(simpleSocket, stringa, strlen(stringa));
        returnStatus = read(simpleSocket, buffer, sizeof(buffer) - 1);
        if (returnStatus > 0)
        {
            buffer[returnStatus] = '\0'; // Ensure null-termination
            printf("%d: %s\n", returnStatus, buffer);
        }
        else
        {
            fprintf(stderr, "Return Status = %d \n", returnStatus);
        }
    }

    /* get the message from the server   */

    close(simpleSocket);
    return 0;
}
