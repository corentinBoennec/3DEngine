#pragma once
#include "Vector3D.hpp"
class Plan
{
private:
	Vector3D position;
	Vector3D direction;

public:
	Plan(Vector3D pos, Vector3D dir);
	Plan();
	Vector3D getPosition();
	Vector3D getDirection();
};