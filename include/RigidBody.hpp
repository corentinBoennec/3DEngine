#pragma once

#include "Matrix/Quaternion.hpp"
#include "Vector3D.hpp"

class RigidBody
{
private:
	float mass;
	float inverseMass;
	float linearDamping;
	Vector3D position;
	Vector3D velocity;
	Vector3D acceleration;
	Vector3D angularVelocity;
	Vector3D gravity;
	Quaternion orientation;
	Matrix4x4 transformMatrix;
	Matrix3x3 inverseInertiaTensor; // Utilisé par l'intégrateur

	Vector3D forceAccum = Vector3D(0, 0, 0); //acummulateur des forces
	Vector3D torqueAccum = Vector3D(0, 0, 0); //acummulateur torque

public:
	RigidBody();
	RigidBody(float mass, float linearDumping, Vector3D position, Vector3D velocity, Vector3D acceleration, Vector3D angularVelocity, Vector3D gravity, Quaternion orientation, Matrix3x3 inverseInertiaTensor);
	~RigidBody();

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
	Vector3D getPosition();
	void setPosition(Vector3D position);
	Vector3D getAccuForce();


	void calculDerivedData();
	void updateAngularVelocity(Vector3D angularVelocity, float timeframe);
	void addForceAtPoint(Vector3D force, Vector3D point); // Applique une force en un point précis de l'objet - repère du monde
	void addForceAtBodyPoint(Vector3D force, Vector3D point); // Même chose mais dans le repère de l'objet

};