#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int my_strlen(char *str)
{
    int i;
    i = 0;
    while (str[i] != 0)
    {
        ++i;
    }
    return (i);
}

int main(int argc, char *argv[])
{

    // on fait un client qui va prendre des arguments lors de son lancement avec argc (le nombre d'arguments) et argv les arguments qui doivent être rentrés
    //argv[0] : c'est le nom du binaire
    //argv[1] : adresse de l'hôte (on peut aussi la mettre en bianaire ou littéral genre localhost)
    //argv[2] : port de l'hôte

    // on vérifie qu'il y a le bom nombre d'argument
    if (argc < 3)
    {
        fprintf(stderr, "le format de la commande doit être : %s hostAdresse port\n", argv[0]);
        return (0);
    }

    // créer un socket
    int mysocket;
    struct sockaddr_in addr;
    mysocket = socket(AF_INET, SOCK_STREAM, 0);
    if (mysocket < 0)
    {
        perror("socket()");
        return -1;
    }

    //récupérer les arguments et les transformer
    int portno; //numéro de port
    portno = atoi(argv[2]);
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_port = htons(portno);
    addr.sin_family = AF_INET;

    //tester la connection avec le server

    if (connect(mysocket, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("connect()");
        return 1;
    }

    //envoyer des messages

    char nom[20];
    printf("écrivez votre message : \n");
    fgets(nom, 10, stdin);
    int length = my_strlen(nom);
    //le programme attend qu'on rentre une valeur
    write(mysocket, nom, length);
    return 0;
}
