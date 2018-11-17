#pragma once
#include <math.h>

#include "Vector3D.hpp"

class Particule 
{
private:
	float mass;
	float damping;
	Vector3D position;
	Vector3D velocity;
	Vector3D acceleration;
	Vector3D gravity;
	float inverseMass;
	float radius;
	
	Vector3D accumForce = Vector3D(0, 0, 0); //acummulateur des forces

public:
	Particule();
	~Particule();
	Particule(float mass, float damping, Vector3D position, Vector3D velocity, Vector3D acceleration, Vector3D gravity, float radius);

	// Accesseurs
	float getMass();
	void setMass(float mass);
	Vector3D getGravity();
	void setGravity(Vector3D gravity);
	float getDamping();
	void setDamping(float damping);
	Vector3D getVelocity();
	void setVelocity(Vector3D velocity);
	Vector3D getAcceleration();
	void setAcceleration(Vector3D acceleration);
	float getInverseMass();
	void setInverseMass(float inverseMass);
	Vector3D getPosition();
	void setPosition(Vector3D position);
	float getRadius();
	Vector3D getAccuForce();

	// Intégrateur
	void updatePosition(float timeFrame);
	void updateVelocity(float timeFrame);

	void PrintPosition(std::ofstream& file); // écrit la position dans un fichier
	float invertingMass(float mass);

	// Forces
	void addForce(const Vector3D &force);
	void clearAccumulator();



};