#include "WorldRigidBody.hpp"

WorldRigidBody::WorldRigidBody()
{

}

void WorldRigidBody::addRigidBody(RigidBody* rigidbody)
{
	this->rigidbody.push_back(rigidbody);
}

std::vector<RigidBody*> WorldRigidBody::getRigidBody()
{
	return rigidbody;
}