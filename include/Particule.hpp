#pragma once
#include <math.h>
#include "Vector.hpp"

class Particule 
{
private:
	float timeFrame;
	Vector gravity;

	float mass;
	float damping;
	Vector position;
	Vector velocity;
	Vector acceleration;
	float inverseMass;

public:
	Particule();
	~Particule();

	// Accesseurs
	float getMass();
	void setMass(float mass);
	Vector getGravity();
	void setGravity(Vector gravity);
	float getDamping();
	void setDamping(float damping);
	Vector getVelocity();
	void setVelocity(Vector velocity);
	Vector getAcceleration();
	void setAcceleration(Vector acceleration);
	float getInverseMass();
	void setInverseMass(float inverseMass);

	void updatePosition();
	void updateVelocity();

};