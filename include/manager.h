#ifndef _MANAGER_GUARD
#define _MANAGER_GUARD

#include "menu.h"
#include "game.h"
#include "levelMenu.h"

typedef enum {

    MENU_STATE,
    LEVELMENU_STATE,
    GAME_STATE

} AppState;

typedef struct Manager {

    SDL_Surface* screen;     // écran
    SDL_Surface** tabSprite; // tableau des sprites
    AppState current;        // état actuel du programme
    Menu menu;
    LevelMenu levelMenu;
    Game game;
    bool done;               // indique l'arrêt du programme

} Manager;

bool managerInit(Manager* m);
void runManager(Manager m);

#endif // MANAGER

