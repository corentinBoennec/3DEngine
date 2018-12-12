#include "Spring/SimpleSpring.hpp"

SimpleSpring::SimpleSpring(Particule* otherParticule, float k, float length0)
{
	this->otherParticule = *otherParticule;
	this->k = k;
	this->length0 = length0;
}

SimpleSpring::~SimpleSpring() {}

void SimpleSpring::updateForce(Particule* particule, float timeFrame)
{
	Vector3D delta = particule->getPosition() - this->otherParticule.getPosition();
	Vector3D F = (delta / delta.norme()) * -1 * this->k * (delta.norme() - this->length0);
	// std::cout << (delta.norme());
	particule->addForce(F * (timeFrame / 1000));
}