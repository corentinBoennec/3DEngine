#pragma once

#include "Primitive.hpp"

class Plane : public Primitive
{

private:
	Vector3D normal;
	float offset;

public:
	Plane(Vector3D normal, float offset);
	Plane();
	~Plane();

	// Getter and Setter
	Vector3D getNormal();
	float getOffset();
	void DrawPlane();
};