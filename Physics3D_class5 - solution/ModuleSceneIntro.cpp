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

	/*Cube* cube = new Cube(10, 10, 10);

	//cube->physbody->SetAsSensor(true);
	//cube->physbody->collision_listeners.add(this);
	cube->SetPos(500, 25, 20);
	primitives.PushBack(cube);
	cube->physbody = App->physics->AddBody(*cube, 0.0f);*/


	//CreateCircuit();

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


}

void ModuleSceneIntro::CreateCircuit()
{
}

	