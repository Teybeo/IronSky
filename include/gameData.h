#ifndef _GAMEDATA
#define _GAMEDATA

#include "vector.h"
#include "forcefield.h"
#include "junk.h"
#include "spaceship.h"

#include "SDL_video.h"

enum {

    SHIP,
    JUNK_A,
    JUNK_B,
    BACKGROUND,
    ATTRACTOR,
    REPULSOR,
    NB_SPRITES
};

typedef struct GameData {

    SDL_Surface** sprites;
    Ship player;
    Point spawnPos;
    Junk* junks;
    Field* attractors;
    Field* repulsors;
    int nbJunks;
    int nbAttractors;
    int nbRepulsors;
    int nbCurrentAtt;
    int nbCurrentRep;

} GameData;

void loadGameSprites(GameData* g);
void loadLevel(GameData* g, int IDlevel);
void prepareGame(GameData* g);
void generateRandomLevel(int w, int h, int IDLevel);
void freeGame(GameData gameData);

#endif // GAMEDATA


