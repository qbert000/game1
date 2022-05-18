#ifndef character_h
#define character_h

#include "BaseObject.h"
#include "commonFunc.h"

#define step 8
#define GRAVITY_SPEED 0.8
#define MAX_FALL_SPEED 10
#define PLAYER_SPEED 8

class Character : public BaseObject {
public:
	Character();
	~Character();

	enum WalkType {
		WALK_RIGHT = 0,
		WALK_LEFT = 1,
	};

	bool LoadImg(string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	void HandelInputAction(SDL_Event events, SDL_Renderer* screen);
	void set_clip();

	void DoPlayer(Map& map_data);
	void CheckToMap(Map& map_data);
	void SetmapXY(const int map_x, const int map_y) { map_x_ = map_x; map_y_ = map_y; }
	void CenterEntityOnMap(Map& map_data);

private:
	float x_val_;
	float y_val_;

	float x_pos_;
	float y_pos_;

	int width_frame_;
	int height_frame_;

	SDL_Rect frame_clip_[step];
	Input input_type_;
	int frame_;
	int status_;
	bool on_ground;

	int map_x_;
	int map_y_;
};




#endif // !character_h
