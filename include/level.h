#ifndef _LEVEL
#define _LEVEL

#include "Point.h"
#include "junk.h"
#include "SDL_video.h"
#include "spaceship.h"

typedef struct Level {

    int nbJunk;
    Point* tabPosJunk;
    Point depart;

} Level;

void buildLevel(Level lev, Junk** tabJunk, SpaceShip* spaceship, SDL_Surface* spriteEcrou, SDL_Surface* spriteSpaceship);

Level generateLevel(int w, int h);
Level createLevel(int nbJunk, Point* tabPosJunk, Point depart);

Level chargeLevel(char* chemin);
void saveLevel(Level a);

#endif // LEVEL

