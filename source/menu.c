#include "menu.h"

void menuDraw(Menu m) {

    SDL_FillRect(m.screen, NULL, 0x000000);

    drawButton(m.play, m.screen);
    drawButton(m.quit, m.screen);

    SDL_Flip(m.screen);

}

void menuEvent(Menu* m, SDL_Event ev) {

    if (ev.type == SDL_MOUSEMOTION)
    {
        updateButtonState(&m->play, ev.motion.x, ev.motion.y);
        updateButtonState(&m->quit, ev.motion.x, ev.motion.y);
    }

    if (ev.type == SDL_MOUSEBUTTONUP)
    {
        if (m->play.state == HOVER)
            m->goToLevelMenu = true;
        if (m->quit.state == HOVER)
            m->done = true;
    }

}

Menu menuInit(SDL_Surface* screen) {

    Menu m = {};

    m.screen = screen;

    m.play = createButton(500, 100, 200, 100, 0x5321ff, 0x9921ff);
    m.quit = createButton(500, 500, 200, 100, 0x5321ff, 0x9921ff);

    return m;
}

void resetInputMenu(Menu* m) {

    m->goToLevelMenu = false;

    m->play.state = NORMAL;

}
