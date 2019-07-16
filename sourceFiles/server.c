#include "../headerFiles/header.h"

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "le format de la commande doit être : %s hostAdresse port\n", argv[0]);
        return (0);
    }
    //variable pour la création du socket du serveur
    int server_socket;
    struct sockaddr_in addr;

    //variables pour gérer la comparaison des sockets descriptor
    int max_sd;
    //variable pour la fonction accept
    int new_socket;
    int clients_array[4];
    //initialisation du tableau à zéro
    int i = 0;
    while (i < 4)
    {
        clients_array[i] = 0;

        i++;
    }
    int max_client = 4;

    socklen_t client_addr_size = sizeof(addr); //attention cette valeur attend une taille donc un sizeof!!!!!!!!!!!!!!!!
    //on peut aussi déclarer sockelen_t direct dans la fonction accept

    //variables pour le select
    fd_set read_fs;         //structure pour manager les files descriptors
    struct timeval timeout; //on va utiliser pour le timeout

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0)
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

    //créer la scoket server
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &addr, sizeof(int)) == -1)
    {
        perror("setsockopt");
        pthread_exit(NULL);
    }

    //binder la socket
    if (bind(server_socket, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind()");
        return 1;
    }
    //vérifier que le server ecoute le port concerné
    if (listen(server_socket, 5) < 0)
    {
        perror("listen()");
        return 1;
    }
    //acceptation des clients
    puts("en attente d'accepation de nouveaux clients");
    int sd = 0; //socket descriptor "dynamique" qu'on va utliser pour le select

    while (1) //boucle infini pour laisser le server tourner
    {
        FD_ZERO(&read_fs); //initialiser read fs à zéro important de faire cela à chaque tour de boucle
        FD_SET(server_socket, &read_fs);
        max_sd = server_socket; //le plus grand des socket descriptor

        //comparaison des socket descriptor
        //on parcours le tableau de clients pour voir si on a des sd valables et on met le plus grand au max
        for (int i = 0; i < max_client; i++)
        {

            sd = clients_array[i]; //on remet sd à zéro si tous les clients sont nuls comme on a indiqué plus bas en cas de déconnexion de ces derniers

            //si le socket descriptor existe donc != 0
            //si le socket n'est pas valable il ne sera plus fd_set et donc le select ne le suivra plus on n'entre pas dans la condition ci-dessous
            if (sd > 0)
            {
                FD_SET(sd, &read_fs);
            }
            //si il est plus grand que le max il devient le max pour qu'on puisse l'utiliser avec le select
            if (sd > max_sd)
            {
                max_sd = sd;
            }
        }

        select(max_sd + 1, &read_fs, NULL, NULL, NULL);

        if (FD_ISSET(server_socket, &read_fs)) //détecte les changements sur le socket_server normalement l'arrivée d'un nouveau client
        {
            //ici on a détecté une nouvelle demande de client on essaye de l'accpeter
            //géréer ici une nouvelle demande supérieur à la taille du tableau

            if ((new_socket = accept(server_socket, (struct sockaddr *)&addr, &client_addr_size)) < 0)
            {
                perror("accept");
                return 1;
            }
            puts("detect client");
            if (new_socket >= 8)
            {
                puts("nombre client max atteint");
                        }
            //client accepté ? on parcours le tableau pour affecter la new socket

            for (int i = 0; i < max_client; i++)
            {
                if (clients_array[i] == 0)
                {

                    clients_array[i] = new_socket;

                    printf("add new client :%i", new_socket);
                    if (send(new_socket, "hello\n", 6, MSG_NOSIGNAL) < 0)
                    {
                        puts("send failed");
                        return 1;
                    }

                    break;
                }
            }
        }
        //on parcours le tableau des clients
        for (i = 0; i < max_client; i++)
        {
            sd = clients_array[i];

            if (FD_ISSET(sd, &read_fs))
            {
                if (read_client(sd) == -1)
                {
                    puts("client disconnected");
                    close(sd);
                    clients_array[i] = 0;
                }
            }
        }

        puts("looping");
    }
    close(server_socket);
}
