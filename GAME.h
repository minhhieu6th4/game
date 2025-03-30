#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <iostream>
#include <vector>
#include "map.h"
#include "player.h"
#include "EnemyTank.h"
#include "bullet.h"
#include <SDL_mixer.h>

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int TILE_SIZE = 40;
const int MAP_WIDTH = SCREEN_WIDTH/ TILE_SIZE;
const int MAP_HEIGHT = SCREEN_HEIGHT/ TILE_SIZE;

class Game
{
public:
	Game();
	void render();
	void run();
	vector <Wall> walls;
	PlayerTank player = PlayerTank(((MAP_WIDTH - 1) / 3 ) * TILE_SIZE , ((MAP_HEIGHT - 1) / 3 ) * TILE_SIZE);
	int enemyNumber = 4;
	vector <EnemyTank> enemies;
	void spawnEnemies();
	void handleEvents();
	void generateWall();
	void showSplashScreen();
	~Game();
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool running;
	void update();
};


#endif
