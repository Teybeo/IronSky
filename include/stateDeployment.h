#ifndef H_GAMEMENU_GUARD
#define H_GAMEMENU_GUARD

#include "state.h"
#include "gameData.h"
#include "forcefield.h"
#include "button.h"

#include "SDL.h"

typedef struct Deployment {

    State state;
    GameData* gameData;
    SDL_Surface* background; // image de fond
    Forcefield* selection;
    Button attrac;             // bouton pour lancer une partie
    Button repuls;             // bouton pour quitter le jeu

} Deployment;

Deployment Deployment_Create(App* appRef, GameData* g);
void resetInputDeployment(Deployment* g);

#endif // GAMEMENU

