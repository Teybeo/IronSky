#include "statePause.h"

#include "statePlay.h"
#include "app.h"

void Pause_Draw(State* state) {

    Pause* pause = (Pause*)state;

    SDL_FillRect(state->screen, NULL, 0x000000);

    drawButton(pause->resumeBtn, state->screen);
    drawButton(pause->changeLevelBtn, state->screen);
    drawButton(pause->mainMenuBtn, state->screen);

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

        updateButtonState(&pause->resumeBtn, ev.motion.x, ev.motion.y);
        updateButtonState(&pause->changeLevelBtn, ev.motion.x, ev.motion.y);
        updateButtonState(&pause->mainMenuBtn, ev.motion.x, ev.motion.y);

    break;

    case SDL_MOUSEBUTTONUP:

        if (pause->resumeBtn.state == HOVER)
            setCurrentState(state->appRef, getPrecedentState(state->appRef));

        if (pause->changeLevelBtn.state == HOVER)
        {
            game_Destroy(*(Play*)getPlayState(state->appRef));
            setCurrentState(state->appRef, getLevelMenuState(state->appRef));
        }
        if (pause->mainMenuBtn.state == HOVER)
        {
            game_Destroy(*(Play*)getPlayState(state->appRef));
            setCurrentState(state->appRef, getMenuState(state->appRef));
        }

    break;
    }

}

void Pause_Logic(State* state) {

}

Pause Pause_Create(App* appRef) {

    Pause m = {};

    m.state = createState(appRef, &Pause_Event, &Pause_Logic, &Pause_Draw, "Pause");

    m.resumeBtn = createButton(583, 100, 200, 100, 0x5321ff, 0x9921ff);
    m.changeLevelBtn = createButton(583, 300, 200, 100, 0x5321ff, 0x9921ff);
    m.mainMenuBtn = createButton(583, 500, 200, 100, 0x5321ff, 0x9921ff);

    return m;
}

void resetInputPause(Pause* g) {

    g->changeLevelBtn.state = NORMAL;
    g->mainMenuBtn.state = NORMAL;
    g->resumeBtn.state = NORMAL;

}

