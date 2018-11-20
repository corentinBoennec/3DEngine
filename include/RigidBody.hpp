﻿#pragma once

#include "Matrix/Quaternion.hpp"
#include "Matrix\Matrix3x3.hpp"

class RigidBody
{
private:
	float mass;
	float inverseMass;
	float linearDamping;
	float radius; // Uniquement des sphères pour le moment
	Vector3D position;
	Vector3D velocity;
	Vector3D acceleration;
	Quaternion angularVelocity;
	Quaternion angularAcceleration;
	Vector3D gravity;
	Quaternion orientation;
	Matrix4x4 transformMatrix;
	Matrix3x3 inverseInertiaTensor; // Utilisé par l'intégrateur

	Vector3D forceAccum = Vector3D(0, 0, 0); //acummulateur des forces
	Vector3D torqueAccum = Vector3D(0, 0, 0); //acummulateur torque

public:
	RigidBody();
	RigidBody(float mass, float linearDumping, Vector3D position, Vector3D velocity, Vector3D acceleration, Quaternion angularVelocity, Quaternion angularAcceleration, Vector3D gravity, Quaternion orientation, float radius);
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
	void setInertiaTensor(Matrix3x3 &inertiatensor);
	float getRadius();
	Quaternion getOrientation();

	void calculDerivedData();
	

	// Fonction de l'intégrateur
	void updatePositionOrientation(float timeFrame);
	void updateAllVelocity(float timeFrame); 

	// Forces
	void addForceAtPoint(Vector3D force, Vector3D point); // Applique une force en un point précis de l'objet - repère du monde
	void addForceAtBodyPoint(Vector3D force, Vector3D point); // Même chose mais dans le repère de l'objet
	void clearAccumulator();
};