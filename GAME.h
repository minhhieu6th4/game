#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <iostream>
#include <vector>
#include "map.h"
#include "player.h"

using namespace std;

class Game
{
public:
	Game();
	void render();
	void run();
	vector <Wall> walls;
	PlayerTank player;
	void generateWall();
	~Game();
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool running;
};

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int TILE_SIZE = 40;
const int MAP_WIDTH = SCREEN_WIDTH/ TILE_SIZE;
const int MAP_HEIGHT = SCREEN_HEIGHT/ TILE_SIZE;

#endif
