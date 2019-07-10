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
    int client1;
    int client2;
    int client3;
    socklen_t client_addr_len;
    fd_set read_fs;         //structure pour manager les files descriptors
    struct timeval timeout; //on va utiliser pour le timeout

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
    //acceptation des clients
    puts("en attente d'accepation de nouveaux clients");
    client1 = accept(mysocket, (struct sockaddr *)&addr, &client_addr_len);
    client2 = accept(mysocket, (struct sockaddr *)&addr, &client_addr_len);

    //ici les accept ne sont pas dynamique mais on peut les mettre dans le select pour que dès que le socket reçois une info on puisse accepter le client, pour le moment il est bloquant
    if (client1 < 0 || client2 < 0)
    {
        perror("accept()");
        return 1;
    }
    puts("new clients");

    while (1) //boucle infini pour laisser le server tourner
    {
        FD_ZERO(&read_fs); //initialiser read fs à zéro important de faire cela à chaque tour de boucle
        FD_SET(mysocket, &read_fs);
        FD_SET(client1, &read_fs); //on peut faire des fd_set en boucle
        FD_SET(client2, &read_fs);

        select(client2 + 1, &read_fs, NULL, NULL, NULL);

        if (FD_ISSET(mysocket, &read_fs))
        {
            client1 = accept(mysocket, (struct sockaddr *)&addr, &client_addr_len);
            client2 = accept(mysocket, (struct sockaddr *)&addr, &client_addr_len);
            if (client1 < 0 || client2 < 0)
            {
                perror("accept()");
                return 1;
            }
            puts("new clients");
        }

        if (FD_ISSET(client1, &read_fs)) //cette fonction repère les changements dans le file descriptor correspondant
        {
            if (read_client(client1) == -1)
            {
                puts("client1 disconnected");
                close(client1);
                client1 = -1;
            }
        }
        else if (FD_ISSET(client2, &read_fs))
        {
            if (read_client(client2) == -1)
            {
                puts("client2 disconnected");
                close(client2);
            }
        }

        if (client1 == -1 && client2 == -1)
        {
            break;
        }
        puts("looping");
    }
    close(mysocket);
}

//code que je garde aucas ou pour reveenir à la base

//read pour un client étape 2 (pour se rappeler de la base mais cette fonction a été déplacée)
// char buff[128];
// memset(buff, '\0', 128);

//write(client, "hello manu :", 12); si on veut un message d'accueil personnalisé
//le server récupère le message du client si n est positif sinon message d'erreur utilisé rcv si on veut une utilisation bien spéciale mais ne pas utilisé de rcv avec un flag à 0 ça ne sert à rien
// while ((n = read(client, buff, 128)) > 0)
// {
//     int length = my_strlen(buff);
//     printf("received : %i octet and %s", length, buff);

//     write(client, buff, length);
//     memset(buff, '\0', 128);
// }

// si on utilise pas close pour ne pas avoir l'erreur  "already bind" quand on ferme un server
//binder le server au socket ET éviter l'erreur bind en cas d'arrêt et redémarrage' du server
