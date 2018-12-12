#pragma once

#include "RigidBody.hpp"
#include "Matrix/Matrix4x4.hpp"

class Primitive {

private:
	RigidBody* rigidbody;
	Matrix4x4 offset; // Transformation au centre de l'objet

public:
	Primitive();
	Primitive(RigidBody* rigidbody);
	~Primitive();

	//Setter and Getter
	RigidBody* getRigidBody();
	void setRigidBody(RigidBody rigidbody);
};