#include <iostream>
#include "sdl++.h"


int main(int argc, char **argv) {

    try {
        SDL sdl(SDL_INIT_VIDEO|SDL_INIT_TIMER);

        /* ... */
        std::cout << "base path: " << sdl.GetPath() << std::endl;

        return 0;
    }

    catch (const InitError& err) {
        std::cerr
            << "Error while initializing SDL:  "
            << err.what() << std::endl;
    }

    return 1;
}
