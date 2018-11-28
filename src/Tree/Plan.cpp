#include "Tree\Plan.hpp"

Plan::Plan(Vector3D pos, Vector3D dir)
{
	this->position = pos;
	this->direction = dir;
}
Plan::Plan()
{
	this->direction = Vector3D(0, 0, 0);
	this->position = Vector3D(0, 0, 0);
}
Vector3D Plan::getPosition()
{
	return position;
}
Vector3D Plan::getDirection()
{
	return direction;
}