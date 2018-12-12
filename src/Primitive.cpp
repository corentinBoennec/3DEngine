#include "..\include\Primitive.hpp"

Primitive::Primitive() {}

Primitive::Primitive(RigidBody * rigidbody)
{
	this->rigidbody = rigidbody;
}

Primitive::~Primitive() {}

//Setter and Getter
RigidBody* Primitive::getRigidBody()
{
	return this->rigidbody;
}

void Primitive::setRigidBody(RigidBody rigidbody)
{
	this->rigidbody = &rigidbody;
}