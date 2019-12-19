#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"



enum class player_state
{
	ST_NONE,
	ST_READY,
	ST_STEADY,
	ST_GO,
	ST_FINISH
};

struct PhysVehicle3D;

#define MAX_ACCELERATION 1000.0f
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 1500.0f

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	//Check if player can start or not.
	void UpdateState();


	//shows chrono, laps, etc. in title
	void TitleInfo();

	//Restores the player to the last checkpoint
	void GoLastCheckpoint();

	//Restart the game
	void Restart();

public:

	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;
	player_state state;
	Timer chrono;
	Timer finish_timer;

	uint start_fx;
	uint claxon_fx;

	uint checkpoints;
	uint num_checkpoints;
	vec3 startingpos;
	uint best_time;
	vec3 last_checkpoint_pos;
};