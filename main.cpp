#include <iostream>
#include "commonFunc.h"
#include "BaseObject.h"
#include "game_map.h"
#include "character.h"
#include "imptimer.h"

BaseObject g_background;

//SDL_Window* window = NULL;
//SDL_Surface* surface = NULL;

bool init() {
	bool success = true;
	int res = SDL_Init(SDL_INIT_VIDEO);
	if (res < 0) return false;
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	g_window = SDL_CreateWindow("game SDL lan 4", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGH, SDL_WINDOW_SHOWN);

	if (g_window == NULL) success = false;
	else {
		g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
		if (g_screen == NULL) {
			success = false;
		}
		else {
			SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
			int ImgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(ImgFlags) && ImgFlags)) {
				success = false;
			}
		}
	}

	return success;
}

bool LoadBackground() {
	bool res = g_background.LoadImg("img//background.png", g_screen);
	if (res == false) return false;
	else return true;
}

void close() {
	g_background.Free();
	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;
	SDL_DestroyWindow(g_window);
	g_window = NULL;
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* argv[]) {

	ImpTimer fps_timer;

	if (init() == false) return -1;
	if (LoadBackground() == false) return -1;

	gamemap game_map;
	game_map.LoadMap("map/map01.dat");
	game_map.LoadTiles(g_screen);

	Character p_player;
	p_player.LoadImg("img/player_right.png", g_screen);
	p_player.set_clip();

	
	bool is_quit = false;
	while (!is_quit) {
		fps_timer.Start();
		while (SDL_PollEvent( &g_event) != 0) {
			if (g_event.type == SDL_QUIT) {
				is_quit = true;
			}

			p_player.HandelInputAction(g_event, g_screen);
		}

		SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
		SDL_RenderClear(g_screen);

		g_background.Render(g_screen, NULL);

		Map map_data = game_map.getMap();



		//game_map.DrawMap(g_screen);

		p_player.SetmapXY(map_data.start_x_, map_data.start_y_);
		p_player.DoPlayer(map_data);

		p_player.Show(g_screen);


		game_map.setMap(map_data);
		game_map.DrawMap(g_screen);

		SDL_RenderPresent(g_screen);

		int real_imp_time = fps_timer.Get_ticks();
		int time_one_frame = 1000 / FRAME_PER_SECOND; // ms

		if (real_imp_time < time_one_frame) {
			int delay_time = time_one_frame - real_imp_time;
			if (delay_time >= 0) {
				SDL_Delay(delay_time);
			}
		}
	}
	

	close();
	return 0;
}
