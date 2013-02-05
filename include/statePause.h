#ifndef H_GAMEPAUSE_GUARD
#define H_GAMEPAUSE_GUARD

#include "state.h"
#include "gameData.h"
#include "button.h"

typedef struct Pause {

    State state;
    GameData* gameData;
    Button resumeBtn;
    Button changeLevelBtn;
    Button mainMenuBtn;

} Pause;

Pause Pause_Create(App* appRef, GameData* gameData);
void resetInputPause(Pause* g);

#endif // GAMEPAUSE

