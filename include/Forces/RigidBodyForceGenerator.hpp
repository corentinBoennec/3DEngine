#pragma once
#include "RigidBody.hpp"


class RigidBodyForceGenerator
{
public:
	virtual void updateForce(RigidBody* rigidbody, float time) = 0;
};