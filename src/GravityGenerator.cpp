#include "GravityGenerator.hpp"

GravityGenerator::GravityGenerator(Vector gravity)
{
	this->gravity = gravity;
}

void GravityGenerator::updateForce(Particule * particule, float time)
{
	if (particule->getMass() != 0)
	{
		Vector F = gravity * particule->getMass();
		particule->addFroce(F);
	}
}