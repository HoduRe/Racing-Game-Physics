#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"


ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;
	checkpoints = 0;
	startingpos = { 0, 50, 0 };
	num_checkpoints = 4;
	last_checkpoint_pos = { 0, 0, 0 };
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	

	VehicleInfo car;

	// Car properties ----------------------------------------

		//All chassis parts
	car.num_chasis_parts = 8;
	car.chasis_parts = new Chassis[car.num_chasis_parts];

			//MAIN BODY------------------------------------
			car.chasis_parts[0].chassis_size.Set(3.f, 1.5f, 4.f);
			car.chasis_parts[0].chassis_offset.Set(0.f, 1.6f, 0.f);
			car.chasis_parts[0].chassis_color = Black;

			//FRONT MUDWARD--------------------------------
			car.chasis_parts[1].chassis_size.Set(3.f, 0.5f, 1.5f);
			car.chasis_parts[1].chassis_offset.Set(0, 1.1f, 2.75f);
			car.chasis_parts[1].chassis_color = Black;

			//BACK MUDWARD---------------------------------
			car.chasis_parts[2].chassis_size.Set(3.f, 0.5f, 1.f);
			car.chasis_parts[2].chassis_offset.Set(0.f, 1.1f, -2.5f);
			car.chasis_parts[2].chassis_color = Black;

			//SPOILER--------------------------------------
			car.chasis_parts[3].chassis_size.Set(0.1f, 1.4f, 0.2f);
			car.chasis_parts[3].chassis_offset.Set(-0.5f, 1.7f, -2.75f);
			car.chasis_parts[3].chassis_color = Green;

			car.chasis_parts[4].chassis_size.Set(0.1f, 1.4f, 0.2f);
			car.chasis_parts[4].chassis_offset.Set(0.5, 1.7f, -2.75f);
			car.chasis_parts[4].chassis_color = Green;

			car.chasis_parts[5].chassis_size.Set(2.5f, 0.2f, 0.4f);
			car.chasis_parts[5].chassis_offset.Set(0.f, 2.5f, -2.75f);
			car.chasis_parts[5].chassis_color = Green;

			car.chasis_parts[6].chassis_size.Set(0.1f, 0.6f, 0.4f);
			car.chasis_parts[6].chassis_offset.Set(-1.3f, 2.5f, -2.75f);
			car.chasis_parts[6].chassis_color = Green;
			
			car.chasis_parts[7].chassis_size.Set(0.1f, 0.6f, 0.4f);
			car.chasis_parts[7].chassis_offset.Set(1.3f, 2.5f, -2.75f);
			car.chasis_parts[7].chassis_color = Green;

			
	
	car.mass = 500.0f;
	car.suspensionStiffness = 15.88f;
	car.suspensionCompression = 0.83f;
	car.suspensionDamping = 0.88f;
	car.maxSuspensionTravelCm = 1000.0f;
	car.frictionSlip = 50.5;
	car.maxSuspensionForce = 6000.0f;

	// Wheel properties ---------------------------------------
	float connection_height = 1.2f;
	float wheel_radius = 0.6f;
	float wheel_width = 0.5f;
	float suspensionRestLength = 1.2f;

	// Don't change anything below this line ------------------

	float half_width = car.chasis_parts[0].chassis_size.x*0.5f;
	float half_length = car.chasis_parts[0].chassis_size.z*0.5f;
	
	vec3 direction(0,-1,0);
	vec3 axis(-1,0,0);
	
	car.num_wheels = 4;
	car.wheels = new Wheel[car.num_wheels];

	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(half_width - 0.3f * wheel_width, connection_height, half_length - (wheel_radius));
	car.wheels[0].direction = direction;
	car.wheels[0].axis = axis;
	car.wheels[0].suspensionRestLength = suspensionRestLength;
	car.wheels[0].radius = wheel_radius;
	car.wheels[0].width = wheel_width;
	car.wheels[0].front = true;
	car.wheels[0].drive = true;
	car.wheels[0].brake = false;
	car.wheels[0].steering = true;

	// FRONT-RIGHT ------------------------
	car.wheels[1].connection.Set(-half_width + 0.3f * wheel_width, connection_height, half_length - (wheel_radius));
	car.wheels[1].direction = direction;
	car.wheels[1].axis = axis;
	car.wheels[1].suspensionRestLength = suspensionRestLength;
	car.wheels[1].radius = wheel_radius;
	car.wheels[1].width = wheel_width;
	car.wheels[1].front = true;
	car.wheels[1].drive = true;
	car.wheels[1].brake = false;
	car.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	car.wheels[2].connection.Set(half_width - 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[2].direction = direction;
	car.wheels[2].axis = axis;
	car.wheels[2].suspensionRestLength = suspensionRestLength;
	car.wheels[2].radius = wheel_radius;
	car.wheels[2].width = wheel_width;
	car.wheels[2].front = false;
	car.wheels[2].drive = false;
	car.wheels[2].brake = true;
	car.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	car.wheels[3].connection.Set(-half_width + 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[3].direction = direction;
	car.wheels[3].axis = axis;
	car.wheels[3].suspensionRestLength = suspensionRestLength;
	car.wheels[3].radius = wheel_radius;
	car.wheels[3].width = wheel_width;
	car.wheels[3].front = false;
	car.wheels[3].drive = false;
	car.wheels[3].brake = true;
	car.wheels[3].steering = false;

	vehicle = App->physics->AddVehicle(car);
	vehicle->SetPos(startingpos.x, startingpos.y, startingpos.z);

	state = player_state::ST_READY;
	start_fx = App->audio->LoadFx("assets/start.wav");
	chrono.Start();
	

	

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	

	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	turn = acceleration = brake = 0.0f;
	float velocity = vehicle->GetKmh();
	
	UpdateState();

	switch (state)
	{

	case player_state::ST_READY:

		App->audio->PlayFx(start_fx);	

		break;

	case player_state::ST_GO:

		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		{
			if (velocity < 0)
				brake = BRAKE_POWER;
			else if (velocity < 130.0f)
				acceleration = MAX_ACCELERATION;
			else
				acceleration = 0;
		}		

		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		{
			if (turn < TURN_DEGREES)
				turn += TURN_DEGREES;
		}
		
		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		{
			if (turn > -TURN_DEGREES)
				turn -= TURN_DEGREES;
		}

		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		{
			if (velocity > 0)
				brake = BRAKE_POWER;
			else
				acceleration = -MAX_ACCELERATION / 2;
		}

		break;

	case player_state::ST_FINISH:

				

		break;
		
	}
	
	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
	{
		Restart();
	}
	if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN)
	{
		checkpoints++;
	}
	if (App->input->GetKey(SDL_SCANCODE_BACKSPACE) == KEY_DOWN)
	{
		GoLastCheckpoint();
	}

	vehicle->ApplyEngineForce(acceleration);
	vehicle->Turn(turn);
	vehicle->Brake(brake);

	vehicle->Render();

	TitleInfo();

	return UPDATE_CONTINUE;
}

