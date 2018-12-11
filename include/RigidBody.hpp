#pragma once

#include "Matrix/Quaternion.hpp"
#include "Matrix/Matrix3x3.hpp"
#include "Vector3D.hpp"

class RigidBody
{
private:
	float mass;
	float inverseMass;
	float linearDamping;
	float angularDamping;

	Vector3D position;
	Vector3D velocity;
	Vector3D angularVelocity;
	Vector3D gravity;

	Quaternion orientation;
	Matrix3x3 transformMatrix;
	Matrix3x3 inverseInertiaTensor; // Utilisé par l'intégrateur

	float radius; // Uniquement des sphères pour le moment

	Vector3D forceAccum = Vector3D(0, 0, 0); //acummulateur des forces
	Vector3D torqueAccum = Vector3D(0, 0, 0); //acummulateur torque

	struct BoudingSphere
	{
		Vector3D center;
		float radius;
	};

	BoudingSphere sphere;

public:
	RigidBody();
	RigidBody(float mass, float linearDamping, float angularDamping, Vector3D position, Vector3D velocity, Vector3D angularVelocity, Vector3D gravity, Quaternion orientation, float radius);
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
	float getInverseMass();
	Vector3D getPosition();
	void setPosition(Vector3D position);
	Vector3D getAccuForce();
	Vector3D getAccuTorque();
	void setInertiaTensor(Matrix3x3 inertiatensor);
	float getRadiusBoudingSphere();
	Vector3D getCenterBoudingSphere();
	Quaternion getOrientation();
	bool operator==(const RigidBody r1);


	void calculDerivedData();
	

	// Fonction de l'intégrateur
	void updatePositionOrientation(float timeFrame);
	void updateAllVelocity(float timeFrame); 

	// Forces
	void addForceAtPoint(Vector3D force, Vector3D point); // Applique une force en un point précis de l'objet - repère du monde
	void addForceAtBodyPoint(Vector3D force, Vector3D point); // Même chose mais dans le repère de l'objet
	void clearAccumulator();
};