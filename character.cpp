#include "character.h"


Character::Character() {
	frame_ = 0;
	x_pos_ = 0;
	y_pos_ = 0;
	x_val_ = 0;
	y_val_ = 0;
	width_frame_ = 0;
	height_frame_ = 0;
	status_ = -1;
	input_type_.left_ = 0;
	input_type_.right_ = 0;
	input_type_.jump_ = 0;
	input_type_.down_ = 0;
	input_type_.up_ = 0;
	on_ground = false;

	map_x_ = 0;
	map_y_ = 0;
}

Character::~Character() {

}

bool Character::LoadImg(string path, SDL_Renderer* screen) {
	bool ret = BaseObject::LoadImg(path, screen);
	if (ret == true) {
		width_frame_ = rect_.w / step;
		height_frame_ = rect_.h;
	}
	return ret;
}




void Character::set_clip() {
	if (width_frame_ > 0 && height_frame_ > 0) {
		for (int i = 0; i < step; i++) {
			if (i == 0) {
				frame_clip_[i].x = 0;
			}
			else {
				frame_clip_[i].x = frame_clip_[i - 1].x + width_frame_;
			}
			frame_clip_[i].y = 0;
			frame_clip_[i].w = width_frame_;
			frame_clip_[i].h = height_frame_;
		}
	}
}

void Character::Show(SDL_Renderer* des) {
	LoadImg("img//player_right.png", des);
	
	if (input_type_.left_ == 1 || input_type_.right_ == 1) {
		frame_ = (frame_ + 1)% step;
	}
	else { frame_ = 0; }
	rect_.x = x_pos_ - map_x_;
	rect_.y = y_pos_ - map_y_;

	SDL_Rect* current_clip = &frame_clip_[frame_];
	SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame_, height_frame_ };
	if (status_ == WALK_RIGHT)
	{
		SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
	}
	else {
		SDL_RenderCopyEx(des, p_object_, current_clip, &renderQuad, 0, NULL, SDL_FLIP_HORIZONTAL);
	}
	
}

void Character::HandelInputAction(SDL_Event events, SDL_Renderer* screen) {
	if (events.type == SDL_KEYDOWN) {
		switch (events.key.keysym.sym) {
		case SDLK_RIGHT:
			status_ = WALK_RIGHT;
			input_type_.right_ = 1;
			input_type_.left_ = 0;
			break;
		case SDLK_LEFT:
			status_ = WALK_LEFT;
			input_type_.left_ = 1;
			input_type_.right_ = 0;
			break;
		case SDLK_UP:
			status_ = WALK_LEFT;
			input_type_.up_ = 1;
			input_type_.down_ = 0;
			break;
		case SDLK_DOWN:
			status_ = WALK_RIGHT;
			input_type_.down_ = 1;
			input_type_.up_ = 0;
		default:
			break;
		}
	}
	else if (events.type == SDL_KEYUP) {
		switch (events.key.keysym.sym) {
		case SDLK_RIGHT:
			input_type_.right_ = 0;
			break;
		case SDLK_LEFT:
			input_type_.left_ = 0;
			break;
		case SDLK_UP:
			input_type_.up_ = 0;
			break;
		case SDLK_DOWN:
			input_type_.down_ = 0;
		default:
			break;
		}
	}
}

void Character::DoPlayer(Map& map_data) {
	x_val_ = 0;
	y_val_ += GRAVITY_SPEED;
	if (y_val_ >= MAX_FALL_SPEED) y_val_ = MAX_FALL_SPEED;
	
	if (input_type_.left_ == 1) {
		x_val_ = -PLAYER_SPEED;
	}
	else if (input_type_.right_ == 1) {
		x_val_ = PLAYER_SPEED;
	}

	if (input_type_.up_ == 1) {
		y_val_ = -PLAYER_SPEED;
	}
	else if (input_type_.down_ == 1) {
		y_val_ = PLAYER_SPEED;
	}

	CheckToMap(map_data);
	CenterEntityOnMap(map_data);
}


void Character::CenterEntityOnMap(Map& map_data) {
	map_data.start_x_ = x_pos_ - (SCREEN_WIDTH / 2);
	if (map_data.start_x_ < 0) map_data.start_x_ = 0;
	else if (map_data.start_x_ + SCREEN_WIDTH >= map_data.max_x_) map_data.start_x_ = map_data.max_x_ - SCREEN_WIDTH;

	map_data.start_y_ = y_pos_ - (SCREEN_HEIGH / 2);
	if (map_data.start_y_ < 0) map_data.start_y_ = 0;
	else if (map_data.start_y_ + SCREEN_HEIGH >= map_data.max_y_) map_data.start_y_ = map_data.max_y_ - SCREEN_HEIGH;
}
void Character::CheckToMap(Map& map_data) {
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;
	// check horizontal
	int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;

	x1 = (x_pos_ + x_val_) / TILE_SIZE;
	x2 = (x_pos_ + x_val_ + width_frame_ - 1) / TILE_SIZE;

	y1 = (y_pos_ ) / TILE_SIZE;
	y2 = (y_pos_  + height_min -1) / TILE_SIZE;

	if (x1 > 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
		if (x_val_ > 0) {
			if (map_data.tile[y1][x2] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE) {
				x_pos_ = x2 * TILE_SIZE;
				x_pos_ -= width_frame_ + 1;
				x_val_ = 0;
			}
		}// character is moving to right 
		else if (x_val_ < 0) {
			if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE) {
				x_pos_ = (x1 + 1) * TILE_SIZE;
				x_val_ = 0;
			}
		}
	}

	// check vertical

	int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;
	x1 = (x_pos_) / TILE_SIZE;
	x2 = (x_pos_ + width_min) / TILE_SIZE;

	y1 = (y_pos_ + y_val_) / TILE_SIZE;
	y2 = (y_pos_ + y_val_ + height_frame_ - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
		if (y_val_ > 0) {
			if (map_data.tile[y2][x1] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE) {
				y_pos_ = y2 * TILE_SIZE;
				y_pos_ -= (height_frame_ + 1);
				y_val_ = 0;
				on_ground = true;
			}
		}
		else if (y_val_ < 0) {
			if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y1][x2] != BLANK_TILE) {
				y_pos_ = (y1 + 1) * TILE_SIZE;
				y_val_ = 0;
			}
		}
	}
	x_pos_ += x_val_;
	y_pos_ += y_val_;
	if (x_pos_ < 0) {
		x_pos_ = 0;
	}
	else if (x_pos_ + width_frame_ > map_data.max_x_) {
		x_pos_ = map_data.max_x_ - width_frame_ - 1;
	}
}