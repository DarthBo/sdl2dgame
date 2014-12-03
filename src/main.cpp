#include <iostream>
#include "sdl++.h"

using namespace sdl;

int main(int argc, char **argv) {

    try {
        SDL sdl(SDL_INIT_VIDEO|SDL_INIT_TIMER);
        
        Window win("Hello world", 640, 480);
        Texture tex(sdl.GetPath("res") + "kerst.png", win);
        
        win.Clear();
        win.CopyTexture(tex);
        win.Present();
        
        SDL_Delay(2000);
        
        return 0;
    }

    catch (const InitError& err) {
        std::cerr
            << "Error while initializing SDL:  "
            << err.what() << std::endl;
    }

    return 1;
}
