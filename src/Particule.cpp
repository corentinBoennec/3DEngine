#include "Particule.hpp"

// Constructeurs
Particule::Particule()
{

}

Particule::~Particule()
{

}


Particule::Particule(float mass, float damping, Vector3D position, Vector3D velocity, Vector3D acceleration, Vector3D gravity, float radius)
{
	this->damping = damping;
	this->mass = mass;
	this->inverseMass = invertingMass(mass);
	this->position = position;
	this->velocity = velocity;
	this->acceleration = acceleration + gravity;
	this->gravity = gravity;
	this->radius = radius;
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

Vector3D Particule::getGravity()
{
	return gravity;
}

void Particule::setGravity(Vector3D gravity)
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

Vector3D Particule::getVelocity()
{
	return velocity;
}

void Particule::setVelocity(Vector3D velocity)
{
	this->velocity = velocity;
}

Vector3D Particule::getAcceleration()
{
	return acceleration;
}

void Particule::setAcceleration(Vector3D acceleration)
{
	this->acceleration = acceleration;
}

float Particule::getInverseMass()
{
	return inverseMass;
}

float Particule::getRadius()
{
	return radius;
}

void Particule::setInverseMass(float inverseMass)
{
	this->inverseMass = inverseMass;
}

Vector3D Particule::getPosition()
{
	return position;
}

void Particule::setPosition(Vector3D position)
{
	this->position = position;
}


// Fonctions de l'intégrateur
void Particule::updatePosition(float timeFrame)
{
	this->position = this->position + this->velocity * (timeFrame/1000);
	if (this->position.getZ() <= this->radius)
	{
		this->position.setZ(this->radius);
	}
}

void Particule::updateVelocity(float timeFrame)
{
	this->velocity = (this->velocity * (float)pow(this->damping, (timeFrame/1000) ) + (this->acceleration * (timeFrame/1000)));
}


void Particule::PrintPosition(std::ofstream& file)
{
	file << "Particule "  << "= (" << std::to_string(this->getPosition().getX()) << ", " << std::to_string(this->getPosition().getY()) << ", " << std::to_string(this->getPosition().getZ()) << ")" << std::endl;
}


float Particule::invertingMass(float mass)
{
	return (float)1 / mass;
}

// Forces
void Particule::addForce(const Vector3D &force)
{
	this->accumForce += force;
}
void Particule::clearAccumulator()
{
	this->accumForce = Vector3D(0, 0, 0);
}