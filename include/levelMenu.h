#ifndef _LEVELMENU_GUARD
#define _LEVELMENU_GUARD

#include "SDL.h"
#include <stdbool.h>
#include "button.h"

#define NBLEVELS 10

typedef struct LevelMenu {

    SDL_Surface* screen;     // écran
    SDL_Surface* background; // image de fond
    Button level[NBLEVELS];  // boutons pour chaque niveaux
    Button play;             // bouton pour lancer une partie
    Button quit;             // bouton pour quitter le jeu
    int goToGame;            // indique le numéro du jeu à lancer
    bool goToMenu;           // indique le retour au menu

} LevelMenu;

void levelMenuEvent(LevelMenu* m, SDL_Event ev);
void levelMenuDraw(LevelMenu m);
LevelMenu levelMenuInit(SDL_Surface* screen);

#endif // MENU

