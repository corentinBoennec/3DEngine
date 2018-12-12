#include "Contact/Contact.hpp"

Contact::Contact(Vector3D contactPoint, Vector3D contactNormal, float interpenetration)
{
	this->contactPoint = contactPoint;
	this->contactNormal = contactNormal;
	this->interpenetration = interpenetration;
}

Contact::~Contact(){}

Vector3D Contact::getContactPoint()
{
	return this->contactPoint;
}

Vector3D Contact::getContactNormal()
{
	return contactNormal;
}

float Contact::getInterpenetration()
{
	return this->interpenetration;
}
