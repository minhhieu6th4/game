#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

//#include<window.h>
#include<string>
#include<SDL_image.h>
#include<SDL.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>



static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

// SCREEN

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;


const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR = 255;



#endif
