#include "../headerFiles/header.h"

int main(int argc, char *argv[])
{

    //initialiser le jeu
    stGame *game = game_init_2();
    SDL_Event event;

    int mysocket;
    struct sockaddr_in addr;
    int portno;
    char message[128];

    int quit = 0;
    char hostname[50];
    char port[50];
    for (int i = 0; i < 50; i++)
    {
        hostname[i] = '\0';
        port[i] = '\0';
    }

    int step = 0;
    char *currentText = hostname;

    while (step != -1)
    {

        while (SDL_PollEvent(&event) != 0)
        {
            //User requests quit
            switch (event.type)
            {
            case (SDL_QUIT):
                step = -1;
            case (SDL_TEXTINPUT):
                strcat(currentText, event.text.text);
                break;
            case (SDL_KEYDOWN):
                switch (event.key.keysym.sym)
                {
                case SDLK_BACKSPACE:
                    strcpy(currentText, "");
                    break;
                case SDLK_RETURN:
                    step++;
                    if (step == 1)
                    {
                        currentText = port;
                    }
                }
            }
        }

        if (step == 0) //quand quit = 2 on dessine l'invitation pour le port
        {
            game_draw_hostname(game, hostname);
        }
        else if (step == 1)
        {
            game_draw_port(game, port);
        }
        else if (step == 2)
        {

            mysocket = socket(AF_INET, SOCK_STREAM, 0);
            if (mysocket < 0)
            {
                perror("socket()");
                break;
            }

            //récupérer les arguments et les transformer
            //numéro de port
            portno = atoi(port);
            addr.sin_addr.s_addr = inet_addr(hostname);
            addr.sin_port = htons(portno);
            addr.sin_family = AF_INET;

            //tester la connection avec le server

            if (connect(mysocket, (struct sockaddr *)&addr, sizeof(addr)) < 0)
            {
                perror("connect()");
                break;
            }

            memset(message, '\0', 128);
            read(mysocket, message, 128);
            printf("%s\n", message);
            step++;
        }

        else if (step == 3)
        {
            memset(message, '\0', 128);

            printf("écrivez votre message : \n"); //invitation de commande pour l'utilisateur
            fgets(message, 128, stdin);
            //le programme attend qu'on rentre une valeur
            int length = my_strlen(message); //une fois le message écris on calcule son length

            //message utilisateur est écris sur le socket si jamais write return un int positif sinon message erreur ainsi le server peut le récupérer
            //et on utilise send car cette fonction catch les erreurs en cas de server interrompu
            if (send(mysocket, message, length, MSG_NOSIGNAL) < 0)
            {
                puts("send failed");
                close(mysocket);
                break;
            }
        }

        SDL_Delay(30);
    }
    //Arrêt de TTf
    TTF_Quit();
    //Destruction

    game_destroy_2(game);
    close(mysocket);

    return (EXIT_SUCCESS);
}
