#pragma once

#include <exception>
#include <string>
#include "SDL.h"

#ifdef _WIN32
    const char PATH_SEP = '\\';
#else
    const char PATH_SEP = '/';
#endif

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

        const std::string& GetPath() const;
    private:
        std::string base_path;
        //const std::string pref_path;
};

class Window
{

};
