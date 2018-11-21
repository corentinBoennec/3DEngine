#include "Forces/GravityGeneratorRigidBody.hpp"

GravityGeneratorRigidBody::GravityGeneratorRigidBody(Vector3D gravity)
{
	this->gravity = gravity;
}

void GravityGeneratorRigidBody::updateForce(RigidBody* rigidbody, float timeFrame)
{
	if (rigidbody->getMass() != 0)
	{
		Vector3D F = gravity * rigidbody->getMass() * (timeFrame / 1000);
		rigidbody->addForceAtPoint(F, rigidbody->getPosition()); // pas certain pour l'application via la position
	}
}