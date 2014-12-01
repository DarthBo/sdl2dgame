#include "sdl++.h"

/**** InitError ****/

InitError::InitError(): exception(), msg(SDL_GetError()) {}
InitError::InitError(const std::string& m): exception(), msg(m) {}
InitError::~InitError() throw() {}
const char* InitError::what() const throw() {
    return msg.c_str();
}


/**** SDL ****/

SDL::SDL(Uint32 flags) throw(InitError) {
    if (SDL_Init(flags) != 0)
        throw InitError();

    char *bp = SDL_GetBasePath();
    if (bp) {
        base_path = bp; //copy
        SDL_free(bp);
    } else {
        base_path = "./";
    }
}

SDL::~SDL() {
    SDL_Quit();
}

const std::string& SDL::GetPath() const
{
    return base_path;
}
