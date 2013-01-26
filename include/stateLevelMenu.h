#ifndef _LEVELMENU_GUARD
#define _LEVELMENU_GUARD

#include "state.h"
#include "button.h"

#include "SDL.h"

#define NBLEVELS 10

typedef struct LevelMenu {

    State state;
    SDL_Surface* background; // image de fond
    Button level[NBLEVELS];  // boutons pour chaque niveaux
    Button quit;             // bouton pour quitter le jeu

} LevelMenu;

LevelMenu LevelMenu_Create(App* appRef);
void resetInputLevelMenu(LevelMenu* m);

#endif // MENU

