#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX 1024

int main()
{
    int sockfd;
    char message[MAX], buffer[MAX * 5];

    struct sockaddr_in server;
    socklen_t len = sizeof(server);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

    printf("Enter sentence:\n");
    fgets(message, MAX, stdin);

    sendto(sockfd, message, strlen(message) + 1, 0,
           (struct sockaddr *)&server, len);

    recvfrom(sockfd, buffer, sizeof(buffer), 0,
             (struct sockaddr *)&server, &len);

    printf("\nTranslated Sentence:\n%s\n", buffer);

    close(sockfd);
    return 0;
}