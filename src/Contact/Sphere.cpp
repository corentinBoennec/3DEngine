#include "Contact\Sphere.hpp"


Sphere::Sphere(Vector3D center, float radius)
{
	this->center = center;
	this->radius = radius;
}
Sphere::Sphere()
{
	this->center = Vector3D(0,0,0);
	this->radius = 0.0;
}
Sphere::~Sphere()
{

}
Vector3D Sphere::getCenter()
{
	return center;
}
float Sphere::getRadius()
{
	return radius;
}
void Sphere::setCenter(Vector3D center)
{
	this->center = center;
}
void Sphere::setRadius(float radius)
{
	this->radius = radius;
}