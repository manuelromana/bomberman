#include "../headerFiles/header.h"

int main(int argc, char *argv[])
{
    stGame *game = game_init_2();
    SDL_Event event;

    int mysocket;
    struct sockaddr_in addr;
    int portno;
    char message[128];

    int quit = 0;
    char hostname[50];
    char port[50];
    
    for (int i = 0; i < 50; i++) {
        hostname[i] = '\0';
        port[i] = '\0';
    }

    int step = 0;
    char *currentText = hostname;

    while (step != -1) {
        while (SDL_PollEvent(&event) != 0) {
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
                    break;
                case SDLK_UP:
                case SDLK_DOWN:
                case SDLK_RIGHT:
                case SDLK_LEFT:
                case SDLK_SPACE:
                    send_key(event.key.keysym.sym, mysocket);
                    break;
                }
            }
        }

        if (step == 0) {
            game_draw_hostname(game, hostname);
        } else if (step == 1) {
            game_draw_port(game, port);
        } else if (step == 2) {

            mysocket = socket(AF_INET, SOCK_STREAM, 0);
            if (mysocket < 0) {
                perror("socket()");
                break;
            }

            portno = atoi(port);
            addr.sin_addr.s_addr = inet_addr(hostname);
            addr.sin_port = htons(portno);
            addr.sin_family = AF_INET;

            if (connect(mysocket, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
                perror("connect()");
                break;
            }

            memset(message, '\0', 128);
            read(mysocket, message, 128);
            printf("%s\n", message);
            step++;
        }

        SDL_Delay(30);
    }

    TTF_Quit();

    game_destroy_2(game);
    close(mysocket);

    return (EXIT_SUCCESS);
}
