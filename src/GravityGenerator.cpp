#include "GravityGenerator.hpp"

GravityGenerator::~GravityGenerator(){}

GravityGenerator::GravityGenerator(Vector3D gravity)
{
	this->gravity = gravity;
}

void GravityGenerator::updateForce(Particule * particule)
{
	if (particule->getMass() != 0)
	{
		Vector3D F = gravity * particule->getMass();
		particule->addForce(F);
	}
}