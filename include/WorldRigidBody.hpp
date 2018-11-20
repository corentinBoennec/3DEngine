#pragma once

#include "RigidBody.hpp"

#include <vector>

class WorldRigidBody
{
private:
	std::vector<RigidBody*> rigidbody;
public:

	WorldRigidBody();
	std::vector<RigidBody*> getRigidBody();
	void addRigidBody(RigidBody * rigidbody);
};