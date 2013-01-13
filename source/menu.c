#include "menu.h"

void menuDraw(Menu m) {

    SDL_BlitSurface(m.background, NULL, m.screen, NULL);

    drawButton(m.play, m.screen);
    drawButton(m.quit, m.screen);

    SDL_Flip(m.screen);

}

void menuEvent(Menu* m, SDL_Event ev) {

    if (ev.type == SDL_MOUSEMOTION)
    {
        updateButtonState(&m->play, (Point) {ev.motion.x, ev.motion.y} );
        updateButtonState(&m->quit, (Point) {ev.motion.x, ev.motion.y} );
    }

    if (ev.type == SDL_MOUSEBUTTONUP)
    {
        if (m->play.state == HOVER)
            m->gotoGame = true;
        if (m->quit.state == HOVER)
            m->done = true;
    }

}

Menu menuInit(SDL_Surface* screen) {

    Menu m = {};

    m.screen = screen;

    m.play.rect.x = 500;
    m.play.rect.y = 100;
    m.play.rect.w = 200;
    m.play.rect.h = 100;
    m.play.color[NORMAL] = 0x145321ff;
    m.play.color[HOVER] = 0x999921ff;
    m.play.state = false;

    m.quit.rect.x = 500;
    m.quit.rect.y = 500;
    m.quit.rect.w = 200;
    m.quit.rect.h = 100;
    m.quit.color[NORMAL] = 0x145321ff;
    m.quit.color[HOVER] = 0x999921ff;
    m.quit.state = false;

    return m;
}


