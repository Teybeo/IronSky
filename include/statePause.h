#ifndef H_GAMEPAUSE_GUARD
#define H_GAMEPAUSE_GUARD

#include "state.h"
#include "button.h"

typedef struct Pause {

    State state;
    Button resumeBtn;
    Button changeLevelBtn;
    Button mainMenuBtn;

} Pause;

Pause Pause_Create(App* appRef);
void resetInputPause(Pause* g);

#endif // GAMEPAUSE

