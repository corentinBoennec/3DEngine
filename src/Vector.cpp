#include "Vector.hpp"


Vector::Vector(void)
{

}

Vector::Vector(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector::~Vector(void)
{

}

Vector Vector::operator+(Vector &vector)
{
	Vector result;

	result.x = this->x + vector.x;
	result.y = this->y + vector.y;
	result.z = this->z + vector.z;

	return result;
}

float Vector::operator *(Vector vector)
{
	float result = this->x * vector.x + this->y * vector.y + this->z * vector.z;

	return result;
}



Vector Vector::operator*(float a)
{
	Vector result;

	result.x = this->x * a;
	result.y = this->y * a;
	result.z = this->z * a;

	return result;
}

Vector Vector::operator/(float a)
{
	Vector result;

	result.x = this->x / a;
	result.y = this->y / a;
	result.z = this->z / a;

	return result;
}

Vector Vector::compose(Vector &vector1)
{
	Vector result;

	result.x = this->x * vector1.x;
	result.y = this->y * vector1.y;
	result.z = this->z * vector1.z;

	return result;
}

float Vector::norme()
{
	float x = this->x;
	float y = this->y;
	float z = this->z;

	float norme = sqrt(x * x + y * y + z * z);

	return norme;
}

Vector Vector::project(Vector &vector1)
{
	Vector result = vector1 * (*this*(vector1))/vector1.norme();
	return result;
}

float Vector::distance(Vector &vector1)
{
	float result = sqrt((this->x - vector1.x) * (this->x - vector1.x) +
						(this->y - vector1.y) * (this->y - vector1.y) +
						(this->z - vector1.z) * (this->z - vector1.z));
	return result;
}

Vector Vector::operator ^(Vector &vector)
{
	Vector result;

	result.x = (this->y * vector.z) - (this->z *  vector.y);
	result.y = (this->z * vector.x) - (this->x *  vector.z);
	result.z = (this->x * vector.y) - (this->y *  vector.x);

	return result;
}

float Vector::produitMixte(Vector &vector1, Vector &vector2)
{
	float result = *this*(vector1^vector2);

	return result;
}
	




