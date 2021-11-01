#include "Globals.h"
#include "Application.h"
#include "ModuleSceneKen.h"
#include "ModuleSceneHonda.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"

ModuleSceneHonda::ModuleSceneHonda(bool start_enabled) : Module(start_enabled)
{
	// Ground:
	ground.x = 8;
	ground.y = 375;
	ground.w = 848;
	ground.h = 65;
	ground_draw_pos = iPoint(-96,170);

	// Background:
	background.x = 120;
	background.y = 128;
	background.w = 671;
	background.h = 199;
	background_draw_pos = iPoint(-16,-5);

	// Ceiling: 
	ceiling.x = 91;
	ceiling.y = 8;
	ceiling.w = 765;
	ceiling.h = 48;
	ceiling_draw_pos = iPoint(-68, -5);

	// Bath Tub:
	bath_tub.x = 164;
	bath_tub.y = 66;
	bath_tub.w = 336;
	bath_tub.h = 51;
	bath_tub_draw_pos = iPoint(140, 136);

	// Bath Tub Water:
	bath_tub_water.frames.push_back({8, 448, 284, 18});
	bath_tub_water.frames.push_back({296, 448, 284, 18});
	bath_tub_water.speed = 0.08f;
	bath_tub_water_draw_pos = iPoint(168, 148);
}

ModuleSceneHonda::~ModuleSceneHonda()
{
}

bool ModuleSceneHonda::Start()
{
	LOG("Loading honda scene");
	
	graphics = App->textures->Load("honda_stage2.png");

	// Enable the player module:
	App->player->Enable();

	// Set Position:
	App->player->position = iPoint(0, 0);

	// Clamp player movement for scene. If not specified, x_clamp_min = INT_MIN, x_clamp_max = INT_MAX:
	App->player->x_clamp_min = 0;
	App->player->x_clamp_max = 614;
	App->player->y_default = 123;
	

	// Play background music:
	App->audio->PlayMusic("honda.ogg");

	return true;
}

update_status ModuleSceneHonda::Update()
{
	// Switch back to ken scene if user presses space:
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
	{
		LOG("FROM HONDA TO KEN");
		App->fade->FadeToBlack(App->scene_ken, App->scene_honda, 3.0f);
		/*return UPDATE_CONTINUE;*/
	}

	// The following code is used to move the objects in the scene by changing 
	// the object in the code:
	/*
	
	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)
	{
		bath_tub_water_draw_pos.y++;
	} 
	else if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
	{
		bath_tub_water_draw_pos.y--;
	}
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
	{
		bath_tub_water_draw_pos.x--;
	}
	else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
	{
		bath_tub_water_draw_pos.x++;
	}
	
	LOG("X: %i Y: %i", bath_tub_water_draw_pos.x, bath_tub_water_draw_pos.y);
	
	*/

	// Render entities in the scene:

	// Render Ground:
	App->renderer->Blit(
		graphics, 
		ground_draw_pos.x, 
		ground_draw_pos.y,
		&ground, 
		1.0f
	);

	// Render Background:
	App->renderer->Blit(
		graphics, 
		background_draw_pos.x, 
		background_draw_pos.y,
		&background, 
		0.8f
	);

	// Render Ceiling:
	App->renderer->Blit(
		graphics,
		ceiling_draw_pos.x,
		ceiling_draw_pos.y,
		&ceiling,
		0.8f
	);

	// Render Bath Tub:
	App->renderer->Blit(
		graphics,
		bath_tub_draw_pos.x,
		bath_tub_draw_pos.y,
		&bath_tub,
		1.0f
	);

	// Render Bath Tub Water:
	App->renderer->Blit(
		graphics,
		bath_tub_water_draw_pos.x,
		bath_tub_water_draw_pos.y,
		&(bath_tub_water.GetCurrentFrame()),
		1.0f
	);

	return UPDATE_CONTINUE;
}

bool ModuleSceneHonda::CleanUp()
{
	LOG("Unloading honda scene");

	App->textures->Unload(graphics);
	App->player->Disable();
	
	return true;
}
