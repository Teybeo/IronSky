#include "manager.h"

int main() {

    Manager m = {};

    if (managerInit(&m) == false)
        return EXIT_FAILURE;

    runManager(m);

    return EXIT_SUCCESS;

}
