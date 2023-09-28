// Server side implementation of UDP client-server model
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 9991
#define MAXLINE 1024

char *strrev(char *str);

// Driver code
int main()
{
    int current_pid = getpid();
	// printf("Program pid = %d\n", current_pid);
    FILE *fptr = fopen("/tmp/cudp.pid", "w");
    if (fptr != NULL)
    {
        fprintf(fptr, "%d", current_pid);
        fclose(fptr);
    }
    else
    {
        return -1;
    }
    
    int sockfd;
    char buffer[MAXLINE];
    const char *hello = "Hello from server";
    struct sockaddr_in servaddr, cliaddr;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&servaddr,
             sizeof(servaddr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    socklen_t len;
    int n;

    while (1)
    {
        len = sizeof(cliaddr); // len is value/result

        n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                     MSG_WAITALL, (struct sockaddr *)&cliaddr,
                     &len);
        buffer[n] = '\0';
        // printf("Client : %s\n", buffer);



        sendto(sockfd, (const char *)strrev(buffer), strlen(hello),
               MSG_CONFIRM, (const struct sockaddr *)&cliaddr,
               len);
        // std::cout << "Hello message sent." << std::endl;
    }

    return 0;
}

char *strrev(char *str)
{
    if (!str || ! *str)
        return str;

    int i = strlen(str) - 1, j = 0;

    char ch;
    while (i > j)
    {
        ch = str[i];
        str[i] = str[j];
        str[j] = ch;
        i--;
        j++;
    }
    return str;
}
