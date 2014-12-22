#include "game.h"

using namespace sdl;

const int SCREEN_WIDTH  = 720;
const int SCREEN_HEIGHT = 480;
static const int VEL = 4;
static const int JMP = 12;
static const int FLOOR = 256;

static const Uint8 level[10][15] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,1,1,1,1,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,1,1,1,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1,1,1,1,1,0,0,1},
    {1,0,1,1,1,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

Game::Game(const std::string &title) : sdl(SDL_INIT_VIDEO|SDL_INIT_TIMER),
                                 win(title, SCREEN_WIDTH, SCREEN_HEIGHT)
{
    win.SetInternalResolution(480,320);
    win.SetDrawColour(100,75,25);
}

int Game::Start()
{
    //Texture bg(sdl.GetPath("res") + "bg.png", win);
    Texture tile(sdl.GetPath("res") + "tile.png", win);
    Player player(sdl.GetPath("res") + "char.png", win, 200, FLOOR);


    //Calculate player center
    int pMidX, pMidY;
    player.QueryDimensions(&pMidX, &pMidY);
    pMidX /= 2;
    pMidY /= 2;

    SDL_Event e;
    bool quit = false;
    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.scancode)
                {
                case SDL_SCANCODE_LEFT:
                case SDL_SCANCODE_A:
                    //go left
                    player.isLeft = true;
                    break;
                case SDL_SCANCODE_RIGHT:
                case SDL_SCANCODE_D:
                    //go right
                    player.isRight = true;
                    break;
                case SDL_SCANCODE_UP:
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_SPACE:
                    //go up
                    if (!player.isFalling & !player.isJumping)
                        player.isJumping = true;
                    break;
                case SDL_SCANCODE_DOWN:
                case SDL_SCANCODE_S:
                    //go down
                    //player.velY += VEL;
                    break;
                case SDL_SCANCODE_ESCAPE:
                    //escape
                    quit = true;
                    break;
                default:
                    break;
                }
            }
            else if (e.type == SDL_KEYUP)
            {
                switch (e.key.keysym.scancode)
                {
                case SDL_SCANCODE_LEFT:
                case SDL_SCANCODE_A:
                    //go left
                    player.isLeft = false;
                    break;
                case SDL_SCANCODE_RIGHT:
                case SDL_SCANCODE_D:
                    //go right
                    player.isRight = false;
                    break;
                case SDL_SCANCODE_UP:
                case SDL_SCANCODE_W:
                    //go up
                    //player.velY += VEL;
                    break;
                case SDL_SCANCODE_DOWN:
                case SDL_SCANCODE_S:
                    //go down
                    //player.velY -= VEL;
                    break;
                default:
                    break;
                }
            }
            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                quit = true;
            }
        }

        //Player velocity
        if (player.isJumping)
        {
            player.velY -= JMP;
            player.isJumping = false;
            player.isFalling = true;
        }

        player.velX = 0;
        if (player.isLeft)
            player.velX -= VEL;
        if (player.isRight)
            player.velX += VEL;

        //Player position
        player.posX += player.velX;
        if (player.posX + pMidX < 0)
            player.posX = SCREEN_WIDTH - pMidX;
        else if (player.posX + pMidX > SCREEN_WIDTH)
            player.posX = -pMidX;
        player.posY += player.velY;
        if (player.posY + pMidY < 0)
            player.posY = SCREEN_HEIGHT - pMidY;
        else if (player.posY + pMidY > SCREEN_HEIGHT)
            player.posY = -pMidY;

        //gravity
        if (player.isFalling)
            player.velY += 1;

        //hardcoded floor
        if (player.posY >= FLOOR)
        {
            player.isFalling = false;
            player.posY = FLOOR;
            player.velY = 0;
        }

        //Render the scene
        win.Clear();
        //win.CopyTexture(bg);
        for (int y=0; y<10; y++)
        {
            for (int x=0; x<15; x++)
            {
                if (level[y][x] == 1)
                    win.CopyTexture(tile, x*32, y*32);
            }
        }
        win.CopyTexture(player, player.posX, player.posY);
        win.Present();
    }

    return 0;
}
