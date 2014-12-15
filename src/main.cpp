#include <iostream>
#include <map>
#include "game.h"

int main() {

    try {
        Game g("testje");

        g.Start();
    }
    catch (const sdl::InitError& err) {
        std::cerr
            << "Error while initializing SDL:  "
            << err.what() << std::endl;
    }

    return 0;
}
