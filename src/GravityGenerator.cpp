#include "GravityGenerator.hpp"

<<<<<<< HEAD
GravityGenerator::~GravityGenerator(){}

=======
>>>>>>> 7d1e2ad34ecc19a9b2d26c89fdbb521659dcd761
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