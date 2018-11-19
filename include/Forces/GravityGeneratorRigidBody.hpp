#pragma once
#include "RigidBodyForceGenerator.hpp"

class GravityGeneratorRigidBody : public RigidBodyForceGenerator
{
private:
	Vector3D gravity;
public:
	GravityGeneratorRigidBody(Vector3D gravity);
	void updateForce(RigidBody* rigidbody, float timeframe);
};