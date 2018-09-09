#include <Particule.hpp>

// Constructeurs
Particule::Particule()
{

}

Particule::~Particule()
{

}

// Définition des accesseurs
float Particule::getMass()
{
	return mass;
}

void Particule::setMass(float mass)
{
	this->mass = mass;
}

Vector Particule::getGravity()
{
	return gravity;
}

void Particule::setGravity(Vector gravity)
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

Vector Particule::getVelocity()
{
	return velocity;
}

void Particule::setVelocity(Vector velocity)
{
	this->velocity = velocity;
}

Vector Particule::getAcceleration()
{
	return acceleration;
}

void Particule::setAcceleration(Vector acceleration)
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


// Update

void Particule::updatePosition()
{
	position = position + velocity * timeFrame;
}

void Particule::updateVelocity()
{
	velocity = (velocity * (float)pow(damping, timeFrame) ) + (acceleration * timeFrame);
}