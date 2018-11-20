#include "RigidBody.hpp"

RigidBody::RigidBody(){}

RigidBody::RigidBody(float mass, float linearDumping, Vector3D position, Vector3D velocity, Vector3D acceleration, Vector3D angularVelocity, Vector3D gravity, Quaternion orientation, Matrix3x3 inverseInertiaTensor)
{
	this->mass = mass;
	this->linearDamping = linearDamping;
	this->position = position;
	this->velocity = velocity;
	this->acceleration = acceleration;
	this->angularVelocity = angularVelocity;
	this->gravity = gravity;
	this->orientation = orientation;
	this->inverseInertiaTensor = inverseInertiaTensor.inverse();
	this->inverseMass = 1 / mass;
}

RigidBody::~RigidBody(){}

// Définition des accesseurs
float RigidBody::getMass()
{
	return mass;
}

void RigidBody::setMass(float mass)
{
	this->mass = mass;
}

Vector3D RigidBody::getGravity()
{
	return gravity;
}

void RigidBody::setGravity(Vector3D gravity)
{
	this->gravity = gravity;
}

float RigidBody::getDamping()
{
	return linearDamping;
}

void RigidBody::setDamping(float damping)
{
	this->linearDamping = damping;
}

Vector3D RigidBody::getVelocity()
{
	return velocity;
}

void RigidBody::setVelocity(Vector3D velocity)
{
	this->velocity = velocity;
}

Vector3D RigidBody::getAcceleration()
{
	return acceleration;
}

void RigidBody::setAcceleration(Vector3D acceleration)
{
	this->acceleration = acceleration;
}

float RigidBody::getInverseMass()
{
	return inverseMass;
}


Vector3D RigidBody::getPosition()
{
	return position;
}

void RigidBody::setPosition(Vector3D position)
{
	this->position = position;
}

Vector3D RigidBody::getAccuForce()
{
	return this->forceAccum;
}

void RigidBody::calculDerivedData()
{
	Matrix4x4 rotationMatrix = orientation.quaternToMatrix();
	transformMatrix = rotationMatrix.inverse();
}

void RigidBody::updateAngularVelocity(Vector3D angularVelocity, float timeframe)
{
	Quaternion w(0, angularVelocity.getX(), angularVelocity.getY(), angularVelocity.getZ());
	this->orientation = this->orientation + w * this->orientation * (timeframe / 2);
}

void RigidBody::addForceAtPoint(Vector3D force, Vector3D point)
{
	
	// convertir point en coord relatives au centre de masse
	this->forceAccum += force.orthonormalChange(transformMatrix.inverse());
	this->torqueAccum += point.orthonormalChange(transformMatrix.inverse()) ^ force.orthonormalChange(transformMatrix.inverse());
}

void RigidBody::addForceAtBodyPoint(Vector3D force, Vector3D point)
{
	// convertir point vers le repère du monde
	addForceAtPoint(force, point.orthonormalChange(transformMatrix));
}

