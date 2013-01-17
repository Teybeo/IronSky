#include "gamePause.h"

void gamePauseDraw(GamePause m) {

    SDL_FillRect(m.screen, NULL, 0x000000);

    drawButton(m.resumeBtn, m.screen);
    drawButton(m.changeLevelBtn, m.screen);
    drawButton(m.mainMenuBtn, m.screen);

    SDL_Flip(m.screen);

}

void gamePauseEvent(GamePause* m, SDL_Event ev) {

    switch (ev.type)
    {
    case SDL_KEYDOWN:

        // Sortie de pause
        if (ev.key.keysym.sym == SDLK_ESCAPE)
            m->resume = true;

    break;

    case SDL_MOUSEMOTION:

        updateButtonState(&m->resumeBtn, ev.motion.x, ev.motion.y);
        updateButtonState(&m->changeLevelBtn, ev.motion.x, ev.motion.y);
        updateButtonState(&m->mainMenuBtn, ev.motion.x, ev.motion.y);

    break;

    case SDL_MOUSEBUTTONUP:

        if (m->resumeBtn.state == HOVER)
            m->resume = true;
        if (m->changeLevelBtn.state == HOVER)
            m->changeLevel = true;
        if (m->mainMenuBtn.state == HOVER)
            m->mainMenu = true;
    break;
    }

}

GamePause gamePauseInit(SDL_Surface* screen) {

    GamePause m = {};

    m.screen = screen;

    m.resumeBtn = createButton(500, 100, 200, 100, 0x5321ff, 0x9921ff);
    m.changeLevelBtn = createButton(500, 300, 200, 100, 0x5321ff, 0x9921ff);
    m.mainMenuBtn = createButton(500, 500, 200, 100, 0x5321ff, 0x9921ff);

    return m;
}

void resetInputGamePause(GamePause* g) {

    g->changeLevel = false;
    g->mainMenu = false;
    g->resume = false;

    g->changeLevelBtn.state = NORMAL;
    g->mainMenuBtn.state = NORMAL;
    g->resumeBtn.state = NORMAL;

}

