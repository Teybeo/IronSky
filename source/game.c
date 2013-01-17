#include "game.h"

#include "level.h"

void gameLogic(Game* g)
{
    int i;

    resolveWallCollision(&g->player, g->screen->w, g->screen->h);

    for (i = 0; i < g->nbAttractors; i++)
    {
        if (isInForcefieldRange(g->tabAttractor[i], g->player.pos) == true)
        {
            Vector force = calculateForce(g->tabAttractor[i], g->player.pos);
            addForce(&g->player, force);
        }
    }

    for (i = 0; i < g->nbRepulsors; i++)
    {
        if (isInForcefieldRange(g->tabRepulsor[i], g->player.pos) == true)
        {
            Vector force = calculateForce(g->tabRepulsor[i], g->player.pos);
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

    // draw all attractors
    for (i = 0; i < g.nbAttractors; i++)
    {
        drawForcefield(g.tabAttractor[i], g.screen);
    }

    // draw all repulsors
    for (i = 0; i < g.nbRepulsors; i++)
    {
        drawForcefield(g.tabRepulsor[i], g.screen);
    }

    // draw spaceship
    drawSpaceship(g.player, g.screen);

    // finally, update the screen :)
    SDL_Flip(g.screen);

}

void gameEvent(Game* g, SDL_Event ev) {

    switch (ev.type)
    {
        case SDL_KEYDOWN:

            // Mise en pause
            if (ev.key.keysym.sym == SDLK_ESCAPE)
                g->done = true;
        break;

    }

}

Game gameInit(int IDlevel, SDL_Surface* screen, SDL_Surface** tabSprite)
{
    int i;

    Game g = {};

    g.screen = screen;
    g.background = tabSprite[3];
    g.done = false;

    g.tabJunk = NULL;
    g.comptJunk = 0;

    // Chargement d'un niveau
    loadLevel(IDlevel, &g, tabSprite[1], tabSprite[0]);

    g.tabAttractor = malloc(sizeof(Forcefield) * g.nbAttractors);
    g.tabRepulsor = malloc(sizeof(Forcefield) * g.nbRepulsors);

    for (i = 0; i < g.nbAttractors; i++)
        g.tabAttractor [i] = createForcefield(rand() % (g.screen->w - 55), rand() % (g.screen->h - 55), 100, -1, tabSprite[4] );

    for (i = 0; i < g.nbRepulsors; i++)
        g.tabRepulsor [i] = createForcefield(rand() % (g.screen->w - 55), rand() % (g.screen->h - 55), 100, 1, tabSprite[5] );

    addForce(&g.player, (Vector){-0.001, 0});

    return g;

}

void gameDestroy(Game g) {

    free(g.tabAttractor);
    free(g.tabRepulsor);
    free(g.tabJunk);
    SDL_FreeSurface(g.player.sprite);

}

void resetInputGame(Game* g) {

    g->done = false;

}
