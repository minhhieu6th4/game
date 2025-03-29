#include "game.h"
#include "player.h"
#include <algorithm>

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
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        cout << "SDL không thể khởi tạo! SDL_Error: " << SDL_GetError() << endl;
        running = false;
    }

    // Khởi tạo SDL_mixer với tần số 44100 Hz, định dạng 16-bit stereo, 2 kênh, và buffer 2048
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        cout << "SDL_mixer không thể khởi tạo! Mix_Error: " << Mix_GetError() << endl;
        running = false;
    }

    generateWall();
    spawnEnemies();
}

void Game :: generateWall()
{
    for ( int i = 3; i < MAP_HEIGHT - 3; i+=2)
    {
        for ( int j = 3; j < MAP_WIDTH - 3 ; j+=2)
        {
            Wall w = Wall(j*TILE_SIZE, i*TILE_SIZE);
            walls.push_back(w);
        }
    }
}

void Game :: spawnEnemies()
{
    enemies.clear();
    for ( int i = 0 ; i < enemyNumber ; i++)
    {
        int ex,ey;
        bool validPosition = false;
        while (!validPosition)
        {
            ex = (rand() % (MAP_WIDTH - 2) + 1) * TILE_SIZE;
            ey = (rand() % (MAP_HEIGHT - 2) +1) * TILE_SIZE;
            validPosition = true;
            for ( const auto& wall : walls)
            {
                if (wall.active && wall.x == ex && wall.y == ey)
                {
                    validPosition = false;
                    break;
                }
            }
        }
        enemies.push_back(EnemyTank(ex,ey));
    }
}

void Game::update()
{
    // Cập nhật đạn của người chơi
    player.updateBullets();

    // Cập nhật và di chuyển kẻ địch
    for (auto& enemy : enemies)
    {
        enemy.move(walls);
        enemy.updateBullets();
        if (rand() % 100 < 2)
        {
            enemy.shoot();
        }
    }

    // Kiểm tra va chạm giữa đạn của người chơi với kẻ địch
    for (auto& bullet : player.bullets)
    {
        if (!bullet.active) continue;  // Bỏ qua viên đạn không hoạt động

        for (auto& enemy : enemies)
        {
            if (enemy.active && SDL_HasIntersection(&bullet.rect, &enemy.rect))
            {
                enemy.active = false;   // Kẻ địch bị tiêu diệt
                bullet.active = false;  // Viên đạn biến mất
                break; // Dừng kiểm tra sau khi trúng 1 mục tiêu
            }
        }
    }

    // Xóa kẻ địch không hoạt động
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(),[](const EnemyTank &e)
    {
        return !e.active;
    }),enemies.end());

    // Kiểm tra va chạm giữa đạn của kẻ địch và người chơi
    for (auto& enemy : enemies)
    {
        for (auto& bullet : enemy.bullets)
        {
            if (SDL_HasIntersection(&bullet.rect, &player.rect))
            {
                SDL_Event event;
                while (running)
                {
                    while (SDL_PollEvent(&event))
                    {
                        if (event.type == SDL_QUIT) running = false;
                        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) running = false;
                    }

                    SDL_RenderClear(renderer);
                    SDL_Texture* imageTexture = IMG_LoadTexture(renderer, "lose.png");
                    SDL_RenderCopy(renderer, imageTexture, nullptr, nullptr);
                    SDL_DestroyTexture(imageTexture);
                    SDL_RenderPresent(renderer);
                }
                return;
            }
        }
    }

    // Kiểm tra va chạm giữa đạn của người chơi và tường
    for (auto& bullet : player.bullets)
    {
        if (!bullet.active) continue;

        for (auto& wall : walls)
        {
            if (wall.active && SDL_HasIntersection(&bullet.rect, &wall.rect))
            {
                wall.active = false;  // Phá hủy tường
                bullet.active = false; // Đạn biến mất
                break;
            }
        }
    }

    // Kiểm tra va chạm giữa đạn của kẻ địch và tường
    for (auto& enemy : enemies)
    {
        for (auto& bullet : enemy.bullets)
        {
            if (!bullet.active) continue;

            for (auto& wall : walls)
            {
                if (wall.active && SDL_HasIntersection(&bullet.rect, &wall.rect))
                {
                    wall.active = false;  // Phá hủy tường
                    bullet.active = false; // Đạn biến mất
                    break;
                }
            }
        }
    }

    // Xóa tất cả đạn không còn hoạt động
    player.bullets.erase(std::remove_if(player.bullets.begin(), player.bullets.end(),
                                        [](const Bullet &b)
    {
        return !b.active;
    }),
    player.bullets.end());

    for (auto& enemy : enemies)
    {
        enemy.bullets.erase(std::remove_if(enemy.bullets.begin(), enemy.bullets.end(),
                                           [](const Bullet &b)
        {
            return !b.active;
        }),
        enemy.bullets.end());
    }

    // Nếu không còn kẻ địch => thắng game
    if (enemies.empty())
    {
        SDL_Event event;
        while (running)
        {
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT) running = false;
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) running = false;
            }

            SDL_RenderClear(renderer);
            SDL_Texture* imageTexture = IMG_LoadTexture(renderer, "win.png");
            SDL_RenderCopy(renderer, imageTexture, nullptr, nullptr);
            SDL_DestroyTexture(imageTexture);
            SDL_RenderPresent(renderer);
        }
        return;
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
            case SDLK_UP :
                player.move(0,-5,walls);
                break;
            case SDLK_DOWN :
                player.move(0,5,walls);
                break;
            case SDLK_LEFT :
                player.move(-5,0,walls);
                break;
            case SDLK_RIGHT :
                player.move(5,0,walls);
                break;
            case SDLK_SPACE :
                player.shoot();
                break;
            }
        }
    }
}



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

    for (int i = 0; i < int(walls.size()); i++)
    {
        walls[i].render(renderer);
    }

    player.render(renderer);

    for (auto &enemy : enemies)
    {
        enemy.render(renderer);
    }

    SDL_RenderPresent(renderer);
}


void Game :: run()
{
    const int FPS = 60;
    const int frameDelay = 1000 / FPS; // Mỗi frame mất khoảng 16.67ms

    Uint32 frameStart;
    int frameTime;

    while (running)
    {
        frameStart = SDL_GetTicks(); // Lấy thời gian bắt đầu frame

        render();
        update();
        handleEvents();

        // Tính thời gian xử lý 1 frame
        frameTime = SDL_GetTicks() - frameStart;

        // Nếu frame xử lý quá nhanh, tạm dừng để đảm bảo 60 FPS
        if (frameTime < frameDelay)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
}

Game :: ~Game()
{
    Mix_FreeChunk(shootSound);
    Mix_CloseAudio(); // Đóng SDL_mixer
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

