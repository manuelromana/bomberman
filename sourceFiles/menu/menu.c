#include "../../headerFiles/menu/menu.h"
#include "../../headerFiles/game/game.h" //pour les screensize

stMenu *menu_init(SDL_Window *pWindow, SDL_Renderer *pRenderer)
{
    stMenu *menu = {0};
    menu = malloc(sizeof(stMenu));

    TTF_Init();
    if (TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    menu->pWindow = pWindow;
    menu->pRenderer = pRenderer;

    menu->police1 = TTF_OpenFont(PATHFGRAFITI, 70);
    menu->police2 = TTF_OpenFont(PATHFNEON, 45);
    // menu_image_load(menu);
    menu->pTextChoix = font_load(menu, menu->police2, TXTSURFCHOIX);
    menu->pTextHostname = font_load(menu, menu->police1, TXTSURFHOSTNAME);
    menu->pTextPortname = font_load(menu, menu->police1, TXTSURFPORTNAME);
    menu->pTextWelcome = font_load(menu, menu->police1, TXTWELCOMESERVEUR);

    SDL_StartTextInput();

    return menu;
}

void menu_image_load(stMenu *menu)
{
    char *path = "../../assets/bomberman.png";
    menu->surface = IMG_Load(path);
    if (!menu->surface)
    {

        fprintf(stderr, "Erreur au chargement de l'image : %s,%s\n", path,
                IMG_GetError());
        menu_destroy_2(menu);
    }
    else
    {
        menu->texture = SDL_CreateTextureFromSurface(
            menu->pRenderer, menu->surface);
        if (!menu->texture)
        {
            fprintf(stderr, "Erreur au chargement de la texture : %s,%s\n",
                    path, SDL_GetError());
            menu_destroy_2(menu);
        }
        SDL_FreeSurface(menu->surface);
    }
}

void menu_event(SDL_Event event, int *step, char **currentText, char *hostname, char *port, int socket_target)
{
    while (SDL_PollEvent(&event) != 0)
    {
        switch (event.type)
        {
        case (SDL_QUIT):
            *step = -1;
        case (SDL_TEXTINPUT):
            strcat(*currentText, event.text.text);
            break;
        case (SDL_KEYDOWN):
            switch (event.key.keysym.sym)
            {
            case SDLK_BACKSPACE:
                strcpy(*currentText, "");
                break;
            case SDLK_RETURN:
                (*step)++;
                if (*step == 1)
                {
                    *currentText = hostname;
                }
                if (*step == 2)
                {
                    *currentText = port;
                }
                break;
            case SDLK_UP:
            case SDLK_DOWN:
            case SDLK_RIGHT:
            case SDLK_LEFT:
            case SDLK_SPACE:
                send_key(event.key.keysym.sym, socket_target);
                break;
            }
        }
    }
}

void menu_draw(stMenu *menu)
{
    SDL_SetRenderDrawColor(menu->pRenderer, 255, 255, 255, 255);
    SDL_RenderClear(menu->pRenderer);

    SDL_Rect menu_fond = {0, 0, SCREENSIZEX, SCREENSIZEY};
    SDL_RenderCopy(menu->pRenderer, menu->texturesMenu[0]->texture, NULL, &menu_fond);

    SDL_RenderPresent(menu->pRenderer);
}

void menu_draw_choix(stMenu *menu, char *choix)
{
    SDL_SetRenderDrawColor(menu->pRenderer, 255, 255, 255, 255);
    SDL_RenderClear(menu->pRenderer);

    SDL_Rect modeChoixText = {MENUDISPLAYX, MENUDISPLAYY, MENUDISPLAYW, MENUDISPLAYH};
    SDL_RenderCopy(menu->pRenderer, menu->pTextChoix, NULL, &modeChoixText);

    if (*choix != '\0')
    {
        menu->pInputText = font_load(menu, menu->police2, choix);

        menu->inputPositionRect.x = 60;
        menu->inputPositionRect.y = 160;
        menu->inputPositionRect.w = 15;
        menu->inputPositionRect.h = 50;
        SDL_Rect destinationInput = {menu->inputPositionRect.x, menu->inputPositionRect.y, menu->inputPositionRect.w, menu->inputPositionRect.h};
        SDL_RenderCopy(menu->pRenderer, menu->pInputText, NULL, &destinationInput);
    }

    SDL_RenderPresent(menu->pRenderer);
}

void menu_draw_hostname(stMenu *menu, char *hostname)
{
    SDL_SetRenderDrawColor(menu->pRenderer, 255, 255, 255, 255);
    SDL_RenderClear(menu->pRenderer);

    SDL_Rect hostnameInvite = {MENUDISPLAYX, MENUDISPLAYY, MENUDISPLAYW, MENUDISPLAYH};
    SDL_RenderCopy(menu->pRenderer, menu->pTextHostname, NULL, &hostnameInvite);

    if (*hostname != '\0')
    {
        menu->pInputText = font_load(menu, menu->police2, hostname);

        int width = strlen(hostname);
        SDL_Rect destinationInput = {INPUTPOSITIONX, INPUTPOSITIONY, INPUTPOSITIONW(width), INPUTPOSITIONH};
        SDL_RenderCopy(menu->pRenderer, menu->pInputText, NULL, &destinationInput);
    }

    SDL_RenderPresent(menu->pRenderer);
}

void menu_draw_port(stMenu *menu, char *port)
{

    SDL_SetRenderDrawColor(menu->pRenderer, 255, 255, 255, 255);
    SDL_RenderClear(menu->pRenderer);

    SDL_Rect portInvite = {MENUDISPLAYX, MENUDISPLAYY, MENUDISPLAYW, MENUDISPLAYH};
    SDL_RenderCopy(menu->pRenderer, menu->pTextPortname, NULL, &portInvite);

    if (*port != '\0')
    {
        menu->pInputText = font_load(menu, menu->police2, port);

        int width = strlen(port);
        SDL_Rect destinationInput = {INPUTPOSITIONX, INPUTPOSITIONY, INPUTPOSITIONW(width), INPUTPOSITIONH};
        SDL_RenderCopy(menu->pRenderer, menu->pInputText, NULL, &destinationInput);
    }

    SDL_RenderPresent(menu->pRenderer);
}

void menu_draw_welcome(stMenu *menu)
{
    SDL_SetRenderDrawColor(menu->pRenderer, 255, 255, 255, 255);
    SDL_RenderClear(menu->pRenderer);

    menu->welcomePositionRect.x = 60;
    menu->welcomePositionRect.y = 60;
    menu->welcomePositionRect.w = 550;
    menu->welcomePositionRect.h = 100;
    SDL_Rect welcomeMess = {menu->welcomePositionRect.x, menu->welcomePositionRect.y, menu->welcomePositionRect.w, menu->welcomePositionRect.h};
    SDL_RenderCopy(menu->pRenderer, menu->pTextWelcome, NULL, &welcomeMess);
    SDL_RenderPresent(menu->pRenderer);
}

void menu_destroy_2(stMenu *menu)
{
    if (menu)
    {
        TTF_CloseFont(menu->police1);
        TTF_CloseFont(menu->police2);
        SDL_DestroyWindow(menu->pWindow);
        SDL_DestroyRenderer(menu->pRenderer);

        free(menu);
    }
}
