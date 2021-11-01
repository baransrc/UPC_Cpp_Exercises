#ifndef __MODULESCENEHONDA_H__
#define __MODULESCENEHONDA_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Point.h"

struct SDL_Texture;

class ModuleSceneHonda : public Module
{
public:
	ModuleSceneHonda(bool start_enabled = true);
	~ModuleSceneHonda();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Rect ceiling;
	SDL_Rect ground;
	SDL_Rect background;
	SDL_Rect bath_tub;
	Animation bath_tub_water;

private:
	iPoint ceiling_draw_pos;
	iPoint ground_draw_pos;
	iPoint background_draw_pos;
	iPoint bath_tub_draw_pos;
	iPoint bath_tub_water_draw_pos;
};

#endif // __MODULESCENEHONDA_H__