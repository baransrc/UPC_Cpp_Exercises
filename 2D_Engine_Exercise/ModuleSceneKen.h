#ifndef __MODULESCENEKEN_H__
#define __MODULESCENEKEN_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Point.h"
#include "PingPong.h"

struct SDL_Texture;

class ModuleSceneKen : public Module
{
public:
	ModuleSceneKen( bool start_enabled = true);
	~ModuleSceneKen();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	
	SDL_Texture* graphics = nullptr;
	SDL_Rect ground;
	SDL_Rect background;
	SDL_Rect foreground_ship;
	Animation flag;
	Animation girl;
	Animation two_guys;
	Animation green_guy;
	Animation blue_guy;
	Animation purple_guy;
	Animation brown_guy;
private:
	PingPong<float> ship_position_anim;
	iPoint ground_draw_pos;
	iPoint background_draw_pos;
	iPoint foreground_ship_draw_pos;
	iPoint flag_draw_pos;
	iPoint girl_draw_pos;
	iPoint green_guy_draw_pos;
	iPoint two_guys_draw_pos;
	iPoint blue_guy_draw_pos;
	iPoint purple_guy_draw_pos;
	iPoint brown_guy_draw_pos;
};

#endif // __MODULESCENEKEN_H__