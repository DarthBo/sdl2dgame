#pragma once

#include <exception>
#include <string>
#include <iostream>
#include "SDL.h"

#ifdef _WIN32
#include "SDL_image.h"
#elif __linux__
#include "SDL2/SDL_image.h"
#else
#include "SDL2_image/SDL_image.h"
#endif

#ifdef _WIN32
const char PATH_SEP = '\\';
#else
const char PATH_SEP = '/';
#endif

namespace sdl
{
    void logSDLError(const std::string &msg, std::ostream &os = std::cerr);

    class InitError: public std::exception
    {
    public:
        InitError();
        InitError(const std::string&);
        virtual ~InitError() throw();
        virtual const char* what() const throw();
    private:
        std::string msg;
    };
    
    
    class SDL
    {
    public:
        SDL(Uint32 flags = 0) throw(InitError);
        virtual ~SDL();
        
        std::string GetPath(const std::string& subdir) const;
        const std::string& GetPath() const;
    private:
        std::string base_path;
        //const std::string pref_path;
    };
    
    class Window;
    class Texture;
    
    class Window
    {
        friend class Texture;
    public:
        Window(const std::string &title, int w, int h, Uint32 flags = SDL_WINDOW_SHOWN) throw(InitError);
        virtual ~Window();
        
        void Clear();
        void SetInternalResolution(int w, int h);
        void SetDrawColour(Uint8 r, Uint8 g, Uint8 b, Uint8 a = SDL_ALPHA_OPAQUE);
        void EnableLinearScaling(bool enable);

        /*
        void CopyTexture(const Texture &texture,
                         const SDL_Rect* srcrect,
                         const SDL_Rect* dstrect);*/
        void CopyTexture (const Texture &texture, int x=0, int y=0);
        void CopyTexture (const Texture &texture, int x, int y, int w, int h);
        void Present();
        
    private:
        SDL_Window *win;
        SDL_Renderer *ren;
    };
    
    class Texture
    {
        friend class Window;
    public:
        Texture(const std::string &file, const Window &window, bool enableAlpha = false);
        virtual ~Texture();
        void QueryDimensions(int *width, int *height) const;
        void ModulateColor(Uint8 red, Uint8 green, Uint8 blue);
        void SetOpacity(Uint8 opacity);
    private:
        SDL_Texture *tex;
    };
    
    class Event
    {

    };
    
}
