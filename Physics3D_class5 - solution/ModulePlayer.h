#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"


enum class player_state
{
	ST_NONE,
	ST_READY,
	ST_GO,
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

	//Restart the game
	void Restart();

public:

	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;
	player_state state;
	Timer chrono;
	uint start_fx;

	uint checkpoints;
	vec3 startingpos;
	float rot;
};