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

	Cube* cube = new Cube(10, 10, 10);

	cube->SetPos(10, 5, 20);
	cube->physbody = App->physics->AddBody(*cube, 0.0f);
	primitives.PushBack(cube);
	cube->physbody->SetAsSensor(true);
	cube->physbody->collision_listeners.add(this);
	cube->physbody->parent = cube;
	sensors.PushBack(cube->physbody);



	Cube* cubee = new Cube(10, 10, 10);

	cubee->SetPos(30, 5, 20);
	cubee->physbody = App->physics->AddBody(*cubee, 0.0f);
	primitives.PushBack(cubee);
	cubee->physbody->SetAsSensor(true);
	cubee->physbody->collision_listeners.add(this);
	cubee->physbody->parent = cubee;
	sensors.PushBack(cubee->physbody);

	Cube* cubeee = new Cube(10, 10, 10);

	cubeee->SetPos(50, 5, 20);
	cubeee->physbody = App->physics->AddBody(*cubeee, 0.0f);
	primitives.PushBack(cubeee);
	cubeee->physbody->SetAsSensor(true);
	cubeee->physbody->collision_listeners.add(this);
	cubeee->physbody->parent = cubeee;
	sensors.PushBack(cubeee->physbody);

	Cube* cubeeee = new Cube(10, 10, 10);

	cubeeee->SetPos(-10, 5, 20);
	cubeeee->physbody = App->physics->AddBody(*cubeeee, 0.0f);
	primitives.PushBack(cubeeee);
	cubeeee->physbody->SetAsSensor(true);
	cubeeee->physbody->collision_listeners.add(this);
	cubeeee->physbody->parent = cubeeee;
	sensors.PushBack(cubeeee->physbody);
}
	