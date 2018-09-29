#include "DragGenerator.hpp"

DragGenerator::DragGenerator(float K1, float K2)
{
	this->K1 = K1;
	this->K2 = K2;
}

void DragGenerator::updateForce(Particule * particule, float time)
{
	Vector3D force = ((particule->getVelocity()) / (particule->getVelocity().norme()) *-1) * ((this->K1 * particule->getVelocity().norme()) + (this->K2 * pow(particule->getVelocity().norme(), 2)));
											/* - p point unitaire */							/* K1 fois norme de p point               +             K2 fois norme de p point au carré */
	particule->addForce(force);
}

