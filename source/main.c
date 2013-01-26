#include "app.h"

#include <stdlib.h>

int main() {

    App* IronSky = NULL;

    if (App_New(&IronSky) == false)
        return EXIT_FAILURE;

    App_Run(IronSky);

    return EXIT_SUCCESS;

}










