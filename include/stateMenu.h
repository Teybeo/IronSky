#ifndef _MENU_GUARD
#define _MENU_GUARD

#include "state.h"
#include "button.h"

#include "SDL_video.h"

typedef struct Menu {

    State state;
    SDL_Surface* background; // image de fond
    Button play;             // bouton pour lancer une partie
    Button quit;             // bouton pour quitter le jeu

} Menu;

Menu Menu_Create(App* appRef);
void resetInputMenu(Menu* m);

#endif // MENU
