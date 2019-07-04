#include "../headerFiles/header.h"

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "le format de la commande doit être : %s hostAdresse port\n", argv[0]);
        return (0);
    }
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
    //portno = numéro de port
    int portno; //numéro de port
    portno = atoi(argv[2]);
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_port = htons(portno);
    addr.sin_family = AF_INET;

    //binder le server au socket et éviter l'erreur bind en cas de redérrage du server

    if (setsockopt(mysocket, SOL_SOCKET, SO_REUSEADDR, &addr, sizeof(int)) == -1)
    {
        perror("setsockopt");
        pthread_exit(NULL);
    }
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

    int n;
    char buff[128];
    while (1)
    {
        puts("en attente d'accepation");
        client = accept(mysocket, (struct sockaddr *)&addr, &client_addr_len);
        if (client < 0)
        {
            perror("accepts()");
            return -1;
        }
        puts("new client");
        memset(buff, '\0', 128);
        //write(client, "hello manu :", 12);
        while ((n = read(client, buff, 10)) > 0)
        {
            int length = my_strlen(buff);
            printf("received : %i octet and %s\n", length, buff);

            write(client, buff, length);
            memset(buff, '\0', 128);
        }
    }
    close(mysocket);
}