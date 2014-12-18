#include "game.h"

using namespace sdl;

static const int VEL = 5;
static const int JMP = 15;
static const int FLOOR = 300;

int Game::Start()
{
    Texture bg(sdl.GetPath("res") + "bg.png", win);
    Player player(sdl.GetPath("res") + "front.png", win, 320, FLOOR);
    player.ModulateColor(255, 0, 0);

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
        if (player.posY > FLOOR)
        {
            player.posY = FLOOR;
            player.velY = 0;
            player.isFalling = false;
        }

        //Render the scene
        win.Clear();
        win.CopyTexture(bg);
        win.CopyTexture(player, player.posX, player.posY);
        win.Present();
    }

    return 0;
}
