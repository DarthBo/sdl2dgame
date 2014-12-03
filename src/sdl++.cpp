#include "sdl++.h"

using namespace sdl;

/**** InitError ****/

InitError::InitError(): exception(), msg(SDL_GetError()) {}
InitError::InitError(const std::string& m): exception(), msg(m) {}
InitError::~InitError() throw() {}
const char* InitError::what() const throw() {
    return msg.c_str();
}


/**** SDL ****/

SDL::SDL(Uint32 flags) throw(InitError)
{
    if (SDL_Init(flags) != 0)
        throw InitError("sdl init");
    
    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
        throw InitError("sdl_img init");

    char *bp = SDL_GetBasePath();
    if (bp) {
        base_path = bp; //copy
        SDL_free(bp);

        //save parent directory
        size_t pos = base_path.rfind("bin");
        base_path.resize(pos);
    } else {
        base_path = "";
    }
}

SDL::~SDL()
{
    SDL_Quit();
}

std::string SDL::GetPath(const std::string& subdir) const
{
    if (subdir.length() == 0)
        return base_path;
    else
        return base_path + subdir + PATH_SEP;
}

const std::string& SDL::GetPath() const
{
    return base_path;
}

/**** Window ****/

Window::Window(const std::string &title, int w, int h, Uint32 flags) throw(InitError)
{
    win = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, flags);
    if (win == nullptr)
        throw InitError();
    
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr)
        throw InitError();
}

Window::~Window()
{
    if (ren)
        SDL_DestroyRenderer(ren);
    if (win)
        SDL_DestroyWindow(win);
}

void Window::Clear()
{
    SDL_RenderClear(ren);
}

int Window::CopyTexture(const Texture &texture, const SDL_Rect* srcrect,
                                                const SDL_Rect* dstrect)
{
    return SDL_RenderCopy(ren, texture.tex, srcrect, dstrect);
}

void Window::Present()
{
    SDL_RenderPresent(ren);
}

/**** Texture ****/

Texture::Texture(const std::string &file, const Window &window) throw(InitError)
{
    tex = IMG_LoadTexture(window.ren, file.c_str());
}

Texture::~Texture()
{
    if (tex)
        SDL_DestroyTexture(tex);
}

void Texture::QueryDimensions(int *width, int *height) const
{
    SDL_QueryTexture(tex, NULL, NULL, width, height);
}