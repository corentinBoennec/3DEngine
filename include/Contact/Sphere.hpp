#include "Vector3D.hpp"

class Sphere {
private :
	Vector3D center;
	float radius;

public:
	Sphere(Vector3D center, float radius);
	Sphere();
	~Sphere();
	Vector3D getCenter();
	float getRadius();
	void setCenter(Vector3D center);
	void setRadius(float radius);
};