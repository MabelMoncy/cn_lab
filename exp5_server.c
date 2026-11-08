#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX 20

int main()
{
    int s, ns, n, a[MAX][MAX];
    char result[50];
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);

    s = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    bind(s, (struct sockaddr *)&server, sizeof(server));
    listen(s, 3);

    printf("Waiting for client connection...\n");
    ns = accept(s, (struct sockaddr *)&client, &len);

    read(ns, &n, sizeof(n));
    read(ns, a, sizeof(a));

    int upper = 1, lower = 1, diagonal = 1;

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(i > j && a[i][j] != 0) upper = 0;
            if(i < j && a[i][j] != 0) lower = 0;
            if(i != j && a[i][j] != 0) diagonal = 0;
        }
    }

    if(diagonal)
        strcpy(result, "Diagonal Matrix");
    else if(upper)
        strcpy(result, "Upper Triangular Matrix");
    else if(lower)
        strcpy(result, "Lower Triangular Matrix");
    else
        strcpy(result, "Neither Upper nor Lower nor Diagonal");

    write(ns, result, sizeof(result));
    printf("Matrix Type sent to Client: %s\n", result);

    close(ns);
    close(s);
    return 0;
}