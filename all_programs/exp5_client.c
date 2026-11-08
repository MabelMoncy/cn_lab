#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX 20

int main()
{
    int sock, n, a[MAX][MAX];
    char result[50];
    struct sockaddr_in server;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

    connect(sock, (struct sockaddr *)&server, sizeof(server));

    printf("Enter order of matrix: ");
    scanf("%d", &n);

    srand(time(0));
    printf("\nGenerated Matrix:\n");

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            a[i][j] = rand() % 2;
            printf("%4d", a[i][j]);
        }
        printf("\n");
    }

    write(sock, &n, sizeof(n));
    write(sock, a, sizeof(a));

    read(sock, result, sizeof(result));
    printf("\nMatrix Type Received from Server: %s\n", result);

    close(sock);
    return 0;
}