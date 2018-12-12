#pragma once

#include "Vector3D.hpp"

class Contact
{
public:
	Contact(Vector3D contactPoint, Vector3D contactNormal, float interpenetration);
	~Contact();

	// Getter 
	Vector3D getContactPoint();
	Vector3D getContactNormal();
	float getInterpenetration();

private:
	Vector3D contactPoint;
	Vector3D contactNormal;
	float interpenetration;
};