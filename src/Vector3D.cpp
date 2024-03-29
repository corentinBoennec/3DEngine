#include "Vector3D.hpp"

// Constructeurs
Vector3D::Vector3D(void) {}

Vector3D::Vector3D(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3D::~Vector3D(void)
{
}

// Définition des accesseurs
float Vector3D::getX()
{
	return x;
}

float Vector3D::getY()
{
	return y;
}

float Vector3D::getZ()
{
	return z;
}

void Vector3D::setX(float x)
{
	this->x = x;
}

void Vector3D::setY(float y)
{
	this->y = y;
}

void Vector3D::setZ(float z)
{
	this->z = z;
}

// Surcharge des opérateurs pour des calculs vectoriels
Vector3D Vector3D::operator+(const Vector3D& vector) const
{
	Vector3D result;

	result.x = this->x + vector.x;
	result.y = this->y + vector.y;
	result.z = this->z + vector.z;

	return result;
}

Vector3D Vector3D::operator-(const Vector3D& vector) const
{
	Vector3D result;

	result.x = this->x - vector.x;
	result.y = this->y - vector.y;
	result.z = this->z - vector.z;

	return result;
}

void Vector3D::operator+=(const Vector3D& vector)
{
	this->x += vector.x;
	this->y += vector.y;
	this->z += vector.z;
}

float Vector3D::operator*(const Vector3D & v) const
{
	float result = this->x * v.x + this->y * v.y + this->z * v.z;

	return result;
}

Vector3D Vector3D::operator*(float a) const
{
	Vector3D result;

	result.x = this->x * a;
	result.y = this->y * a;
	result.z = this->z * a;

	return result;
}
bool Vector3D::operator==(Vector3D v1)
{
	if (this->getX() == v1.getX() && this->getY() == v1.getY() && this->getZ() == v1.getZ())
	{
		return true;
	}
	else
		return false;
}

Vector3D Vector3D::operator/(float a) const
{
	Vector3D result;

	result.x = this->x / a;
	result.y = this->y / a;
	result.z = this->z / a;

	return result;
}

Vector3D Vector3D::compose(const Vector3D& vector1) const
{
	Vector3D result;

	result.x = this->x * vector1.x;
	result.y = this->y * vector1.y;
	result.z = this->z * vector1.z;

	return result;
}

float Vector3D::norme() const
{
	float norme = sqrt(x * x + y * y + z * z);
	float rounded_down = floorf(norme * 1000) / 1000;
	return rounded_down;
}

Vector3D Vector3D::project(const Vector3D& vector1) const
{
	Vector3D result = vector1 * (*this*(vector1)) / vector1.norme();
	return result;
}

float Vector3D::distance(const Vector3D& vector1) const
{
	float result = sqrt((this->x - vector1.x) * (this->x - vector1.x) + (this->y - vector1.y) * (this->y - vector1.y) + (this->z - vector1.z) * (this->z - vector1.z));
	return result;
}

Vector3D Vector3D::operator ^(const Vector3D& vector) const
{
	Vector3D result;

	result.x = (this->y * vector.z) - (this->z *  vector.y);
	result.y = (this->z * vector.x) - (this->x *  vector.z);
	result.z = (this->x * vector.y) - (this->y *  vector.x);

	return result;
}

float Vector3D::produitMixte(Vector3D& vector1, const Vector3D& vector2) const
{
	float result = *this*(vector1^vector2);

	return result;
}

Vector3D Vector3D::unit() const
{
	Vector3D result = *this / this->norme();

	return result;
}

Vector3D Vector3D::operator*(Matrix3x3 & m)
{
	float x, y, z;
	x = m.getCells(0) * this->getX() + m.getCells(1) * this->getY() + m.getCells(2) * this->getZ();
	y = m.getCells(3) * this->getX() + m.getCells(4) * this->getY() + m.getCells(5) * this->getZ();
	z = m.getCells(6) * this->getX() + m.getCells(7) * this->getY() + m.getCells(8) * this->getZ();

	Vector3D result(x, y, z);

	return result;
}

void Vector3D::localToWorld(Matrix4x4 transformationMatrix)
{
	int w = 0;

	// En tirer une fonction
	this->x = transformationMatrix.getWithIndice(1) * this->x + transformationMatrix.getWithIndice(2) * this->y + transformationMatrix.getWithIndice(3) * this->z + transformationMatrix.getWithIndice(4) * w;
	this->y = transformationMatrix.getWithIndice(5) * this->x + transformationMatrix.getWithIndice(6) * this->y + transformationMatrix.getWithIndice(7) * this->z + transformationMatrix.getWithIndice(8) * w;
	this->z = transformationMatrix.getWithIndice(9) * this->x + transformationMatrix.getWithIndice(10) * this->y + transformationMatrix.getWithIndice(11) * this->z + transformationMatrix.getWithIndice(12) * w;
}

void Vector3D::localToWorld(Matrix3x3 transformationMatrix)
{
	*this = transformationMatrix.inverse() * *this * transformationMatrix;
}

void Vector3D::worldToLocal(Matrix3x3 transformationMatrix)
{
	localToWorld(transformationMatrix.inverse());
}

void Vector3D::worldToLocal(Matrix4x4 transformationMatrix)
{
	localToWorld(transformationMatrix.inverse());
}