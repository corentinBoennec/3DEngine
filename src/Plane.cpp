#include "..\include\Plane.hpp"

#include "GL/freeglut.h"

Plane::Plane(Vector3D normal, float offset)
{
	this->normal = normal;
	this->offset = offset;
}

Plane::Plane() {}

Plane::~Plane() {}

Vector3D Plane::getNormal()
{
	return this->normal;
}

float Plane::getOffset()
{
	return this->offset;
}

void Plane::DrawPlane()
{
	//glScalef(0.5, 0.5, 0.5);
	glTranslatef(this->offset, this->normal.getY(), this->normal.getZ());

	glBegin(GL_QUADS);
	// Front face
	glVertex3f(this->offset, 100, 0);
	glVertex3f(this->offset, -100, 0);
	glVertex3f(this->offset, -100, 0);
	glVertex3f(this->offset, 100, 0);
	glEnd();
}