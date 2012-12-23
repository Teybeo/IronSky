#include "spaceship.h"
#include "junk.h"
#include "level.h"
#include "fonctionCSDL.h"
#include "point.h"
#include "champForce.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_rotozoom.h"

#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


bool gameInit(SDL_Surface** ecran);
void gameEvent(bool* done);
void gameLogic(SpaceShip* spaceship, Junk* tabJunk, int nbJunk, int* comptJunk, bool* done, ChampForce* champ, int nbChamp, int w, int h);
void gameDraw(SpaceShip spaceship, Junk* tabJunk, int nbJunk, ChampForce* tabChamp, int nbChamp, SDL_Surface* screen, SDL_Surface* background);

SDL_Surface* screen;

int gameStart (char* cheminNiveau, SDL_Surface** tabSprite)
{
    screen = SDL_GetVideoSurface();
    SDL_Surface* background = tabSprite[3];
    SpaceShip spaceship;
    Level lev = {};
    Junk *tabJunk = NULL;
    int nbChamp = 5;
    ChampForce* tabChamp = malloc(sizeof(ChampForce) * nbChamp);
    int i;
    int tabIntensite[2] = {-1, 1};
    for (i = 0; i < nbChamp; i++)
        tabChamp [i] = createChampForce(rand() % (screen->w - 55), rand() % (screen->h - 55), 100, tabIntensite[rand() % 2], tabSprite[4], tabSprite[5]);
    int comptJunk = 0;

    if (gameInit(&screen) == false)
        return EXIT_FAILURE;

    SDL_Surface* spriteSpaceship = tabSprite[0];
    SDL_Surface* spriteEcrou = tabSprite[1];

//    lev = generateLevel(screen->w, screen->h);
//    saveLevel(lev);

    lev = chargeLevel(cheminNiveau);

    // Chargement d'un niveau
    buildLevel(lev, &tabJunk, &spaceship, spriteEcrou, spriteSpaceship);

    addForces(&spaceship, (Vecteur){-0.001, 0});

    // program main loop
    bool done = false;
    while (!done)
    {
        static float debut = 0;
        debut = SDL_GetTicks();

        gameEvent(&done);
        gameLogic(&spaceship, tabJunk, lev.nbJunk, &comptJunk, &done, tabChamp, nbChamp, screen->w, screen->h);
        gameDraw(spaceship, tabJunk, lev.nbJunk, tabChamp, nbChamp, screen, background);

        float duree = (SDL_GetTicks() - debut);
        char chaine[30] = "";
        sprintf(chaine, "Duree: %.0f ms", duree);
        SDL_WM_SetCaption(chaine, NULL);
//        if (duree < 16)
//            SDL_Delay(10 - duree);

    } // end main loop

    // all is well ;)
    printf("Fin de partie\n");

    return 0;
}

void gameLogic(SpaceShip* spaceship, Junk* tabJunk, int nbJunk, int* comptJunk, bool* done, ChampForce* tabChamp, int nbChamp, int w, int h) {

    // Rotation du sprite
    turnSpaceShip(spaceship);

    int i;
    for (i = 0; i < nbJunk; i++)
        if (takeJunk( &tabJunk[i] , spaceship->pos, spaceship->rayon))
                (*comptJunk)++;

    //printf("%d %d\n",spaceship.pos.x,spaceship.pos.y);
    if (spaceship->pos.x - spaceship->rayon < 0)
    {
        spaceship->vitesse.x *= -0.9;
        spaceship->pos.x = spaceship->rayon;
    }
    if (spaceship->pos.x + spaceship->rayon > w)
    {
        spaceship->vitesse.x *= -0.9;
        spaceship->pos.x = w - spaceship->rayon;
    }
    if (spaceship->pos.y + spaceship->rayon > h)
    {
        spaceship->vitesse.y *= -0.9;
        spaceship->pos.y = h - spaceship->rayon;
    }
    if (spaceship->pos.y - spaceship->rayon < 0)
    {
        spaceship->vitesse.y *= -0.9;
        spaceship->pos.y = spaceship->rayon;
    }

    for (i = 0; i < nbChamp; i++)
    {

        if (distanceVect( createVect(tabChamp[i].pos, spaceship->pos)) < tabChamp[i].rayon)
        {
            Vecteur normale = createVect(tabChamp[i].pos,  spaceship->pos);
            float longueur = distanceVect(normale);
            divisVecScal(&normale, longueur);

            Vecteur force = normale;
            multVecScal(&force, tabChamp[i].intensite* 0.01/longueur);

            addVecteurs(&spaceship->totalForces, force);

    //        lineColor(screen, spaceship->pos.x, spaceship->pos.y, tabChamp[i].pos.x, tabChamp[i].pos.y, 0xffffffff);
            short x, y;
            x = force.x * 10000;
            y = force.y * 10000;

            lineColor(screen, spaceship->pos.x, spaceship->pos.y,spaceship->pos.x + x, spaceship->pos.y + y, 0xffffffff);

        }

    }
    appliqueForces(spaceship);
    nextpos(spaceship);

    //printf("nbJunk %d\n", *comptJunk);

    if (*comptJunk == nbJunk)
        *done = true;
}

void gameDraw(SpaceShip spaceship, Junk* tabJunk, int nbJunk, ChampForce* tabChamp, int nbChamp, SDL_Surface* screen, SDL_Surface* background) {

    // clear screen

    // draw bitmap
    SDL_BlitSurface(background,NULL,screen,NULL);
    int i;
    for(i=0 ; i < nbJunk ; i++)
    {
        if (tabJunk[i].take == 0)
            afficherDechet(tabJunk[i], screen);

    }

    for (i = 0; i < nbChamp; i++)
    {
        affichChampForce(tabChamp[i], screen);
    }

    afficheSpaceship(spaceship, screen);

    // finally, update the screen :)
    SDL_Flip(screen);
    SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

}

void gameEvent(bool* done) {
    // message processing loop
    SDL_Event event;
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
            {
                // exit if ESCAPE is pressed
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    *done = true;
                break;
            }
        } // end switch
    } // end of message processing

}

bool gameInit(SDL_Surface** screen) {



    return true;

}
