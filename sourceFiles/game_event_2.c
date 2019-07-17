#include "../headerFiles/header.h"

int game_event_hostname(char *hostname)
{
    int quit = 0;
    SDL_Event event;
    int size = my_strlen(hostname);

    while (SDL_PollEvent(&event) != 0)
    {
        //User requests quit
        switch (event.type)
        {
        case (SDL_QUIT):
            quit = -1;
        case (SDL_TEXTINPUT):
            strcat(hostname, event.text.text);
            break;
        case (SDL_KEYDOWN):
            switch (event.key.keysym.sym)
            {
            case SDLK_BACKSPACE:
                strcpy(hostname, "");
                break;
            case SDLK_DOWN:
                quit = 2;
            }
        }
    }

    return quit;
}

int game_event_port(char *port)
{

    int quit = 2;
    SDL_Event event;
    int size = my_strlen(port);

    while (SDL_PollEvent(&event) != 0)
    {
        //User requests quit
        switch (event.type)
        {
        case (SDL_QUIT):
            quit = -1;
        case (SDL_TEXTINPUT):
            strcat(port, event.text.text);
            break;
        case (SDL_KEYDOWN):
            switch (event.key.keysym.sym)
            {
            case SDLK_BACKSPACE:
                strcpy(port, "");
                break;
            case SDLK_DOWN:
                quit = 0;
            }
        }
    }

    return quit;
}