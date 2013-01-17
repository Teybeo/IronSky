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
        else if (m->current == GAMEDEPLOYMENT_STATE)
            gameDeploymentEvent(&m->gameDeployment, ev);
    }

}

void manageLogic(Manager* m) {

    static int gamePhase;

    switch (m->current)
    {
    case MENU_STATE:

        if (m->menu.done == true)
            m->done = true;

        // Passage à l'état LevelMenu
        if (m->menu.goToLevelMenu == true)
        {
            m->current = LEVELMENU_STATE;
            resetInputMenu(&m->menu);

        }
    break;

    case LEVELMENU_STATE:

        if (m->levelMenu.goToGame > 0)
        {
            m->current = GAMEDEPLOYMENT_STATE;
            m->game = gameInit(m->levelMenu.goToGame, m->screen, m->tabSprite);
            m->gameDeployment = gameDeploymentInit(m->screen, &m->game, m->tabSprite[4], m->tabSprite[5]);
            resetInputLevelMenu(&m->levelMenu);
            gamePhase = GAMEDEPLOYMENT_STATE;
        }

        if (m->levelMenu.goToMenu == true)
        {
            m->current = MENU_STATE;
            resetInputLevelMenu(&m->levelMenu);
        }
    break;

    case GAME_STATE:

        gameLogic(&m->game);

        // Passage à l'état GamePause
        if (m->game.done == true)
        {
            m->current = GAMEPAUSE_STATE;
            resetInputGame(&m->game);
        }

        // Passage à l'état GameDeployment
        if (m->game.deployment == true)
        {
            m->current = GAMEDEPLOYMENT_STATE;
            resetInputGame(&m->game);
            gamePhase = GAMEDEPLOYMENT_STATE;
        }
    break;

    case GAMEPAUSE_STATE:

        // Passage à l'état Game ou GameDeployment
        if (m->gamePause.resume == true)
        {
            m->current = gamePhase;
            resetInputGamePause(&m->gamePause);
        }

        // Passage à l'état LevelMenu
        if (m->gamePause.changeLevel == true)
        {
            m->current = LEVELMENU_STATE;
            resetInputGamePause(&m->gamePause);
            gameDestroy(m->game);
        }

        // Passage à l'état MainMenu
        if (m->gamePause.mainMenu == true)
        {
            m->current = MENU_STATE;
            resetInputGamePause(&m->gamePause);
            gameDestroy(m->game);
        }
    break;

    case GAMEDEPLOYMENT_STATE:

        // Passage à l'état Game
        if (m->gameDeployment.pause == true)
        {
            m->current = GAMEPAUSE_STATE;
            resetInputGameDeployment(&m->gameDeployment);
        }

        // Passage à l'état GameDeployment
        if (m->gameDeployment.game == true)
        {
            m->current = GAME_STATE;
            resetInputGameDeployment(&m->gameDeployment);
            gamePhase = GAME_STATE;
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
    else if (m->current == GAMEDEPLOYMENT_STATE)
        gameDeploymentDraw(m->gameDeployment);


    // Mise à jour du titre de la fenêtre
    char chaine[50] = "";
    if (m->current == MENU_STATE)
        sprintf(chaine, "Menu");
    else if (m->current == GAME_STATE)
        sprintf(chaine, "Game");
    else if (m->current == LEVELMENU_STATE)
        sprintf(chaine, "LevelMenu");
    else if (m->current == GAMEPAUSE_STATE)
        sprintf(chaine, "GamePause");
    else if (m->current == GAMEDEPLOYMENT_STATE)
        sprintf(chaine, "GameDeployment");

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
