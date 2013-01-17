#ifndef _GAME
#define _GAME

#include "forcefield.h"
#include "spaceship.h"
#include "junk.h"

#include "SDL.h"

typedef struct Game {

    SDL_Surface* screen;
    SDL_Surface* background;
    SpaceShip player;
    Junk* tabJunk;
    Forcefield* tabAttractor;
    Forcefield* tabRepulsor;
    int nbJunks;
    int nbAttractors;
    int nbRepulsors;
    int comptJunk;
    bool done;
    bool deployment;

} Game;

Game gameInit(int IDlevel, SDL_Surface* screen, SDL_Surface** tabSprite);
void gameEvent(Game* done, SDL_Event ev);
void gameLogic(Game* g);
void gameDraw(Game g);
void gameDestroy(Game g);
void resetInputGame(Game* g);

#endif // _GAME

