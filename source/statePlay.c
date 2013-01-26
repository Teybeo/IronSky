#include "statePlay.h"

#include "app.h"

#include "vector.h"
#include "forcefield.h"
#include "junk.h"
#include "spaceship.h"

void Play_Logic(State* state)
{
    Play* play = (Play*)state;

    int i;

    resolveWallCollision(&play->gameData->player, state->screen->w, state->screen->h);

    // On applique les forces d'attractions au vaisseau
    for (i = 0; i < play->gameData->nbAttractors; i++)
    {
        if (isInForcefieldRange(play->gameData->attractors[i], play->gameData->player.pos) == true)
        {
            Vector force = calculateForce(play->gameData->attractors[i], play->gameData->player.pos);
            addForce(&play->gameData->player, force);
        }
    }

    // On applique les forces de répulsions au vaisseau
    for (i = 0; i < play->gameData->nbRepulsors; i++)
    {
        if (isInForcefieldRange(play->gameData->repulsors[i], play->gameData->player.pos) == true)
        {
            Vector force = calculateForce(play->gameData->repulsors[i], play->gameData->player.pos);
            addForce(&play->gameData->player, force);
        }
    }

    // On déplace le vaisseau
    applyForces(&play->gameData->player);
    nextpos(&play->gameData->player);
    turnSpaceShip(&play->gameData->player);

    // On comptabilise les junks ramassés
    for (i = 0; i < play->gameData->nbJunks; i++)
    {
        if (canTakeJunk(play->gameData->junks[i], play->gameData->player.pos, play->gameData->player.rayon))
        {
            setTakenJunk(&play->gameData->junks[i], true);
            play->comptJunk++;
        }
    }

    // La partie est terminée, on revient au menu des niveaux
    if (play->comptJunk == play->gameData->nbJunks)
    {
        game_Destroy(*play);
        setCurrentState(state->appRef, getLevelMenuState(state->appRef));
    }
}


void Play_Draw(State* state) {

    Play* play = (Play*)state;

    // draw background
    SDL_BlitSurface(play->background, NULL, state->screen, NULL);

    // draw all junks
    drawAvailableJunks(play->gameData->junks, play->gameData->nbJunks, state->screen);

    // draw all attractors
    drawForcefields(play->gameData->attractors, play->gameData->nbAttractors, state->screen);

    // draw all repulsors
    drawForcefields(play->gameData->repulsors, play->gameData->nbRepulsors, state->screen);

    // draw spaceship
    drawSpaceship(play->gameData->player, state->screen);

    // finally, update the screen :)
    SDL_Flip(state->screen);

}

void Play_Event(State* state, SDL_Event ev) {

    Play* play = (Play*)state;

    if (ev.type == SDL_KEYDOWN)
    {
        // Mise en pause
        if (ev.key.keysym.sym == SDLK_ESCAPE)
            setCurrentState(state->appRef, getPauseState(state->appRef));

        // On replace les vaisseaux et on remet les junks en visible
        if (ev.key.keysym.sym == SDLK_SPACE)
        {
            prepareGame(play->gameData);
            play->comptJunk = 0;
            setCurrentState(state->appRef, getDeploymentState(state->appRef));
        }
    }

}

Play Play_Create(App* appRef, GameData* gameData)
{
    Play g = {};

    g.state = createState(appRef, &Play_Event, &Play_Logic, &Play_Draw, "Play");

    g.gameData = gameData;
    g.background = gameData->sprites[BACKGROUND];

    g.comptJunk = 0;

//    addForce(&g.player, (Vector){-0.001, 0});

    return g;
}

void game_Destroy(Play g) {

    if (g.gameData->attractors != NULL)
        free(g.gameData->attractors);

    if (g.gameData->repulsors != NULL)
        free(g.gameData->repulsors);

    if (g.gameData->junks != NULL)
        free(g.gameData->junks);

    if (g.gameData->player.sprite != NULL && g.gameData->player.sprite != g.gameData->player.spriteOriginal)
        SDL_FreeSurface(g.gameData->player.sprite);

}
