#include "../../headerFiles/menu/menu.h"
#include "../../headerFiles/game/game.h"

void menu_draw(stMenu *menu) {
    SDL_SetRenderDrawColor(menu->pRenderer, 0, 0, 0, 0);
    SDL_RenderClear(menu->pRenderer);
    SDL_Rect menu_title = {300, 30, 500, 500};
    SDL_RenderCopy(menu->pRenderer, menu->textureMenu, NULL, &menu_title);
    SDL_Rect heberger = {550, 400, 500, 100};
    SDL_RenderCopy(menu->pRenderer, menu->pTextheberger, NULL, &heberger);
    SDL_Rect rejoindre = {550, 600, 500, 100};
    SDL_RenderCopy(menu->pRenderer, menu->pTextRejoindre, NULL, &rejoindre);
    SDL_RenderPresent(menu->pRenderer);
}

void menu_draw_choix(stMenu *menu, char *choix) {
    SDL_SetRenderDrawColor(menu->pRenderer, 255, 255, 255, 255);
    SDL_RenderClear(menu->pRenderer);
    SDL_Rect modeChoixText = {MENUDISPLAYX, MENUDISPLAYY, MENUDISPLAYW, MENUDISPLAYH};
    SDL_RenderCopy(menu->pRenderer, menu->pTextChoix, NULL, &modeChoixText);
    if (*choix != '\0') {
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

void menu_draw_hostname(stMenu *menu, char *hostname) {
    SDL_SetRenderDrawColor(menu->pRenderer, 255, 255, 255, 255);
    SDL_RenderClear(menu->pRenderer);
    SDL_Rect hostnameInvite = {MENUDISPLAYX, MENUDISPLAYY, MENUDISPLAYW, MENUDISPLAYH};
    SDL_RenderCopy(menu->pRenderer, menu->pTextHostname, NULL, &hostnameInvite);
    if (*hostname != '\0') {
        menu->pInputText = font_load(menu, menu->police2, hostname);
        int width = strlen(hostname);
        SDL_Rect destinationInput = {INPUTPOSITIONX, INPUTPOSITIONY, INPUTPOSITIONW(width), INPUTPOSITIONH};
        SDL_RenderCopy(menu->pRenderer, menu->pInputText, NULL, &destinationInput);
    }
    SDL_RenderPresent(menu->pRenderer);
}

void menu_draw_port(stMenu *menu, char *port) {
    SDL_SetRenderDrawColor(menu->pRenderer, 255, 255, 255, 255);
    SDL_RenderClear(menu->pRenderer);
    SDL_Rect portInvite = {MENUDISPLAYX, MENUDISPLAYY, MENUDISPLAYW, MENUDISPLAYH};
    SDL_RenderCopy(menu->pRenderer, menu->pTextPortname, NULL, &portInvite);
    if (*port != '\0') {
        menu->pInputText = font_load(menu, menu->police2, port);
        int width = strlen(port);
        SDL_Rect destinationInput = {INPUTPOSITIONX, INPUTPOSITIONY, INPUTPOSITIONW(width), INPUTPOSITIONH};
        SDL_RenderCopy(menu->pRenderer, menu->pInputText, NULL, &destinationInput);
    }
    SDL_RenderPresent(menu->pRenderer);
}

void menu_draw_welcome(stMenu *menu) {
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