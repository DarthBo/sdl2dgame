#include <iostream>
#include "sdl++.h"

using namespace sdl;


const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char **argv) {

    try {
        SDL sdl(SDL_INIT_VIDEO|SDL_INIT_TIMER);
        
        Window win("Hello world", SCREEN_WIDTH, SCREEN_HEIGHT);
        Texture tex(sdl.GetPath("res") + "kerst.png", win);

        SDL_Event e;
        bool quit = false;
        while (!quit){
            while (SDL_PollEvent(&e)){
                if (e.type == SDL_QUIT){
                    quit = true;
                }
                if (e.type == SDL_KEYDOWN){
                    quit = true;
                }
                if (e.type == SDL_MOUSEBUTTONDOWN){
                    quit = true;
                }
            }
            //Render the scene
            win.Clear();
            win.CopyTexture(tex);
            win.Present();
        }
        
        return 0;
    }

    catch (const InitError& err) {
        std::cerr
            << "Error while initializing SDL:  "
            << err.what() << std::endl;
    }

    return 1;
}
