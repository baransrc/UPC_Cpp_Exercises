#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include "Utilfuncs.h"

ModuleRender::ModuleRender()
{
	camera.x = 0;
	camera.y = 0;
	camera.w = SCREEN_WIDTH * SCREEN_SIZE;
	camera.h = SCREEN_HEIGHT* SCREEN_SIZE;

	camera_lerping = false;
	camera_lerp_destination = iPoint(camera.x, camera.y);
	camera_lerp_start = camera_lerp_destination;
	camera_lerp_speed = 0.0f;
	camera_lerp_value = 0.0f;
}

// Destructor
ModuleRender::~ModuleRender()
{}

// Called before render is available
bool ModuleRender::Init()
{
	LOG("Creating Renderer context");
	bool ret = true;
	Uint32 flags = 0;

	if(VSYNC == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
	}

	renderer = SDL_CreateRenderer(App->window->window, -1, flags);
	
	if(renderer == nullptr)
	{
		LOG("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

update_status ModuleRender::PreUpdate()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleRender::Update()
{
	// debug camera
	int speed = 1;

	/*if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->renderer->camera.y += speed;

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->renderer->camera.y -= speed;

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->renderer->camera.x += speed;

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->renderer->camera.x -= speed;*/

	LerpToPosition();

	return UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	SDL_RenderPresent(renderer);
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
	LOG("Destroying renderer");

	//Destroy window
	if(renderer != nullptr)
	{
		SDL_DestroyRenderer(renderer);
	}

	return true;
}

// Blit to screen
bool ModuleRender::Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section, float speed)
{
	bool ret = true;
	SDL_Rect rect;
	rect.x = (int)(camera.x * speed) + x * SCREEN_SIZE;
	rect.y = (int)(camera.y * speed) + y * SCREEN_SIZE;

	if(section != NULL)
	{
		rect.w = section->w;
		rect.h = section->h;
	}
	else
	{
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	}

	rect.w *= SCREEN_SIZE;
	rect.h *= SCREEN_SIZE;

	if(SDL_RenderCopy(renderer, texture, section, &rect) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

void ModuleRender::MoveCameraToPosition(iPoint position, float speed)
{
	camera_lerping = true;
	camera_lerp_destination = position;
	camera_lerp_speed = speed;
	camera_lerp_value = 0.0f;
	camera_lerp_start = iPoint(camera.x, camera.y);
}

void ModuleRender::LerpToPosition()
{
	if (!camera_lerping)
	{
		return;
	}

	camera_lerp_value += camera_lerp_speed;
	camera_lerp_value = camera_lerp_value > 1.0f ? 1.0f : camera_lerp_value;
	camera.x = utilfuncs::lerp(camera_lerp_start.x, camera_lerp_destination.x, camera_lerp_value);
	camera.y= utilfuncs::lerp(camera_lerp_start.y, camera_lerp_destination.y, camera_lerp_value);

	if (camera.x == camera_lerp_destination.x && camera.y == camera_lerp_destination.y)
	{
		camera_lerp_value = 1.0f;
	}

	if (camera_lerp_value == 1.0f)
	{
		camera_lerping = false;
		camera_lerp_value = 0.0f;
		camera_lerp_destination = {0,0};
		camera_lerp_speed = 0.0f;
		camera_lerp_value = 0.0f;
		camera_lerp_start = {0,0};
	}
}
