#include "game.h"
#include "bullet.h"

using namespace std;



Game:: Game()
{
    running = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        running = false;
    }

    window = SDL_CreateWindow("Battle City", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window)
    {
        cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
        running = false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << endl;
        running = false;
    }
    if (!renderer)
    {
        cerr << "Renderer could not be created! SDL_Error: ";
        running = false;
    }
    generateWall();

    //player = PlayerTank(((MAP_WIDTH - 1) / 2 ) * TILE_SIZE , ((MAP_HEIGHT - 1) / 2 ) * TILE_SIZE);
}

void Game :: generateWall()
{
    for ( int i = 3; i < MAP_HEIGHT - 3; i+=2)
    {
        for ( int j = 3; j < MAP_WIDTH - 3 ; j+=2)
        {
            Wall w = Wall(j*TILE_SIZE , i*TILE_SIZE);
            walls.push_back(w);
        }
    }
}

void Game::update()
{
    player.updateBullets();

    for (auto &bullet : player.bullets)
{
    if (!bullet.active) continue; // Bỏ qua viên đạn đã tắt

    for (auto &wall : walls)
    {
        if (wall.active && SDL_HasIntersection(&bullet.rect, &wall.rect))
        {
            wall.active = false;  // Chỉ vô hiệu hóa tường khi có va chạm
            bullet.active = false; // Đạn cũng biến mất
            break; // Dừng kiểm tra sau khi tìm thấy va chạm
        }
    }
}

}


void Game :: handleEvents()
{
    SDL_Event event;
    while ( SDL_PollEvent(&event))
    {
        if ( event.type == SDL_QUIT)
        {
            running = false;
        }
        else if ( event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
                case SDLK_UP : player.move(0,-5,walls); break;
                case SDLK_DOWN : player.move(0,5,walls); break;
                case SDLK_LEFT : player.move(-5,0,walls); break;
                case SDLK_RIGHT : player.move(5,0,walls); break;
                case SDLK_SPACE : player.shoot(); break;
            }
        }
    }
}

/*void Game ::update()
{
    player.updateBullets();

    for (auto &bullet : player.bullets)
    {
        for (auto &wall : walls)
        {
            wall.active = false;
            bullet.active = false;
            break;
        }
    }
}*/

void Game :: render()
{
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255); // boundaries
    SDL_RenderClear(renderer); // delete color

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (int i = 1; i < MAP_HEIGHT - 1; ++i)
    {
        for (int j = 1; j < MAP_WIDTH - 1; ++j)
        {
            SDL_Rect tile = { j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE };
            SDL_RenderFillRect(renderer, &tile);
        }
    }
        int a = walls.size();
    for ( int i = 0; i<a ; i++)
        {
            walls[i].render(renderer);
        }

    player.render(renderer);

    SDL_RenderPresent(renderer);
}

void Game :: run()
{
    while (running)
    {
        render();
        update();
        handleEvents();
        SDL_Delay(16);
    }
}

Game :: ~Game()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

