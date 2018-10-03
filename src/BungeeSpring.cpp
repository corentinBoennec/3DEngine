#include "BungeeSpring.hpp"

BungeeSpring::BungeeSpring(Particule otherParticule, float k, float length0)
{
	this->otherParticule = otherParticule;
	this->k = k;
	this->length0 = length0;
}

BungeeSpring::~BungeeSpring(){}

void BungeeSpring::updateForce(Particule particule)
{
	if (particule.getPosition().distance(otherParticule.getPosition()) < this->length0)
		exit(EXIT_FAILURE);
	else
	{
		Vector3D delta = particule.getPosition() - this->otherParticule.getPosition();
		Vector3D F = (delta / delta.norme()) * -1 * this->k * (delta.norme() - this->length0);
		particule.addForce(F);
	}
}
