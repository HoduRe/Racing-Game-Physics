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
		body1->parent->color = Purple;
		App->player->checkpoints++;
		App->player->last_checkpoint_pos = body1->GetPos();
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
	cube = new Cube(100, 10, 20);
	cube->SetPos(550, 45, -350);	// Left hallway
	cube->physbody = App->physics->AddBody(*cube, 0.0f);
	primitives.PushBack(cube);
	cube = new Cube(20, 20, 200);
	cube->SetPos(0, 45, -250);	// Ramp
	cube->SetRotation(-20, (0, 0, 1));
	cube->physbody = App->physics->AddBody(*cube, 0.0f);
	primitives.PushBack(cube);
	cube = new Cube(30, 10, 30);
	cube->SetPos(-10, 70, -110);	// Flying platform
	cube->SetRotation(-20, (0, 0, 0.707));
	cube->physbody = App->physics->AddBody(*cube, 0.0f);
	primitives.PushBack(cube);
	cube = new Cube(30, 50, 30);
	cube->SetPos(-250, 75, -200);	// Higher box hideout wall
	cube->physbody = App->physics->AddBody(*cube, 0.0f);
	primitives.PushBack(cube);
	cube = new Cube(30, 50, 30);
	cube->SetPos(-250, 75, -240);	// Lower box hideout wall
	cube->physbody = App->physics->AddBody(*cube, 0.0f);
	primitives.PushBack(cube);
	cube = new Cube(30, 10, 10);
	cube->SetPos(-250, 95, -220);	// Box hideout arch
	cube->physbody = App->physics->AddBody(*cube, 0.0f);
	primitives.PushBack(cube);
	cube = new Cube(5, 10, 10);
	cube->color.r = 255;
	cube->color.b = 0;
	cube->color.g = 0;
	cube->SetPos(-237.5, 55, -220);	// Bottom left constraint box
	cube->physbody = App->physics->AddBody(*cube, 0.1f);
	primitives.PushBack(cube);
	cube = new Cube(5, 10, 10);
	cube->color.r = 255;
	cube->color.b = 0;
	cube->color.g = 0;
	cube->SetPos(-237.5, 65, -220);	// Upper left constraint box
	cube->physbody = App->physics->AddBody(*cube, 0.1f);
	primitives.PushBack(cube);
	cube = new Cube(5, 10, 10);
	cube->color.r = 255;
	cube->color.b = 0;
	cube->color.g = 0;
	cube->SetPos(-262.5, 55, -220);	// Bottom right constraint box
	cube->physbody = App->physics->AddBody(*cube, 0.1f);
	primitives.PushBack(cube);
	cube = new Cube(5, 10, 10);
	cube->color.r = 255;
	cube->color.b = 0;
	cube->color.g = 0;
	cube->SetPos(-262.5, 65, -220);	// Upper right constraint box
	cube->physbody = App->physics->AddBody(*cube, 0.1f);
	primitives.PushBack(cube);
	cube = new Cube(200, 20, 100);
	cube->SetPos(200, 45, -350);	// Left ramp
	cube->SetRotation(-20, (0, 0, 1));
	cube->physbody = App->physics->AddBody(*cube, 0.0f);
	primitives.PushBack(cube);
	cube = new Cube(200, 20, 100);
	cube->SetPos(-50, 45, -350);	// Right ramp
	cube->SetRotation(20, (0, 0, 1));
	cube->physbody = App->physics->AddBody(*cube, 0.0f);
	primitives.PushBack(cube);
	cube = new Cube(10, 10, 10);
	cube->SetPos(350, 55, 200);	// Tower box 1
	cube->color.r = 0;
	cube->color.b = 0;
	cube->color.g = 255;
	cube->physbody = App->physics->AddBody(*cube, 0.01f);
	primitives.PushBack(cube);
	greentower_constraint.PushBack(cube);
	cube = new Cube(10, 10, 10);
	cube->SetPos(350, 65, 200);	// Tower box 2
	cube->color.r = 0;
	cube->color.b = 0;
	cube->color.g = 255;
	cube->physbody = App->physics->AddBody(*cube, 0.01f);
	primitives.PushBack(cube);
	greentower_constraint.PushBack(cube);
	cube = new Cube(10, 10, 10);
	cube->SetPos(350, 75, 200);	// Tower box 3
	cube->color.r = 0;
	cube->color.b = 0;
	cube->color.g = 255;
	cube->physbody = App->physics->AddBody(*cube, 0.01f);
	primitives.PushBack(cube);
	greentower_constraint.PushBack(cube);
	cube = new Cube(10, 10, 10);
	cube->SetPos(350, 85, 200);	// Tower box 4
	cube->color.r = 0;
	cube->color.b = 0;
	cube->color.g = 255;
	cube->physbody = App->physics->AddBody(*cube, 0.01f);
	primitives.PushBack(cube);
	greentower_constraint.PushBack(cube);
	cube = new Cube(10, 10, 10);
	cube->SetPos(350, 95, 200);	// Tower box 5
	cube->color.r = 0;
	cube->color.b = 0;
	cube->color.g = 255;
	cube->physbody = App->physics->AddBody(*cube, 0.01f);
	primitives.PushBack(cube);
	greentower_constraint.PushBack(cube);
	cube->SetPos(350, 105, 200);	// Tower box 6
	cube->color.r = 0;
	cube->color.b = 0;
	cube->color.g = 255;
	cube->physbody = App->physics->AddBody(*cube, 0.01f);
	primitives.PushBack(cube);
	greentower_constraint.PushBack(cube);
	cube = new Cube(20, 70, 20);
	cube->SetPos(-300, 85, 200);	// Laberynth 1
	cube->physbody = App->physics->AddBody(*cube, 0.0f);
	primitives.PushBack(cube);
	cube = new Cube(20, 70, 20);
	cube->SetPos(-280, 85, 220);	// Laberynth 2
	cube->physbody = App->physics->AddBody(*cube, 0.0f);
	primitives.PushBack(cube);
	cube = new Cube(20, 70, 20);
	cube->SetPos(-310, 85, 280);	// Laberynth 3
	cube->physbody = App->physics->AddBody(*cube, 0.0f);
	primitives.PushBack(cube);
	cube = new Cube(20, 70, 20);
	cube->SetPos(-350, 85, 180);	// Laberynth 4
	cube->physbody = App->physics->AddBody(*cube, 0.0f);
	primitives.PushBack(cube);
	cube = new Cube(20, 70, 20);
	cube->SetPos(-400, 85, 300);	// Laberynth 5
	cube->physbody = App->physics->AddBody(*cube, 0.0f);
	primitives.PushBack(cube);
	cube = new Cube(20, 70, 20);
	cube->SetPos(-380, 85, 250);	// Laberynth 6
	cube->physbody = App->physics->AddBody(*cube, 0.0f);
	primitives.PushBack(cube);




	float size = 10;

	for (int i = 0; i < greentower_constraint.Count(); i++)
	{
		if (i > 0)
		{
			Primitive* n1 = *greentower_constraint.At(i);
			Primitive* n2 = *greentower_constraint.At(i - 1);

			App->physics->AddConstraintP2P(*n1->physbody, *n2->physbody, { 0,size,0 }, { 0,size+10,0 });
			size += 10;

		}
	}

	// Chekpoints
	Cylinder* cylinder = new Cylinder(3.0f, 1.0f);
	cylinder->SetPos(0, 54, 50);	// Front checkpoint
	cylinder->color.r = 0;
	cylinder->color.b = 255;
	cylinder->color.g = 0;
	cylinder->physbody = App->physics->AddBody(*cylinder, 0.0f);
	primitives.PushBack(cylinder);
	cylinder->physbody->SetAsSensor(true);
	cylinder->physbody->collision_listeners.add(this);
	cylinder->physbody->parent = cylinder;
	sensors.PushBack(cylinder->physbody);
	cylinder = new Cylinder(3.0f, 1.0f);
	cylinder->SetPos(-295, 54, 220);	// Laberynth checkpoint
	cylinder->color.r = 0;
	cylinder->color.b = 255;
	cylinder->color.g = 0;
	cylinder->physbody = App->physics->AddBody(*cylinder, 0.0f);
	primitives.PushBack(cylinder);
	cylinder->physbody->SetAsSensor(true);
	cylinder->physbody->collision_listeners.add(this);
	cylinder->physbody->parent = cylinder;
	sensors.PushBack(cylinder->physbody);
	cylinder = new Cylinder(3.0f, 1.0f);
	cylinder->SetPos(-10, 79, -110);	// Flying platform checkpoint
	cylinder->color.r = 0;
	cylinder->color.b = 255;
	cylinder->color.g = 0;
	cylinder->physbody = App->physics->AddBody(*cylinder, 0.0f);
	primitives.PushBack(cylinder);
	cylinder->physbody->SetAsSensor(true);
	cylinder->physbody->collision_listeners.add(this);
	cylinder->physbody->parent = cylinder;
	sensors.PushBack(cylinder->physbody);
	cylinder = new Cylinder(6.0f, 1.0f);
	cylinder->SetPos(75, 84, -350);	// Ramps checkpoint
	cylinder->color.r = 0;
	cylinder->color.b = 255;
	cylinder->color.g = 0;
	cylinder->physbody = App->physics->AddBody(*cylinder, 0.0f);
	primitives.PushBack(cylinder);
	cylinder->physbody->SetAsSensor(true);
	cylinder->physbody->collision_listeners.add(this);
	cylinder->physbody->parent = cylinder;
	sensors.PushBack(cylinder->physbody);
	cylinder = new Cylinder(3.0f, 1.0f);
	cylinder->SetPos(-250, 54, -220);	// Box hideout checkpoint
	cylinder->color.r = 0;
	cylinder->color.b = 255;
	cylinder->color.g = 0;
	cylinder->physbody = App->physics->AddBody(*cylinder, 0.0f);
	primitives.PushBack(cylinder);
	cylinder->physbody->SetAsSensor(true);
	cylinder->physbody->collision_listeners.add(this);
	cylinder->physbody->parent = cylinder;
	sensors.PushBack(cylinder->physbody);
	cylinder = new Cylinder(3.0f, 1.0f);
	cylinder->SetPos(650, 54, -350);	// Outskirts checkpoint
	cylinder->color.r = 0;
	cylinder->color.b = 255;
	cylinder->color.g = 0;
	cylinder->physbody = App->physics->AddBody(*cylinder, 0.0f);
	primitives.PushBack(cylinder);
	cylinder->physbody->SetAsSensor(true);
	cylinder->physbody->collision_listeners.add(this);
	cylinder->physbody->parent = cylinder;
	sensors.PushBack(cylinder->physbody);

}
