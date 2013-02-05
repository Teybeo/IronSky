#include "statePause.h"

#include "app.h"

void Pause_Draw(State* state) {

    Pause* pause = (Pause*)state;

    SDL_FillRect(state->screen, NULL, 0x000000);

    Button_Draw(pause->resumeBtn, state->screen);
    Button_Draw(pause->changeLevelBtn, state->screen);
    Button_Draw(pause->mainMenuBtn, state->screen);

    SDL_Flip(state->screen);

}

void Pause_Event(State* state, SDL_Event ev) {

    Pause* pause = (Pause*)state;

    switch (ev.type)
    {
    case SDL_KEYDOWN:

        // Sortie de pause
        if (ev.key.keysym.sym == SDLK_ESCAPE)
            setCurrentState(state->appRef, getPrecedentState(state->appRef));

    break;

    case SDL_MOUSEMOTION:

        Button_UpdateState(&pause->resumeBtn, ev.motion.x, ev.motion.y);
        Button_UpdateState(&pause->changeLevelBtn, ev.motion.x, ev.motion.y);
        Button_UpdateState(&pause->mainMenuBtn, ev.motion.x, ev.motion.y);

    break;

    case SDL_MOUSEBUTTONUP:

        if (pause->resumeBtn.state == HOVER)
            setCurrentState(state->appRef, getPrecedentState(state->appRef));

        if (pause->changeLevelBtn.state == HOVER)
        {
            freeGame(*pause->gameData);
            setCurrentState(state->appRef, getLevelMenuState(state->appRef));
        }
        if (pause->mainMenuBtn.state == HOVER)
        {
            freeGame(*pause->gameData);
            setCurrentState(state->appRef, getMenuState(state->appRef));
        }

    break;
    }

}

void Pause_Logic(State* state) {

}

Pause Pause_Create(App* appRef, GameData* gameData) {

    Pause m = {};

    m.state = createState(appRef, &Pause_Event, &Pause_Logic, &Pause_Draw, "Pause");
    m.gameData = gameData;

    m.resumeBtn = Button_Create(583, 100, 200, 100, 0x5321ff, 0x9921ff);
    m.changeLevelBtn = Button_Create(583, 300, 200, 100, 0x5321ff, 0x9921ff);
    m.mainMenuBtn = Button_Create(583, 500, 200, 100, 0x5321ff, 0x9921ff);

    return m;
}

void resetInputPause(Pause* g) {

    g->changeLevelBtn.state = NORMAL;
    g->mainMenuBtn.state = NORMAL;
    g->resumeBtn.state = NORMAL;

}

