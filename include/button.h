#ifndef _BUTTON_GUARD
#define _BUTTON_GUARD

#include <stdbool.h>
#include "SDL.h"
#include "point.h"

typedef enum {
    NORMAL,
    HOVER,
    DISABLED
} ButtonState;

typedef struct Button {

    SDL_Rect rect;     // rectangle définissant le bouton
    Uint32 color[2];   // couleur pour chaque état
    ButtonState state; // état du bouton

} Button;

void updateButtonState(Button *button, int mouseX, int mouseY);
void drawButton(Button b, SDL_Surface* screen);
Button createButton(int x, int y, int w, int h, Uint32 colorNormal, Uint32 colorHover);
bool isInBox(SDL_Rect rect, int x, int y);

#endif // BUTTON

