#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleBackground::ModuleBackground()
{
	// ground
	ground.x = 8;
	ground.y = 391;
	ground.w = 896;
	ground.h = 72;

	// background / sky
	background.x = 72;
	background.y = 208;
	background.w = 768;
	background.h = 176;

	// ship
	ship.x = 8;
	ship.y = 24;
	ship.w = 521;
	ship.h = 181;

	// flag animation
	flag.PushBack({848, 208, 40, 40});
	flag.PushBack({848, 256, 40, 40});
	flag.PushBack({848, 304, 40, 40});
	flag.speed = 0.08f;

	// woman animation
	woman.PushBack({ 624, 16, 32, 56 });
	woman.PushBack({ 624, 80, 32, 56 });
	woman.PushBack({ 624, 144, 32, 56 });
	woman.speed = 0.08f;
}

ModuleBackground::~ModuleBackground()
{}

// Load assets
bool ModuleBackground::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("ken_stage.png");
	return ret;
}

// Update: draw background
update_status ModuleBackground::Update()
{
	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &background, 0.75f); // sea and sky
	App->render->Blit(graphics, 560, 8, &(flag.GetCurrentFrame()), 0.75f); // flag animation

	// TODO 2: Draw the ship from the sprite sheet with some parallax effect
	// TODO 3: Animate the girl on the ship (see the sprite sheet)

	App->render->Blit(graphics, 0, (0 + App->background->ychange), &ship, 0.75f);
	App->render->Blit(graphics, 192, (104 + App->background->ychange), &(woman.GetCurrentFrame()), 0.75f); // woman animation

	if (App->background->moving == true)
	{
		App->background->ychange -= 0.1;
	}
	else
	{
		App->background->ychange += 0.1;
	}

	if (App->background->ychange <= -4.8)
	{
		moving = false;
	}

	if (App->background->ychange >= 0)
	{
		moving = true;
	}

	App->render->Blit(graphics, 0, 170, &ground);

	return UPDATE_CONTINUE;
}