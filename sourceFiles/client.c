#include "../headerFiles/header.h"
#include <string.h>

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
    char message[128];
    //read(mysocket, message, 128);
    //printf("%s", message);
    //envoyer des messages
    while (1)
    {

        //on remet à zéro le message à chaque boucle
        memset(message, '\0', 128);

        printf("écrivez votre message : \n"); //invitation de commande pour l'utilisateur
        fgets(message, 128, stdin);
        //le programme attend qu'on rentre une valeur
        int length = my_strlen(message); //une fois le message écris on calcule son length

        if (write(mysocket, message, length) < 0)
        {
            puts("send failed");
            close(mysocket);
            return 1;
        }

        read(mysocket, message, 128);
        printf("reçu par le server: %s", message);
    }
    close(mysocket);
    return 0;
}
