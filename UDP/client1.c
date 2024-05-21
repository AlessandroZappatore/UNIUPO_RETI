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
    int simplePort = 12345;
    int returnStatus = 0;
    char buffer[256] = "";
    struct sockaddr_in simpleServer;

    if (argc != 1)
    {
        fprintf(stderr, "Usage: %s\n", argv[0]);
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
    simpleServer.sin_addr.s_addr = inet_addr("127.0.0.1");
    simpleServer.sin_port = htons(simplePort);

    int x = 30;
    char array[][10] = {"prima", "seconda", "terza", "quarta", "quinta", "prima", "seconda", "terza", "quarta", "quinta", "prima", "seconda", "terza", "quarta", "quinta", "prima", "seconda", "terza", "quarta", "quinta", "prima", "seconda", "terza", "quarta", "quinta", "prima", "seconda", "terza", "quarta", "quinta"};
    socklen_t serverLen = sizeof(simpleServer);

    for (int i = 0; i < x; i++)
    {
        memset(buffer, '\0', sizeof(buffer));
        strcpy(buffer, array[i]);

        sendto(simpleSocket, buffer, strlen(buffer), 0, (struct sockaddr *)&simpleServer, serverLen);
        returnStatus = recvfrom(simpleSocket, buffer, sizeof(buffer), 0, (struct sockaddr *)&simpleServer, &serverLen);

        if (returnStatus > 0)
        {
            printf("%d: %s\n", returnStatus, buffer);
        }
        else
        {
            fprintf(stderr, "Return Status = %d \n", returnStatus);
        }
    }

    close(simpleSocket);
    return 0;
}
