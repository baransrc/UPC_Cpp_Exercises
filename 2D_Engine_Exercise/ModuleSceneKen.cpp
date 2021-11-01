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


// Reference at https://youtu.be/OEhmUuehGOA?t=72

ModuleSceneKen::ModuleSceneKen(bool start_enabled) : Module(start_enabled)
{
	// ground
	ground.x = 8;
	ground.y = 391;
	ground.w = 896;
	ground.h = 72;
	ground_draw_pos = iPoint(0,170);

	// DONE 2 : setup the foreground (red ship) with
	// coordinates x,y,w,h from ken_stage.png
	foreground_ship.x = 8;
	foreground_ship.y = 24;
	foreground_ship.w = 512;
	foreground_ship.h = 181;
	foreground_ship_draw_pos = iPoint(0, -5);

	// Ship y position animation:
	ship_position_anim = PingPong<float>();
	ship_position_anim.speed = 0.01f;

	// Background / sky
	background.x = 72;
	background.y = 208;
	background.w = 768;
	background.h = 176;
	background_draw_pos = iPoint(0,0);

	// flag animation
	flag.frames.push_back({848, 208, 40, 40});
	flag.frames.push_back({848, 256, 40, 40});
	flag.frames.push_back({848, 304, 40, 40});
	flag.speed = 0.08f;
	flag_draw_pos = iPoint(560, 8);

	// DONE 4: Setup Girl Animation from coordinates from ken_stage.png
	girl.frames.push_back({ 624, 16, 32, 56 });
	girl.frames.push_back({ 624, 80, 32, 56 });
	girl.frames.push_back({ 624, 144, 32, 56 });
	girl.speed = 0.06f;
	girl_draw_pos = iPoint(
		200 - foreground_ship.x + foreground_ship_draw_pos.x,
		128 - foreground_ship.y + foreground_ship_draw_pos.y);

	// Setup Animation of green guy on the ship:
	green_guy.frames.push_back({ 664, 16, 32, 56 });
	green_guy.frames.push_back({ 664, 80, 32, 56 });
	green_guy.speed = 0.04f;
	green_guy_draw_pos = iPoint(
		232 - foreground_ship.x + foreground_ship_draw_pos.x,
		128 - foreground_ship.y + foreground_ship_draw_pos.y);

	// Setup Animation of blue guy on the ship:
	blue_guy.frames.push_back({ 704, 16, 48, 56 });
	blue_guy.frames.push_back({ 704, 80, 48, 56 });
	blue_guy.frames.push_back({ 704, 144, 48, 56 });
	blue_guy.speed = 0.06f;
	blue_guy_draw_pos = iPoint(
		296 - foreground_ship.x + foreground_ship_draw_pos.x,
		120 - foreground_ship.y + foreground_ship_draw_pos.y);

	// Setup Animation of purple guy on the ship:
	purple_guy.frames.push_back({ 808, 24, 48, 32 });
	purple_guy.frames.push_back({ 808, 72, 48, 32 });
	purple_guy.frames.push_back({ 808, 120, 48, 32 });
	purple_guy.speed = 0.06f;
	purple_guy_draw_pos = iPoint(
		136 - foreground_ship.x + foreground_ship_draw_pos.x,
		48 - foreground_ship.y + foreground_ship_draw_pos.y);

	// Setup Animation of brown guy on the ship:
	brown_guy.frames.push_back({ 760, 16, 40, 40 });
	brown_guy.frames.push_back({ 760, 64, 40, 40 });
	brown_guy.frames.push_back({ 760, 112, 40, 40 });
	brown_guy.speed = 0.06f;
	brown_guy_draw_pos = iPoint(
		96 - foreground_ship.x + foreground_ship_draw_pos.x,
		48 - foreground_ship.y + foreground_ship_draw_pos.y);

	// Setup Animation of two guys on the ship:
	two_guys.frames.push_back({ 552, 8, 64, 64 });
	two_guys.frames.push_back({ 552, 72, 64, 64 });
	two_guys.frames.push_back({ 552, 136, 64, 64 });
	two_guys.speed = 0.06f;
	two_guys_draw_pos = iPoint(
		136 - foreground_ship.x + foreground_ship_draw_pos.x,
		120 - foreground_ship.y + foreground_ship_draw_pos.y);
}

