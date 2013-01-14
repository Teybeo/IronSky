#include "game.h"

#include "spaceship.h"
#include "junk.h"
#include "level.h"
#include "point.h"
#include "forcefield.h"
#include "SDL.h"

#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


void gameLogic(Game* g)
{

    int i;

    resolveWallCollision(&g->player, g->screen->w, g->screen->h);

    for (i = 0; i < g->nbFields; i++)
    {
        if (isInForcefieldRange(g->tabField[i], g->player.pos) == true)
        {
            Vector force = calculateForce(g->tabField[i], g->player.pos);
            addForce(&g->player, force);
        }
    }

    applyForces(&g->player);
    nextpos(&g->player);
    turnSpaceShip(&g->player);

    for (i = 0; i < g->nbJunks; i++)
        if (canTakeJunk( &g->tabJunk[i] , g->player.pos, g->player.rayon))
                g->comptJunk++;

    //printf("nbJunk %d\n", *comptJunk);

    if (g->comptJunk == g->nbJunks)
        g->done = true;
}

void gameDraw(Game g) {

    int i;

    // draw background
    SDL_BlitSurface(g.background, NULL, g.screen, NULL);

    // draw all junks
    for (i=0 ; i < g.nbJunks ; i++)
    {
        if (g.tabJunk[i].taken == false)
            drawJunk(g.tabJunk[i], g.screen);

    }

    // draw all fields
    for (i = 0; i < g.nbFields; i++)
    {
        drawForcefield(g.tabField[i], g.screen);
    }

    // draw spaceship
    drawSpaceship(g.player, g.screen);

    // finally, update the screen :)
    SDL_Flip(g.screen);

}

void gameEvent(Game* g, SDL_Event ev) {

    switch (ev.type)
    {
        // check for keypresses
        case SDL_KEYDOWN:

            // exit if ESCAPE is pressed
            if (ev.key.keysym.sym == SDLK_ESCAPE)
                g->done = true;
        break;

    }

}

Game gameInit(int IDlevel, SDL_Surface* screen, SDL_Surface** tabSprite)
{
    int i;
    int tabIntensite[2] = {-1, 1};

    Game g = {};

    g.screen = screen;
    g.background = tabSprite[3];
    g.done = false;
    g.nbFields = 5;
    g.tabField = malloc(sizeof(Forcefield) * g.nbFields);

    for (i = 0; i < g.nbFields; i++)
        g.tabField [i] = createForcefield(rand() % (g.screen->w - 55), rand() % (g.screen->h - 55), 100, tabIntensite[rand() % 2], tabSprite[4], tabSprite[5]);

    g.tabJunk = NULL;
    g.comptJunk = 0;

    // Chargement d'un niveau
    loadLevel(IDlevel, &g.tabJunk, &g.nbJunks, &g.player, tabSprite[1], tabSprite[0]);

    addForce(&g.player, (Vector){-0.001, 0});

    return g;

}

void gameDestroy(Game g) {

    free(g.tabField);
    free(g.tabJunk);
    SDL_FreeSurface(g.player.sprite);

}
