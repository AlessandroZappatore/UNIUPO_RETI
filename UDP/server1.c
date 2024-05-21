#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <limits.h>

int main(int argc, char *argv[])
{

    int simpleSocket = 0;
    int simplePort = 12345;
    int returnStatus = 0;
    struct sockaddr_in simpleServer, clientName;

    if (1 != argc)
    {

        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    simpleSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (simpleSocket == -1)
    {

        fprintf(stderr, "Could not create a socket!\n");
        exit(1);
    }
    else
    {
        fprintf(stderr, "Socket created!\n");
    }

    memset(&simpleServer, '\0', sizeof(simpleServer));
    simpleServer.sin_family = AF_INET;
    simpleServer.sin_addr.s_addr = htonl(INADDR_ANY);
    simpleServer.sin_port = htons(simplePort);

    /*  bind to the address and port with our socket  */
    returnStatus = bind(simpleSocket, (struct sockaddr *)&simpleServer, sizeof(simpleServer));

    if (returnStatus == 0)
    {
        fprintf(stderr, "Bind completed!\n");
    }
    else
    {
        fprintf(stderr, "Could not bind to address!\n");
        close(simpleSocket);
        exit(1);
    }

    while (1)
    {

        socklen_t clientNameLength = sizeof(clientName);
        char buffer[1024];

        for (int i = 0; i < 30; i++)
        {
            memset(buffer, '\0', sizeof(buffer));
            returnStatus = recvfrom(simpleSocket, buffer, sizeof(buffer), 0, (struct sockaddr *)&clientName, &clientNameLength);
            printf("status: %d, %s\n", returnStatus, buffer);

            if (returnStatus > 0)
            {
                sendto(simpleSocket, buffer, strlen(buffer), 0, (struct sockaddr *)&clientName, clientNameLength);
            }
        }
    }

    close(simpleSocket);
    return 0;
}
