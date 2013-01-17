#ifndef H_GAMEPAUSE_GUARD
#define H_GAMEPAUSE_GUARD

#include "button.h"

typedef struct GamePause {

    SDL_Surface* screen;
    Button resumeBtn;
    Button changeLevelBtn;
    Button mainMenuBtn;
    bool resume;
    bool changeLevel;
    bool mainMenu;

} GamePause;

GamePause gamePauseInit(SDL_Surface* screen);
void gamePauseEvent(GamePause* m, SDL_Event ev);
void gamePauseDraw(GamePause m);
void resetInputGamePause(GamePause* g);

#endif // GAMEPAUSE

