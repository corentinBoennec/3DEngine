#include <Particule.hpp>

// Définition des accesseurs
float Particule::getMass()
{
	return mass;
}

void Particule::setMass(float mass)
{
	this->mass = mass;
}

float Particule::getGravity()
{
	return gravity;
}

void Particule::setGravity(float gravity)
{
	this->gravity = gravity;
}

float Particule::getDamping()
{
	return damping;
}

void Particule::setDamping(float damping)
{
	this->damping = damping;
}

float Particule::getVelocity()
{
	return velocity;
}

void Particule::setVelocity(float velocity)
{
	this->velocity = velocity;
}

float Particule::getAcceleration()
{
	return acceleration;
}

void Particule::setAcceleration(float acceleration)
{
	this->acceleration = acceleration;
}

float Particule::getInverseMass()
{
	return inverseMass;
}

void Particule::setInverseMass(float inverseMass)
{
	this->inverseMass = inverseMass;
}
