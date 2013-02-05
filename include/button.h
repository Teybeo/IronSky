#ifndef _BUTTON_GUARD
#define _BUTTON_GUARD

#include "SDL_video.h"

#include <stdbool.h>

typedef enum ButtonState {

    NORMAL,     // au repos
    HOVER,      // survolé
    DISABLED    // désactivé

} ButtonState;

typedef struct Button {

    SDL_Rect rect;     // rectangle définissant le bouton
    Uint32 color[2];   // couleur pour chaque état
    ButtonState state; // état du bouton

} Button;

void Button_UpdateState(Button *button, int mouseX, int mouseY);
void Button_Draw(Button b, SDL_Surface* screen);
Button Button_Create(int x, int y, int w, int h, Uint32 colorNormal, Uint32 colorHover);
bool isInBox(SDL_Rect rect, int x, int y);

#endif // BUTTON

