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
    int sd = 0;
    while (1) //boucle infini pour laisser le server tourner
    {
        FD_ZERO(&read_fs); //initialiser read fs à zéro important de faire cela à chaque tour de boucle
        FD_SET(server_socket, &read_fs);
        max_sd = server_socket; //le plus grand des socket descriptor

        //comparaison des socket descriptor
        //on parcours le tableau de clients pour voir si on a des sd valables et on met le plus grand au max
        int j = 0;
        while (j < max_client)
        {

            sd = clients_array[j];

            //si le socket descriptor existe donc != 0
            if (sd > 0)
            {
                FD_SET(sd, &read_fs);
            }
            //si il est plus grand que le max il devient le max pour qu'on puisse l'utiliser avec le select
            if (sd > max_sd)
            {
                max_sd = sd;
            }
            j++;
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

            //client accepté ? on parcours le tableau pour affecter la new socket
            int k = 0;
            while (k < max_client)
            {
                if (clients_array[k] == 0)
                {

                    clients_array[k] = new_socket;

                    puts("add new client");
                    break;
                }
                k++;
            }
        }
        //else its some IO operation on some other socket
        for (i = 0; i < max_client; i++)
        {
            sd = clients_array[i];

            if (FD_ISSET(sd, &read_fs))
            {
                if (read_client(sd) == -1)
                {
                    puts("client1 disconnected");
                    close(sd);
                    sd = 0;
                }
            }
        }

        puts("looping");
    }
    close(server_socket);
}
