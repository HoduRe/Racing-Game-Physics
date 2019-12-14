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

	for (int i = 0; i < PRIMITIVE_LIST; i++) {
		primitives[i] = nullptr;
	}

	CreateCircuit();

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	for (int i = 0; i < PRIMITIVE_LIST; i++) {
		if (primitives[i] != nullptr) {
			primitives[i]->InnerRender();
		}
	}
	p.Render();

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

void ModuleSceneIntro::CreateCircuit() {
	Cube* cube = new Cube(15, 50, 800);
	primitives[0] = cube;
	primitives[0]->physbody = App->physics->AddBody(*cube, 0.0f);
	primitives[0]->physbody->SetPos(500, 25, 20);
	primitives[0]->SetPos(500, 25, 20);
	
}