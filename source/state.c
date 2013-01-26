#include "state.h"

State createState(App* appRef,
                        void (*event)(State*, SDL_Event),
                        void (*logic)(State*),
                        void (*draw)(State*),
                        char* stateName)
{

    State state = {};

    state.appRef = appRef;
    state.event = event;
    state.logic = logic;
    state.draw = draw;
    state.screen = SDL_GetVideoSurface();
    strncpy(state.stateName, stateName, 50);

    return state;

}
