#pragma once

class Particule 
{
private:
	float mass;
	float gravity;
	float damping;
	float velocity;
	float acceleration;
	float inverseMass;

public:
	// Accesseurs
	float getMass();
	void setMass(float mass);
	float getGravity();
	void setGravity(float gravity);
	float getDamping();
	void setDamping(float damping);
	float getVelocity();
	void setVelocity(float velocity);
	float getAcceleration();
	void setAcceleration(float acceleration);
	float getInverseMass();
	void setInverseMass(float inverseMass);

};