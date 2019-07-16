#include "../headerFiles/header.h"

int game_event_2(char *test)
{
    int quit = 0;
    SDL_Event event;

    while (SDL_PollEvent(&event) != 0)
    {
        //User requests quit
        switch (event.type)
        {
        case (SDL_QUIT):
            quit = -1;
        case (SDL_TEXTINPUT):
            strcat(test, event.text.text);
            break;
        }
    }

    return quit;
}