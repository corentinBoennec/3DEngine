#include <Particule.hpp>

// Constructeurs
Particule::Particule()
{

}

Particule::~Particule()
{

}

Particule::Particule(float mass, float damping, Vector position, Vector velocity, Vector acceleration, Vector gravity)
{
	this->damping = damping;
	this->mass = mass;
	this->inverseMass = utils::inverseMass(mass);
	this->position = position;
	this->velocity = velocity;
	this->acceleration = acceleration + gravity;
	this->gravity = gravity;
}

// D�finition des accesseurs
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

Vector Particule::getPosition()
{
	return position;
}

void Particule::setPosition(Vector position)
{
	this->position = position;
}


// Update

void Particule::updatePosition(float timeFrame)
{
	this->position = this->position + this->velocity * (timeFrame/1000);
	if (this->position.getZ() <= 0)
	{
		this->position.setZ(0);
	}
}

void Particule::updateVelocity(float timeFrame)
{
	this->velocity = (this->velocity * (float)pow(this->damping, (timeFrame/1000) ) + (this->acceleration * (timeFrame/1000)));
}