#include "spaceship.h"
#include "junk.h"
#include "level.h"
#include "fonctionCSDL.h"
#include "point.h"
#include "forcefield.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_rotozoom.h"

#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct {

    SDL_Surface* screen;
    SDL_Surface* background;
    SpaceShip player;
    Junk* tabJunk;
    ForceField* tabField;
    int nbFields;
    int nbJunks;
    int comptJunk;

} Game;

Game gameInit(char* cheminNiveau, SDL_Surface** tabSprite);
int gameRun(Game g);
void gameEvent(bool* done);
void gameLogic(bool* done, Game* g);
void gameDraw(Game g);

int gameRun(Game g)
{

    // program main loop
    bool done = false;
    while (!done)
    {
        static float debut = 0;
        debut = SDL_GetTicks();

        gameEvent(&done);
        gameLogic(&done, &g);
        gameDraw(g);

        float duree = (SDL_GetTicks() - debut);
        char chaine[30] = "";
        sprintf(chaine, "Duree: %.0f ms", duree);
        SDL_WM_SetCaption(chaine, NULL);

    } // end main loop

    // all is well ;)
    printf("Fin de partie\n");

    return 0;
}

void gameLogic(bool* done, Game* g)
{

    int i;
    for (i = 0; i < g->nbJunks; i++)
        if (takeJunk( &g->tabJunk[i] , g->player.pos, g->player.rayon))
                g->comptJunk++;

    if (g->player.pos.x - g->player.rayon < 0)
    {
        g->player.vitesse.x *= -0.9;
        g->player.pos.x = g->player.rayon;
    }
    if (g->player.pos.x + g->player.rayon > g->screen->w)
    {
        g->player.vitesse.x *= -0.9;
        g->player.pos.x = g->screen->w - g->player.rayon;
    }
    if (g->player.pos.y + g->player.rayon > g->screen->h)
    {
        g->player.vitesse.y *= -0.9;
        g->player.pos.y = g->screen->h - g->player.rayon;
    }
    if (g->player.pos.y - g->player.rayon < 0)
    {
        g->player.vitesse.y *= -0.9;
        g->player.pos.y = g->player.rayon;
    }

    for (i = 0; i < g->nbFields; i++)
    {

        if (distanceVect( createVect(g->tabField[i].pos, g->player.pos)) < g->tabField[i].rayon)
        {
            Vector normale = createVect(g->tabField[i].pos,  g->player.pos);
            float longueur = distanceVect(normale);
            divisVecScal(&normale, longueur);

            Vector force = normale;
            multVecScal(&force, g->tabField[i].intensity* 0.01/longueur);

            addVectors(&g->player.totalForces, force);

        }

    }

    applyForces(&g->player);
    nextpos(&g->player);
    turnSpaceShip(&g->player);

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
        if (g.tabJunk[i].take == 0)
            drawJunk(g.tabJunk[i], g.screen);

    }

    // draw all fields
    for (i = 0; i < g.nbFields; i++)
    {
        drawForceField(g.tabField[i], g.screen);
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
    g.tabField = malloc(sizeof(ForceField) * g.nbFields);

    for (i = 0; i < g.nbFields; i++)
        g.tabField [i] = createForceField(rand() % (g.screen->w - 55), rand() % (g.screen->h - 55), 100, tabIntensite[rand() % 2], tabSprite[4], tabSprite[5]);

    g.tabJunk = NULL;
    g.comptJunk = 0;

    Level lev = {};

//    Level lev = generateLevel(screen->w, screen->h);
//    saveLevel(lev);

    lev = openFileLevel(cheminNiveau);

    // Chargement d'un niveau
    loadLevel(lev, &g.tabJunk, &g.nbJunks, &g.player, tabSprite[1], tabSprite[0]);

    addForces(&g.player, (Vector){-0.001, 0});

    return g;

}

void gameLaunch(char* cheminNiveau, SDL_Surface** tabSprite) {

    Game g = gameInit(cheminNiveau, tabSprite);

    gameRun(g);

}