void ModulePlayer::UpdateState()
{	
	switch (state)
	{
		case player_state::ST_READY:
			if (chrono.Read() >= 3000)
			{
				state = player_state::ST_GO;
				chrono.Stop();
				chrono.Start();
			}
			break;
		case player_state::ST_GO:
			if (checkpoints == num_checkpoints)
				state = player_state::ST_FINISH;
				chrono.Stop();
				finish_timer.Start();
			break;
		case player_state::ST_FINISH:						

			if (finish_timer.Read() > 5000)
			{
				finish_timer.Stop();
				Restart();
			}
			
			break;
	}	
}

void ModulePlayer::TitleInfo()
{
	uint current_time = chrono.Read();

	uint miliseconds = current_time % 1000;
	uint seconds = (current_time / 1000) % 60;
	uint minutes = (current_time / 1000) / 60;

	char title[95];

	switch (state)
	{
		case player_state::ST_READY:
			
			sprintf_s(title, " Speed: 0 Km/h | Time: 00:00:00 | Checkpoints: 0/%u", num_checkpoints);
			App->window->SetTitle(title);

		break;

		case player_state::ST_GO:
			
			sprintf_s(title, " Speed: %.1f Km/h | Time: %02d:%02d:%02d | Checkpoints: %u/%u", vehicle->GetKmh(), minutes, seconds, miliseconds, checkpoints, num_checkpoints);
			App->window->SetTitle(title);
		
		break;

		case player_state::ST_FINISH:			
			
			if (best_time > current_time)
			{
				best_time = current_time;
			}
			uint best_mil = best_time % 1000;
			uint best_sec = (best_time / 1000) % 60;
			uint best_min = (best_time / 1000) / 60;

			sprintf_s(title, " Congratulations, you completed the track in %02d:%02d:%02d, your best time is %02d:%02d:%02d ", minutes, seconds, miliseconds, best_min, best_sec, best_mil);
			App->window->SetTitle(title);

			break;

	}
	
}

void ModulePlayer::GoLastCheckpoint()
{

	vehicle->vehicle_body->setAngularVelocity({ 0,0,0 });
	vehicle->vehicle_body->setLinearVelocity({ 0,0,0 });

	if (checkpoints == 0)
		vehicle->SetPos(startingpos.x, startingpos.y, startingpos.z);
	else
		vehicle->SetPos(last_checkpoint_pos.x, last_checkpoint_pos.y, last_checkpoint_pos.z);
}

void ModulePlayer::Restart()
{	


	mat4x4 rot;
	btTransform transform;
	transform.setIdentity();
	transform.setFromOpenGLMatrix(&rot);

	vehicle->SetTransform(&rot);
	vehicle->vehicle_body->setAngularVelocity({ 0,0,0 });
	vehicle->vehicle_body->setLinearVelocity({ 0,0,0 });

	state = player_state::ST_READY;
	checkpoints = 0u;
	chrono.Stop();
	chrono.Start();
	vehicle->SetPos(startingpos.x, startingpos.y, startingpos.z);

	for (int i = 0;  i < App->scene_intro->sensors.Count();  i++)
	{
		App->scene_intro->sensors[i]->sensor_on = false;
		App->scene_intro->sensors[i]->parent->color = White;
	}
}



