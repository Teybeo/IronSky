#include "stateLevelMenu.h"

#include "app.h"

void LevelMenu_Draw(State* state) {

    LevelMenu* levMenu = (LevelMenu*)state;

    SDL_FillRect(state->screen, NULL, 0x000000);

    drawButton(levMenu->quit, state->screen);

    int i;
    for (i = 0 ; i < NBLEVELS ; i++ )
        drawButton(levMenu->level[i], state->screen);

    SDL_Flip(state->screen);

}

void LevelMenu_Event(State* state, SDL_Event ev) {

    LevelMenu* levMenu = (LevelMenu*)state;

    int i;

    if (ev.type == SDL_MOUSEMOTION)
    {
        updateButtonState(&levMenu->quit, ev.motion.x, ev.motion.y );

        for (i = 0 ; i < NBLEVELS ; i++ )
            updateButtonState(&levMenu->level[i], ev.motion.x, ev.motion.y );
    }

    if (ev.type == SDL_MOUSEBUTTONUP)
    {
        if (levMenu->quit.state == HOVER)
            setCurrentState(state->appRef, getMenuState(state->appRef));

        // On trouve le niveau choisi, on le charge et on lance la partie
        for (i = 0 ; i < NBLEVELS ; i++ )
        {
            if (isInBox(levMenu->level[i].rect, ev.button.x, ev.button.y))
            {
                gameSetup(state->appRef, i + 1);
                setCurrentState(state->appRef, getDeploymentState(state->appRef));
                break;
            }
        }

    }

}

void LevelMenu_Logic(State* state) {

}

LevelMenu LevelMenu_Create(App* appRef) {

    LevelMenu m = {};

    m.state = createState(appRef, &LevelMenu_Event, &LevelMenu_Logic, &LevelMenu_Draw, "LevelMenu");

    m.quit = createButton(583, 650, 200, 100, 0x145321ff, 0x999921ff);

    int i;
    int w = m.state.screen->w / 7;
    for (i = 0 ; i < NBLEVELS ; i++ )
    {
        int x = w/2 + 240 * (i % (NBLEVELS/2));
        int y = 150 + 240 * ((i/5) % (NBLEVELS/2));
        m.level[i] = createButton(x, y, w, w, 0x804030, 0x808030);
    }

    return m;
}

void resetInputLevelMenu(LevelMenu* m) {

    m->quit.state = NORMAL;
    int i;
    for (i = 0 ; i < NBLEVELS ; i++ )
        m->level[i].state = NORMAL;

}

