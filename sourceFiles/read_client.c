#include "../headerFiles/header.h"

//   fn read_client
//   brief read and print recv data from the client file descriptor until he is connected

//   param client file descriptor of the client to use
//  return int

int read_client(int client)
{
    int n;
    char buff[128];

    if (client == -1)
    {
        return 1;
    }

    n = 0; //utilité ?
    memset(buff, '\0', 128);
    while ((n = recv(client, buff, 128, 0)) >= 0)
    {
        if (n == 0)
        {
            return -1;
        }

        printf("received %s", buff);

        if (buff[n - 1] == '\n')
        {
            memset(buff, '\0', 128);
            break;
        }
    }
    return n;
}