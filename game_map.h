#ifndef Game_map_h
#define Game_map_h

#include "BaseObject.h"
#include "commonFunc.h"

#define MAX_TILES 20

class TileMat : public BaseObject {
public: 
	TileMat() { ; };
	~TileMat() { ; };
};

class gamemap {
public:
	gamemap() { ; };
	~gamemap() { ; };

	void LoadMap(const char* name) ;
	void LoadTiles(SDL_Renderer* screen) ;
	void DrawMap(SDL_Renderer* screen) ;
	Map getMap() const { return game_map_; };
	void setMap(Map& game_map) { game_map_ = game_map; }
private:
	Map game_map_;
	TileMat tile_mat_[MAX_TILES];

};





#endif

