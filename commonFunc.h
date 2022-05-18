#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_


#include <Windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
using namespace std;


 
#define BLANK_TILE 0

//screen
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGH 640
#define SCREEN_BPP 32


#define TILE_SIZE 64

#define MAX_MAP_X 400
#define MAX_MAP_Y 10

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

//const int COLOR_KEY_R = 167;
//const int COLOR_KEY_G = 175;
//const int COLOR_KEY_B = 180;


const int FRAME_PER_SECOND = 50; // fps


const int COLOR_KEY_R = 255;
const int COLOR_KEY_G = 255;
const int COLOR_KEY_B = 255;
const int RENDER_DRAW_COLOR = 0xff;

typedef struct Input {
	int left_;
	int right_;
	int up_;
	int down_;
	int jump_;
}Input;

typedef struct Map {
	int start_x_;
	int start_y_;

	int max_x_;
	int max_y_;

	int tile[MAX_MAP_X][MAX_MAP_Y];
	const char* file_name_;
}Map;

#endif
