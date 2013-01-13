#include "manager.h"

#include <stdbool.h>

int main() {

    Manager m = {};

    if (managerInit(&m) == false)
        return EXIT_FAILURE;

    runManager(m);

    return EXIT_SUCCESS;

}
