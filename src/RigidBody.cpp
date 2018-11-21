#include "RigidBody.hpp"
#include "Functions.cpp"

RigidBody::RigidBody(){}

RigidBody::RigidBody(float mass, float linearDumping, float angularDamping ,Vector3D position, Vector3D velocity, Vector3D acceleration, Vector3D angularVelocity, Vector3D angularAcceleration, Vector3D gravity, Quaternion orientation, float radius)
{
	this->mass = mass;
	this->linearDamping = linearDamping;
	this->angularDamping = angularDamping;
	this->position = position;
	this->velocity = velocity;
	this->acceleration = acceleration;
	this->angularVelocity = angularVelocity;
	this->angularAcceleration = angularAcceleration;
	this->gravity = gravity;
	this->orientation = orientation;
	this->inverseMass = 1 / mass;
	this->radius = radius;
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

Vector3D RigidBody::getAccuTorque()
{
	return this->torqueAccum;
}

void RigidBody::setInertiaTensor(Matrix3x3 &inertiaTensor)
{
	this->inverseInertiaTensor = inertiaTensor.inverse();
}

float RigidBody::getRadius()
{
	return this->radius;
}

Quaternion RigidBody::getOrientation()
{
	return this->orientation;
}

void RigidBody::calculDerivedData()
{
	Matrix4x4 rotationMatrix;
	rotationMatrix.quaternToMatrix4(orientation);
	this->transformMatrix = rotationMatrix.inverse();

	Matrix3x3 inertiaModifier;
	inertiaModifier.quaternToMatrix3(orientation);
	this->inverseInertiaTensor = inertiaModifier * this->inverseInertiaTensor * inertiaModifier.inverse();
}

void RigidBody::addForceAtPoint(Vector3D force, Vector3D point)
{
	point.worldToLocal(transformMatrix);
	this->forceAccum += force;
	this->torqueAccum += point ^ force;
}

void RigidBody::addForceAtBodyPoint(Vector3D force, Vector3D point)
{
	point.localToWorld(transformMatrix);
	addForceAtPoint(force, point);
}

void RigidBody::clearAccumulator()
{
	this->forceAccum = Vector3D(0, 0, 0);
	this->torqueAccum = Vector3D(0, 0, 0);
}

void RigidBody::updatePositionOrientation(float timeFrame)
{
	this->position = this->position + this->velocity * (timeFrame / 1000);
	if (this->position.getZ() <= this->radius)
	{
		this->position.setZ(this->radius);
	}

	this->orientation.normalize();
	this->orientation.doRotation(angularVelocity);
}

void RigidBody::updateAllVelocity(float timeFrame)
{
	this->velocity = (this->velocity * (float)pow(this->linearDamping, (timeFrame / 1000)) + (this->acceleration * (timeFrame / 1000)));
	this->velocity = this->velocity + ((this->forceAccum / this->mass) * timeFrame / 1000); // pour passer les forces de N en m/s 

	this->angularVelocity = (this->angularVelocity * (float)pow(this->angularDamping, (timeFrame / 1000)) + (this->angularAcceleration * (timeFrame / 1000)));
	this->angularVelocity = this->angularVelocity + ((this->torqueAccum / this->mass) * timeFrame / 1000); // pour passer les forces de N en m/s 
}



