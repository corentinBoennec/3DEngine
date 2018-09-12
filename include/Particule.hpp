#pragma once
#include "GL/glut.h"
#include <math.h>

#include "Vector.hpp"

class Particule 
{
private:
	float mass;
	float damping;
	Vector position;
	Vector velocity;
	Vector acceleration;
	Vector gravity;
	float inverseMass;
	int id;

public:
	Particule();
	~Particule();
	Particule(float mass, float damping, Vector position, Vector velocity, Vector acceleration, Vector gravity, int id);

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
	Vector getPosition();
	void setPosition(Vector position);

	int getId();

	// Intégrateur
	void updatePosition(float timeFrame);
	void updateVelocity(float timeFrame);

	void PrintPosition(std::ofstream& file); // Écrit la position dans un fichier
	float invertingMass(float mass); 


};