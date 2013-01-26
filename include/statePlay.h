#ifndef _GAME
#define _GAME

#include "state.h"
#include "gameData.h"

#include "SDL_video.h"

typedef struct Play {

    State state;
    SDL_Surface* background;
    GameData* gameData;
    int comptJunk;

} Play;

Play Play_Create(App* appRef, GameData* gameData);
void game_Destroy(Play g);
void resetInputPlay(Play* g);

#endif // _GAME

