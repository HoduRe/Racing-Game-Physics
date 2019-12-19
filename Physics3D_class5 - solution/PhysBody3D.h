#ifndef __PhysBody3D_H__
#define __PhysBody3D_H__

#include "p2List.h"
#include "p2Point.h"
#include "glmath.h"

class btRigidBody;
class Module;
class Primitive;

// =================================================
struct PhysBody3D
{
	friend class ModulePhysics3D;
public:
	PhysBody3D(btRigidBody* body);
	~PhysBody3D();

	void Push(float x, float y, float z);
	void GetTransform(float* matrix) const;
	void SetTransform(const float* matrix) const;
	void SetPos(float x, float y, float z);
	vec3 GetPos() const;
	void SetAsSensor(bool is_sensor);


private:
	btRigidBody* body = nullptr;
	
	
	

public:
	Primitive* parent = nullptr;
	p2List<Module*> collision_listeners;
	bool is_sensor;
	bool sensor_on = false;

};

#endif // __PhysBody3D_H__