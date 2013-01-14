#ifndef _MENU_GUARD
#define _MENU_GUARD

#include "SDL.h"
#include <stdbool.h>
#include "button.h"

typedef struct Menu {

    SDL_Surface* screen;     // écran
    SDL_Surface* background; // image de fond
    Button play;             // bouton pour lancer une partie
    Button quit;             // bouton pour quitter le jeu
    bool goToLevelMenu;      // indique le passage à l'écran de sélection des niveaux
    bool done;               // indique l'arret du programme

} Menu;

void menuEvent(Menu* m, SDL_Event ev);
void menuDraw(Menu m);
Menu menuInit(SDL_Surface* screen);

#endif // MENU
