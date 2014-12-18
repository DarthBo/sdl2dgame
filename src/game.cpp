#include "game.h"

using namespace sdl;

static const int VEL = 5;

int Game::Start()
{
    Texture bg(sdl.GetPath("res") + "bg.png", win);
    Player player(sdl.GetPath("res") + "front.png", win, 320, 300);
    player.ModulateColor(255, 0, 0);

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
            if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
            {
                switch (e.key.keysym.scancode)
                {
                    case SDL_SCANCODE_LEFT:
                    case SDL_SCANCODE_A:
                        //goleft
                        player.velX -= VEL;
                        break;
                    case SDL_SCANCODE_RIGHT:
                    case SDL_SCANCODE_D:
                        //goright
                        player.velX += VEL;
                        break;
                    case SDL_SCANCODE_UP:
                    case SDL_SCANCODE_W:
                        //goup
                        player.velY -= VEL;
                        break;
                    case SDL_SCANCODE_DOWN:
                    case SDL_SCANCODE_S:
                        //godown
                        player.velY += VEL;
                        break;
                    case SDL_SCANCODE_ESCAPE:
                        //escape
                        quit = true;
                        break;
                    default:
                        break;
                }
            }
            else if (e.type == SDL_KEYUP && e.key.repeat == 0)
            {
                switch (e.key.keysym.scancode)
                {
                    case SDL_SCANCODE_LEFT:
                    case SDL_SCANCODE_A:
                        //goleft
                        player.velX += VEL;
                        break;
                    case SDL_SCANCODE_RIGHT:
                    case SDL_SCANCODE_D:
                        //goright
                        player.velX -= VEL;
                        break;
                    case SDL_SCANCODE_UP:
                    case SDL_SCANCODE_W:
                        //goup
                        player.velY += VEL;
                        break;
                    case SDL_SCANCODE_DOWN:
                    case SDL_SCANCODE_S:
                        //godown
                        player.velY -= VEL;
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
        //Calculate position
        int pMidX, pMidY;
        player.QueryDimensions(&pMidX, &pMidY);
        pMidX /= 2;
        pMidY /= 2;

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

        //Render the scene
        win.Clear();
        win.CopyTexture(bg);
        win.CopyTexture(player, player.posX, player.posY);
        win.Present();
    }

    return 0;
}