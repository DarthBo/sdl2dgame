#include "sdl++.h"

const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

class Game
{
public:
    Game(const std::string &title) : sdl(SDL_INIT_VIDEO|SDL_INIT_TIMER),
                                     win(title, SCREEN_WIDTH, SCREEN_HEIGHT) {}
    ~Game() {}
    int Start();
private:
    sdl::SDL sdl;
    sdl::Window win;
};

class Player : public sdl::Texture
{
public:
    Player(const std::string &file, const sdl::Window &window, int x, int y)
        : sdl::Texture(file, window), posX(x), posY(y), velX(0), velY(0) {}
    ~Player() {}

    int posX, posY;
    int velX, velY;
};
