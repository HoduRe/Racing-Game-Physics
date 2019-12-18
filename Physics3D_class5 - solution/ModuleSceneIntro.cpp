#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	

	CreateCircuit();

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	for(int i = 0; i < primitives.Count() ; i++)
	{
		primitives[i]->physbody = nullptr;
		delete primitives[i];
	}

	primitives.Clear();

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;

	for (int i = 0; i < primitives.Count(); i++)
	{
		if (primitives[i]->physbody != nullptr)
		{
			primitives[i]->Update();
			primitives[i]->Render();
		}
	}
	p.Render();

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{

	if (body1->is_sensor && !body1->sensor_on)
	{
		body1->sensor_on = true;
		body1->parent->color = Blue;
		App->player->checkpoints++;
	}	
}

void ModuleSceneIntro::CreateCircuit()
{
	Cube* cube = new Cube(1000, 10, 1000);
	cube->SetPos(0, 45, 0);	// Ground
	cube->physbody = App->physics->AddBody(*cube, 0.0f);
	primitives.PushBack(cube);
	cube = new Cube(50, 50, 800);
	cube->SetPos(525, 75, 100);	// high left border
	cube->physbody = App->physics->AddBody(*cube, 0.0f);
	primitives.PushBack(cube);
	cube = new Cube(1000, 50, 50);
	cube->SetPos(0, 75, 525);	// upper border
	cube->physbody = App->physics->AddBody(*cube, 0.0f);
	primitives.PushBack(cube);
	cube = new Cube(50, 50, 1000);
	cube->SetPos(-525, 75, 0);	// right border
	cube->physbody = App->physics->AddBody(*cube, 0.0f);
	primitives.PushBack(cube);
	cube = new Cube(1000, 50, 50);
	cube->SetPos(0, 75, -525);	// lower border
	cube->physbody = App->physics->AddBody(*cube, 0.0f);
	primitives.PushBack(cube);
	cube = new Cube(100, 50, 50);
	cube->SetPos(550, 75, -275);	// High left hallway
	cube->physbody = App->physics->AddBody(*cube, 0.0f);
	primitives.PushBack(cube);
	cube = new Cube(100, 50, 50);
	cube->SetPos(550, 75, -425);	// Low left hallway
	cube->physbody = App->physics->AddBody(*cube, 0.0f);
	primitives.PushBack(cube);
	cube = new Cube(50, 50, 100);
	cube->SetPos(575, 75, -250);	// High right square wall
	cube->physbody = App->physics->AddBody(*cube, 0.0f);
	primitives.PushBack(cube);
	cube = new Cube(50, 50, 100);
	cube->SetPos(575, 75, -450);	// Low right square wall
	cube->physbody = App->physics->AddBody(*cube, 0.0f);
	primitives.PushBack(cube);
	cube = new Cube(100, 50, 50);
	cube->SetPos(650, 75, -175);	// High square wall
	cube->physbody = App->physics->AddBody(*cube, 0.0f);
	primitives.PushBack(cube);
	cube = new Cube(100, 50, 50);
	cube->SetPos(650, 75, -475);	// Low square wall
	cube->physbody = App->physics->AddBody(*cube, 0.0f);
	primitives.PushBack(cube);
	cube = new Cube(50, 50, 300);
	cube->SetPos(725, 75, -350);	// Left square wall
	cube->physbody = App->physics->AddBody(*cube, 0.0f);
	primitives.PushBack(cube);
	cube = new Cube(50, 50, 100);
	cube->SetPos(525, 75, -450);	// Left square wall
	cube->physbody = App->physics->AddBody(*cube, 0.0f);
	primitives.PushBack(cube);
	cube = new Cube(100, 10, 300);
	cube->SetPos(650, 45, -350);	// Ground
	cube->physbody = App->physics->AddBody(*cube, 0.0f);
	primitives.PushBack(cube);
}
	