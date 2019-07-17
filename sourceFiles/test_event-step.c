#include "../headerFiles/header.h"

int game_event_hostname(char *hostname)
{
    int quit = 0;
    SDL_Event event;
    int size = my_strlen(hostname);

    char hostname[30] = {0};
    char port[30] = {0};

    int stepConnection = 0;
    char *currentText = hostname;

    int isTypingText = 1;

    while (SDL_PollEvent(&event) != 0)
    {
        //User requests quit
        switch (event.type)
        {
        case (SDL_QUIT):
            quit = -1;
        case (SDL_TEXTINPUT):
            strcat(currentText, event.text.text);
            break;
        case (SDL_KEYDOWN):
            switch (event.key.keysym.sym)
            {
            case SDLK_BACKSPACE:
                strcpy(currentText, "");
                break;
            case SDLK_DOWN:
                stepConnection++;
                if (stepConnection == 1)
                {
                    currentText = port;
                }
            }
        }
    }

    return quit;
}
