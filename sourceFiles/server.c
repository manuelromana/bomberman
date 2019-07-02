#include "../headerFiles/header.h"
int main()
{
    int mysocket;
    struct sockaddr_in addr;
    int client;
    socklen_t client_addr_len;
    mysocket = socket(AF_INET, SOCK_STREAM, 0);
    if (mysocket < 0)
    {
        perror("socket()");
        return -1;
    }

    //récupérer les arguments et les transformer

    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(1234);
    addr.sin_family = AF_INET;

    //binder le server au socket

    if (bind(mysocket, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind()");
        return 1;
    }
    //vérifier que le server ecoute le port concerné
    if (listen(mysocket, 5) < 0)
    {
        perror("listen()");
        return 1;
    }
    client = accept(mysocket, (struct sockaddr *)&addr, &client_addr_len);
    if (client < 0)
    {
        perror("accepts()");
        return -1;
    }
    write(client, "hello\n", 6);
    while (1)
    {
    }
}