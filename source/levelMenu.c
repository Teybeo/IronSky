#include "levelMenu.h"

void levelMenuDraw(LevelMenu m) {

    SDL_FillRect(m.screen, NULL, 0x000000);

    drawButton(m.play, m.screen);
    drawButton(m.quit, m.screen);
    int i;
    for (i = 0 ; i < NBLEVELS ; i++ )
        drawButton(m.level[i], m.screen);

    SDL_Flip(m.screen);

}

void levelMenuEvent(LevelMenu* m, SDL_Event ev) {

    int i;

    if (ev.type == SDL_MOUSEMOTION)
    {
        updateButtonState(&m->play, ev.motion.x, ev.motion.y );
        updateButtonState(&m->quit, ev.motion.x, ev.motion.y );

        for (i = 0 ; i < NBLEVELS ; i++ )
            updateButtonState(&m->level[i], ev.motion.x, ev.motion.y );
    }

    if (ev.type == SDL_MOUSEBUTTONUP)
    {
        if (m->quit.state == HOVER)
            m->goToMenu = true;

        for (i = 0 ; i < NBLEVELS ; i++ )
        {
            if (isInBox(m->level[i].rect, ev.button.x, ev.button.y))
            {
                m->goToGame = i + 1;
                break;
            }
        }

    }

}

LevelMenu levelMenuInit(SDL_Surface* screen) {

    LevelMenu m = {};

    m.screen = screen;
    m.goToGame = -1;
    m.goToMenu = false;
    m.play = createButton(400, 650, 200, 100, 0x145321ff, 0x999921ff);
    m.quit = createButton(700, 650, 200, 100, 0x145321ff, 0x999921ff);

    int i;
    int w = screen->w / 7;
    for (i = 0 ; i < NBLEVELS ; i++ )
    {
        int x = w/2 + 240 * (i % (NBLEVELS/2));
        int y = 150 + 240 * ((i/5) % (NBLEVELS/2));
        m.level[i] = createButton(x, y, w, w, 0x804030, 0x808030);
    }


    return m;
}

void resetInputLevelMenu(LevelMenu* m) {

    m->goToGame = -1;
    m->goToMenu = false;

    m->quit.state = NORMAL;
    int i;
    for (i = 0 ; i < NBLEVELS ; i++ )
        m->level[i].state = NORMAL;


}

