#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"
#include "Utilfuncs.h"


// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA
ModulePlayer::ModulePlayer(bool start_enabled) : Module(start_enabled)
{
	position.x = 100;
	position.y = 216;
	x_clamp_min = INT_MIN;
	x_clamp_max = INT_MAX;
	y_default = position.y;

	// idle animation (arcade sprite sheet)
	idle.frames.push_back({ 7, 11, 59, 94 });
	idle.frames.push_back({ 95, 11, 60, 94 });
	idle.frames.push_back({ 184, 11, 59, 94 });
	idle.frames.push_back({ 276, 11, 60, 94 });
	idle.frames.push_back({ 366, 11, 60, 94 });
	idle.speed = 0.2f;
	
	// walk backward animation (arcade sprite sheet)
	backward.frames.push_back({542, 131, 61, 87});
	backward.frames.push_back({628, 129, 59, 90});
	backward.frames.push_back({713, 128, 57, 90});
	backward.frames.push_back({797, 127, 57, 90});
	backward.frames.push_back({883, 128, 58, 91});
	backward.frames.push_back({974, 129, 57, 89});
	backward.speed = 0.2f;

	// DONE 8: setup the walk forward animation from ryu4.png
	forward.frames.push_back({ 6, 128, 64, 92 });
	forward.frames.push_back({ 78, 128, 64, 92 });
	forward.frames.push_back({ 162, 128, 64, 92 });
	forward.frames.push_back({ 259, 128, 64, 92 });
	forward.frames.push_back({ 352, 128, 64, 92 });
	forward.frames.push_back({ 432, 128, 64, 92 });
	forward.speed = 0.2f;
}

ModulePlayer::~ModulePlayer()
{
	// Homework : check for memory leaks

}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("ryu4.png"); // arcade version

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// Update
update_status ModulePlayer::Update()
{
	// DONE 9: Draw the player with its animation
	// make sure to detect player movement and change its
	// position while cycling the animation(check Animation.h)

	int camera_x = -App->renderer->camera.x; // In-game coordinates are inverse of cam coordinates.
	int left_clamp = camera_x / 2;
	int right_clamp = left_clamp + 325; // 325 is camera width/2 - 60 (60 is width of ryu)
	int half_screen = 325;

	position.x = position.x < x_clamp_min ? x_clamp_min : position.x;
	position.x = position.x > x_clamp_max ? x_clamp_max : position.x;
	position.y = y_default; 

	// LOG("Player pos: %i, %i", position.x, position.y);

	if (position.x < left_clamp)
	{
		App->renderer->MoveCameraToPosition(iPoint(App->renderer->camera.x + half_screen, 0), 0.025f);
	}
	else if (position.x > right_clamp)
	{
		App->renderer->MoveCameraToPosition(iPoint(App->renderer->camera.x - half_screen, 0), 0.025f);
	}

	Animation* anim = &idle;

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		anim = &forward;
		position.x++;
	}
	else if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		anim = &backward;
		position.x--;
	}

	App->renderer->Blit(
		graphics,
		position.x,
		position.y,
		&(anim->GetCurrentFrame()),
		1.0f
	);

	anim = nullptr;

	return UPDATE_CONTINUE;
}