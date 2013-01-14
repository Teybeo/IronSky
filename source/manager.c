#include "manager.h"

#include "fonctionCSDL.h"

#include <memory.h>
#include <time.h>

unsigned int updateChrono();
SDL_Surface** loadSprites();

void manageDraw(Manager* m);
void manageLogic(Manager* m);
void manageEvent(Manager* m);

void runManager(Manager m) {

    while (m.done != true) {

        manageEvent(&m);
        manageLogic(&m);
        manageDraw(&m);

    }

}

void manageEvent(Manager* m) {

    SDL_Event ev;

    while (SDL_PollEvent(&ev))
    {
        if (ev.type == SDL_QUIT)
            m->done = true;

        if (m->current == MENU_STATE)
            menuEvent(&m->menu, ev);
        else if (m->current == GAME_STATE)
            gameEvent(&m->game, ev);
        else if (m->current == LEVELMENU_STATE)
            levelMenuEvent(&m->levelMenu, ev);
        else if (m->current == GAMEPAUSE_STATE)
            gamePauseEvent(&m->gamePause, ev);
    }

}

void manageLogic(Manager* m) {

    switch (m->current)
    {
    case MENU_STATE:

        if (m->menu.done == true)
            m->done = true;

        // Passage à l'état LevelMenu
        if (m->menu.goToLevelMenu == true)
        {
            m->current = LEVELMENU_STATE;
            m->menu.goToLevelMenu = false;
        }

    break;

    case LEVELMENU_STATE:

        if (m->levelMenu.goToGame != -1)
        {
            m->current = GAME_STATE;
            m->game = gameInit(m->levelMenu.goToGame, m->screen, m->tabSprite);
            m->levelMenu.goToGame = -1;
        }

        if (m->levelMenu.goToMenu == true)
        {
            m->current = MENU_STATE;
            m->levelMenu.goToMenu = false;
        }


    break;

    case GAME_STATE:

        gameLogic(&m->game);

        // Passage à l'état GamePause
        if (m->game.done == true)
        {
            m->current = GAMEPAUSE_STATE;
//            gameDestroy(m->game);
            m->game.done = false;
        }

    break;

    case GAMEPAUSE_STATE:

        // Passage à l'état Game
        if (m->gamePause.resume == true)
        {
            m->current = GAME_STATE;
//            gameDestroy(m->game);
            m->gamePause.resume = false;
        }

        // Passage à l'état LevelMenu
        if (m->gamePause.changeLevel == true)
        {
            m->current = LEVELMENU_STATE;
            gameDestroy(m->game);
            m->gamePause.changeLevel = false;
        }

        // Passage à l'état MainMenu
        if (m->gamePause.mainMenu == true)
        {
            m->current = MENU_STATE;
            gameDestroy(m->game);
            m->gamePause.mainMenu = false;
        }


    break;
    }

}

void manageDraw(Manager* m) {

    if (m->current == MENU_STATE)
        menuDraw(m->menu);
    else if (m->current == GAME_STATE)
        gameDraw(m->game);
    else if (m->current == LEVELMENU_STATE)
        levelMenuDraw(m->levelMenu);
    else if (m->current == GAMEPAUSE_STATE)
        gamePauseDraw(m->gamePause);

    // Mise à jour du titre de la fenêtre
    char chaine[50] = "";
    if (m->current == MENU_STATE)
        sprintf(chaine, "Menu");
    else if (m->current == GAME_STATE)
        sprintf(chaine, "Game");
    else if (m->current == LEVELMENU_STATE)
        sprintf(chaine, "LevelMenu");

    char temp[10] = "";
    sprintf(temp, " %u ms", updateChrono());
    strcat(chaine, temp);

    SDL_WM_SetCaption(chaine, NULL);
}

bool managerInit(Manager* m) {

    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return false;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    m->screen = SDL_SetVideoMode(1366, 768, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( m->screen == NULL )
    {
        printf("Unable to set video mode: %s\n", SDL_GetError());
        return false;
    }

    srand(time(NULL));

    m->tabSprite = loadSprites();

    m->menu = menuInit(m->screen);
    m->levelMenu = levelMenuInit(m->screen);
    m->gamePause = gamePauseInit(m->screen);

    m->current = MENU_STATE;

    m->done = false;

    return m;
}

unsigned int updateChrono() {

    static unsigned int precedent = 0;

    unsigned int duration = SDL_GetTicks() - precedent;
    precedent = SDL_GetTicks(); // On met à jour la date de la dernière image

    return duration;
}

SDL_Surface** loadSprites()
{

    SDL_Surface** tabSprite = malloc( sizeof(SDL_Surface*) * 6 );

    tabSprite[0] = memoryImg("image/spaceshipE.png");
    tabSprite[1] = memoryImg("image/junkA.png");
    tabSprite[2] = memoryImg("image/junkC.png");
    tabSprite[3] = memoryImg("image/background.png");
    tabSprite[4] = memoryImg("image/itemA.png");
    tabSprite[5] = memoryImg("image/itemR.png");

    return tabSprite;
}
