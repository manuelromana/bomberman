#include "../headerFiles/header.h"

int read_client(int client)
{
    int n = 0;
    char buff[128];

    if (client == -1)
        return 1;
    memset(buff, '\0', 128);
    while ((n = recv(client, buff, 128, 0)) >= 0) {
        if (n == 0)
            return -1;

        printf("received %s", buff);

        if (buff[n - 1] == '\n') {
            memset(buff, '\0', 128);
            break;
        }
    }
    return n;
}