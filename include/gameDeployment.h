#ifndef H_GAMEMENU_GUARD
#define H_GAMEMENU_GUARD

#include "SDL.h"
#include <stdbool.h>
#include "button.h"
#include "game.h"

typedef struct GameDeployment {

    Game* g;
    SDL_Surface* screen;     // écran
    SDL_Surface* background; // image de fond
    SDL_Surface* attSprite;
    SDL_Surface* repSprite;
    Button attrac;             // bouton pour lancer une partie
    Button repuls;             // bouton pour quitter le jeu
    bool pause;              // indique la mise en pause
    bool game;
    Forcefield* selection;
    int nbCurrentAtt;
    int nbCurrentRep;

} GameDeployment;

void gameDeploymentEvent(GameDeployment* m, SDL_Event ev);
void gameDeploymentDraw(GameDeployment m);
GameDeployment gameDeploymentInit(SDL_Surface* screen, Game* g, SDL_Surface* attSprite, SDL_Surface* repSprite);
void resetInputGameDeployment(GameDeployment* g);

#endif // GAMEMENU

