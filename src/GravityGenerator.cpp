#include "GravityGenerator.hpp"

GravityGenerator::GravityGenerator(Vector3D gravity)
{
	this->gravity = gravity;
}

void GravityGenerator::updateForce(Particule * particule, float timeFrame)
{
	if (particule->getMass() != 0)
	{
		Vector3D F = gravity * particule->getMass() * (timeFrame / 1000);
		particule->addForce(F);
	}
}