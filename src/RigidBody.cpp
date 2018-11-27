#include "RigidBody.hpp"
#include "Functions.hpp"

RigidBody::RigidBody(){}

RigidBody::RigidBody(float mass, float linearDamping, float angularDamping ,Vector3D position, Vector3D velocity, Vector3D angularVelocity, Vector3D gravity, Quaternion orientation, float radius)
{
	this->mass = mass;
	this->linearDamping = linearDamping;
	this->angularDamping = angularDamping;
	this->position = position;
	this->velocity = velocity;
	this->angularVelocity = angularVelocity;
	this->gravity = gravity;
	orientation.normalize();
	this->orientation = orientation;
	this->inverseMass = 1 / mass;
	this->radius = radius;
	calculDerivedData();
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

void RigidBody::setInertiaTensor(Matrix3x3 inertiaTensor)
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
	transformMatrix = orientation.quaternToMatrix3();
	this->inverseInertiaTensor = transformMatrix * (this->inverseInertiaTensor * transformMatrix.inverse());
}

void RigidBody::addForceAtPoint(Vector3D force, Vector3D point)
{
	point.worldToLocal(transformMatrix);
	//std::cout << point.getX() << " " << point.getZ() << " " << point.getZ() << " " << std::endl;
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
	this->orientation.modulateToPI();
	this->orientation.doRotation(angularVelocity);
}

void RigidBody::updateAllVelocity(float timeFrame)
{
	Vector3D accLineaire(inverseMass * this->forceAccum.getX(), inverseMass * this->forceAccum.getY(), inverseMass * this->forceAccum.getY());
	this->torqueAccum.localToWorld(inverseInertiaTensor);
	//std::cout << this->torqueAccum.getX() << "," << this->torqueAccum.getY() << "," << this->torqueAccum.getZ() << std::endl;
	Vector3D accAngulaire(this->torqueAccum.getX(), this->torqueAccum.getY(), this->torqueAccum.getZ());
	


	this->velocity = (this->velocity * (float)pow(this->linearDamping, (timeFrame / 1000)) + (accLineaire * (timeFrame / 1000)));
	this->angularVelocity = (this->angularVelocity * (float)pow(this->angularDamping, (timeFrame / 1000)) + (accAngulaire * (timeFrame / 1000)));
}



