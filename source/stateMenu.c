#include "stateMenu.h"

#include "app.h"

void Menu_Draw(State* state) {

    Menu* menu = (Menu*)state;

    SDL_FillRect(state->screen, NULL, 0x000000);

    drawButton(menu->play, state->screen);
    drawButton(menu->quit, state->screen);

    SDL_Flip(state->screen);

}

void Menu_Event(State* state, SDL_Event ev) {

    Menu* menu = (Menu*)state;

    if (ev.type == SDL_MOUSEMOTION)
    {
        updateButtonState(&menu->play, ev.motion.x, ev.motion.y);
        updateButtonState(&menu->quit, ev.motion.x, ev.motion.y);
    }

    if (ev.type == SDL_MOUSEBUTTONUP)
    {
        if (menu->play.state == HOVER)
            setCurrentState(menu->state.appRef, getLevelMenuState(menu->state.appRef));

        if (menu->quit.state == HOVER)
            App_SetDone(menu->state.appRef);
    }

}

void Menu_Logic(State* state)
{

}

Menu Menu_Create(App* appRef) {

    Menu m = {};

    m.state = createState(appRef, &Menu_Event, &Menu_Logic, &Menu_Draw, "Menu");

    m.play = createButton(583, 100, 200, 100, 0x5321ff, 0x9921ff);
    m.quit = createButton(583, 500, 200, 100, 0x5321ff, 0x9921ff);

    return m;
}

void resetInputMenu(Menu* m) {

    m->play.state = NORMAL;

}