ModuleSceneKen::~ModuleSceneKen()
{}

// Load assets
bool ModuleSceneKen::Start()
{
	LOG("Loading ken scene");
	
	graphics = App->textures->Load("ken_stage.png");

	// DONE 7: Enable the player module
	App->player->Enable();

	// Set Position:
	App->player->position = iPoint(0, 0);

	// Clamp player movement for scene. If not specified, x_clamp_min = INT_MIN, x_clamp_max = INT_MAX
	App->player->x_clamp_min = 0;
	App->player->x_clamp_max = 812;
	App->player->y_default = 105;

	// DONE 0: trigger background music
	App->audio->PlayMusic("ken.ogg");

	return true;
}

// UnLoad assets
bool ModuleSceneKen::CleanUp()
{
	LOG("Unloading ken scene");

	App->textures->Unload(graphics);
	App->player->Disable();
	
	return true;
}

// Update: draw background
update_status ModuleSceneKen::Update()
{
	// DONE 10: Build an entire new scene "honda", you can find its
	// and music in the Game/ folder
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		LOG("FROM KEN TO HONDA");
		App->fade->FadeToBlack(App->scene_honda, App->scene_ken, 3.0f);
		// return UPDATE_CONTINUE;
	}


	// DONE 5: make sure the ship goes up and down
	int ship_offset = (int)(ship_position_anim.GetCurrent() * 5.1f);

	// Draw everything --------------------------------------
	
	// DONE 1: Tweak the parallax movement speed of the sea&sky + flag to your taste
	App->renderer->Blit(
		graphics, 
		background_draw_pos.x, 
		background_draw_pos.y, 
		&background, 
		0.6f
	);
	
	// sea and sky
	App->renderer->Blit(
		graphics, 
		flag_draw_pos.x, 
		flag_draw_pos.y, 
		&(flag.GetCurrentFrame()), 
		0.6f
	); // flag animation
	
	// DONE 3: Draw the ship. Be sure to tweak the speed.
	App->renderer->Blit(
		graphics, 
		foreground_ship_draw_pos.x, 
		foreground_ship_draw_pos.y + ship_offset,
		&foreground_ship, 
		0.8f
	);

	// DONE 6: Draw the girl. Make sure it follows the ship movement!
	App->renderer->Blit(
		graphics, 
		girl_draw_pos.x, 
		girl_draw_pos.y + ship_offset,
		&(girl.GetCurrentFrame()), 
		0.8f
	);

	// Draw the green guy on the red ship:
	App->renderer->Blit(
		graphics,
		green_guy_draw_pos.x,
		green_guy_draw_pos.y + ship_offset,
		&(green_guy.GetCurrentFrame()),
		0.8f
	);

	// Draw the blue guy on the red ship:
	App->renderer->Blit(
		graphics,
		blue_guy_draw_pos.x,
		blue_guy_draw_pos.y + ship_offset,
		&(blue_guy.GetCurrentFrame()),
		0.8f
	);

	// Draw the purple guy on the red ship:
	App->renderer->Blit(
		graphics,
		purple_guy_draw_pos.x,
		purple_guy_draw_pos.y + ship_offset,
		&(purple_guy.GetCurrentFrame()),
		0.8f
	);

	// Draw the brown guy on the red ship:
	App->renderer->Blit(
		graphics,
		brown_guy_draw_pos.x,
		brown_guy_draw_pos.y + ship_offset,
		&(brown_guy.GetCurrentFrame()),
		0.8f
	);

	// Draw two guys on the red ship:
	App->renderer->Blit(
		graphics,
		two_guys_draw_pos.x,
		two_guys_draw_pos.y + ship_offset,
		&(two_guys.GetCurrentFrame()),
		0.8f
	);

	App->renderer->Blit(graphics, 0, 170, &ground);

	// DONE 11: Make that pressing space triggers a switch to honda logic module
	// using FadeToBlack module

	return UPDATE_CONTINUE;
}