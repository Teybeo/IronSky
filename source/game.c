#include "spaceship.h"
#include "junk.h"
#include "level.h"
#include "point.h"
#include "forcefield.h"
#include "SDL.h"

#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct {

    SDL_Surface* screen;
    SDL_Surface* background;
    SpaceShip player;
    Junk* tabJunk;
    Forcefield* tabField;
    int nbFields;
    int nbJunks;
    int comptJunk;

} Game;

Game gameInit(char* cheminNiveau, SDL_Surface** tabSprite);
int gameRun(Game g);
void gameEvent(bool* done);
void gameLogic(bool* done, Game* g);
void gameDraw(Game g);
void updateAndPrintChrono(unsigned int* duration);

int gameRun(Game g)
{

    unsigned int duration = 0;

    // program main loop
    bool done = false;
    while (!done)
    {
        gameEvent(&done);
        gameLogic(&done, &g);
        gameDraw(g);

        updateAndPrintChrono(&duration);

    } // end main loop

    // all is well ;)
    printf("Fin de partie\n");

    return 0;
}

void gameLogic(bool* done, Game* g)
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
        *done = true;
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

void gameEvent(bool* done) {

    SDL_Event event;

    // message processing loop
    while (SDL_PollEvent(&event))
    {
        // check for messages
        switch (event.type)
        {
            // exit if the window is closed
            case SDL_QUIT:
                *done = true;
            break;

            // check for keypresses
            case SDL_KEYDOWN:

                // exit if ESCAPE is pressed
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    *done = true;
            break;

        } // end switch

    } // end of message processing

}

Game gameInit(char* cheminNiveau, SDL_Surface** tabSprite)
{
    int i;
    int tabIntensite[2] = {-1, 1};

    Game g = {};

    g.screen = SDL_GetVideoSurface();
    g.background = tabSprite[3];
    g.nbFields = 5;
    g.tabField = malloc(sizeof(Forcefield) * g.nbFields);

    for (i = 0; i < g.nbFields; i++)
        g.tabField [i] = createForcefield(rand() % (g.screen->w - 55), rand() % (g.screen->h - 55), 100, tabIntensite[rand() % 2], tabSprite[4], tabSprite[5]);

    g.tabJunk = NULL;
    g.comptJunk = 0;

    Level lev = {};

//    Level lev = generateLevel(screen->w, screen->h);
//    saveLevel(lev);

    lev = openFileLevel(cheminNiveau);

    // Chargement d'un niveau
    loadLevel(lev, &g.tabJunk, &g.nbJunks, &g.player, tabSprite[1], tabSprite[0]);

    addForce(&g.player, (Vector){-0.001, 0});

    return g;

}

void gameLaunch(char* cheminNiveau, SDL_Surface** tabSprite) {

    Game g = gameInit(cheminNiveau, tabSprite);

    gameRun(g);

}


void updateAndPrintChrono(unsigned int* duration) {

    static unsigned int precedent = 0;
    static char chaine[30];

    *duration = SDL_GetTicks() - precedent;
    precedent = SDL_GetTicks(); // On met à jour la date de la dernière image

    sprintf(chaine, "Duree: %u ms", *duration);
    SDL_WM_SetCaption(chaine, NULL);

}

