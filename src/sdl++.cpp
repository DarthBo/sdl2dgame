#include "sdl++.h"

using namespace sdl;


void sdl::logSDLError(const std::string &msg, std::ostream &os)
{
    os << msg << " SDL error: " << SDL_GetError() << std::endl;
}

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

void Window::SetInternalResolution(int w, int h)
{
    SDL_RenderSetLogicalSize(ren, w, h);
}

void Window::SetDrawColour(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    SDL_SetRenderDrawColor(ren, r, g, b, a);
}

void Window::EnableLinearScaling(bool enable)
{
    if (enable)
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");  // make the scaled rendering look smoother.
    else
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
}

/*
void Window::CopyTexture (const Texture &texture, const SDL_Rect* srcrect,
                                                const SDL_Rect* dstrect)
{
    if (SDL_RenderCopy(ren, texture.tex, srcrect, dstrect) < 0)
        logSDLError("Window::CopyTexture");
}*/

void Window::CopyTexture (const Texture &texture, int x, int y)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    texture.QueryDimensions(&(rect.w),&(rect.h));

    if (SDL_RenderCopy(ren, texture.tex, nullptr, &rect) < 0)
        logSDLError("Window::CopyTexture");
}

void Window::CopyTexture (const Texture &texture, int x, int y, int w, int h)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    if (SDL_RenderCopy(ren, texture.tex, nullptr, &rect) < 0)
        logSDLError("Window::CopyTexture");
}

void Window::Present()
{
    SDL_RenderPresent(ren);
}

/**** Texture ****/

Texture::Texture(const std::string &file, const Window &window, bool enableAlpha)
{
    tex = IMG_LoadTexture(window.ren, file.c_str());
    if (tex == nullptr)
        logSDLError("Texture constr");
    else if (enableAlpha)
        SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);
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

void Texture::ModulateColor(Uint8 red, Uint8 green, Uint8 blue)
{
    SDL_SetTextureColorMod(tex, red, green, blue);
}

void Texture::SetOpacity(Uint8 opacity)
{
    SDL_SetTextureAlphaMod(tex, opacity);
}
