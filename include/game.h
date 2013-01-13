#ifndef _GAME
#define _GAME

#include "forcefield.h"
#include "level.h"
#include <stdbool.h>

#include "SDL.h"

typedef struct {

    SDL_Surface* screen;
    SDL_Surface* background;
    SpaceShip player;
    Junk* tabJunk;
    Forcefield* tabField;
    int nbFields;
    int nbJunks;
    int comptJunk;
    bool done;

} Game;

Game gameInit(char* cheminNiveau, SDL_Surface* screen, SDL_Surface** tabSprite);
void gameEvent(Game* done, SDL_Event ev);
void gameLogic(Game* g);
void gameDraw(Game g);
void gameDestroy(Game g);

#endif // _GAME

