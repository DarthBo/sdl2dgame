#include "sdl++.h"

class Game
{
public:
    Game(const std::string &title);
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
        : sdl::Texture(file, window),
          isLeft(false), isRight(false), isFalling(false), isJumping(false),
          posX(x), posY(y), velX(0), velY(0) {}
    ~Player() {}

    bool isLeft;
    bool isRight;
    bool isFalling;
    bool isJumping;

    int posX, posY;
    int velX, velY;
};
