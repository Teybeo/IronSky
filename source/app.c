#include "game.h"
#include "fonctionCSDL.h"

#include "SDL.h"

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

bool appInit(SDL_Surface** screen);
void loadSprites(SDL_Surface*** tabSprite);

int main() {

    SDL_Surface* screen = NULL;
    SDL_Surface** tabSprite = NULL;

    appInit(&screen);

    loadSprites(&tabSprite);

    gameLaunch("test.niveau", tabSprite);
    gameLaunch("test.niveau", tabSprite);

    return EXIT_SUCCESS;

}

void loadSprites(SDL_Surface*** tabSprite)
{

    *tabSprite = malloc(sizeof(SDL_Surface*) * 6);

    (*tabSprite)[0] = memoryImg("image/spaceshipE.png");
    (*tabSprite)[1] = memoryImg("image/junkA.png");
    (*tabSprite)[2] = memoryImg("image/junkC.png");
    (*tabSprite)[3] = memoryImg("image/background.png");
    (*tabSprite)[4] = memoryImg("image/itemA.png");
    (*tabSprite)[5] = memoryImg("image/itemR.png");

}

bool appInit(SDL_Surface** screen)
{
    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return false;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    *screen = SDL_SetVideoMode(1366, 768, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !*screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return false;
    }

    srand(time(NULL));

    return true;
}
