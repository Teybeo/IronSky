#ifndef _LEVEL
#define _LEVEL

#include "Point.h"
#include "junk.h"
#include "SDL_video.h"
#include "spaceship.h"

typedef struct Level {

    int nbJunks;
    Point* tabPosJunk;
    Point depart;

} Level;


void loadLevel(int IDlevel, Junk** tabJunk, int* nbJunks, SpaceShip* spaceship, SDL_Surface* junkSprite, SDL_Surface* spaceshipSprite);
Level generateLevel(int w, int h);
Level createLevel(int nbJunk, Point* tabPosJunk, Point depart);

Level openFileLevel(char* chemin);
void saveLevel(Level a);

#endif // LEVEL

