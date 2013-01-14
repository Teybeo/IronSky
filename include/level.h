#ifndef _LEVEL
#define _LEVEL

#include "Point.h"
#include "junk.h"
#include "SDL_video.h"
#include "spaceship.h"

//typedef struct Game Game;

#include "game.h"

void loadLevel(int IDlevel, Game* g, SDL_Surface* junkSprite, SDL_Surface* spaceshipSprite);
void generateRandomLevel(int w, int h, int IDLevel);

#endif // LEVEL

