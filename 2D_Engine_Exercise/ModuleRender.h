#ifndef __MODULERENDER_H__
#define __MODULERENDER_H__

#include "Module.h"
#include "Globals.h"
#include "Point.h"

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

class ModuleRender : public Module
{
public:
	ModuleRender();
	~ModuleRender();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	bool Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section, float speed = 1.0f);

	void MoveCameraToPosition(iPoint position, float speed);

private:
	void LerpToPosition();

public:
	SDL_Renderer* renderer = nullptr;
	SDL_Rect camera;
private:
	bool camera_lerping;
	float camera_lerp_value;
	float camera_lerp_speed;
	iPoint camera_lerp_start;
	iPoint camera_lerp_destination;
};

#endif // __MODULERENDER_H__