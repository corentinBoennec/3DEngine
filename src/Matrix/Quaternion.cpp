#define _USE_MATH_DEFINES
#include "Matrix/Quaternion.hpp"

Quaternion::Quaternion() {}

Quaternion::Quaternion(float r, float i, float j, float k)
{
	this->r = r;
	this->i = i;
	this->j = j;
	this->k = k;
}

Quaternion::~Quaternion() {}

Quaternion Quaternion::operator *(const Quaternion& quaternion) const
{
	Quaternion result;

	result.r = this->r * quaternion.r - this->i * quaternion.i - this->j * quaternion.j - this->k * quaternion.k;
	result.i = this->r * quaternion.i + this->i * quaternion.r + this->j * quaternion.k - this->k * quaternion.j;
	result.j = this->r * quaternion.j + this->j * quaternion.r + this->k * quaternion.i - this->k * quaternion.j;
	result.k = this->r * quaternion.k + this->k * quaternion.r + this->i * quaternion.j - this->j * quaternion.i;

	return result;
}

Quaternion Quaternion::operator*(const float& scalaire) const
{
	Quaternion result;

	result.r = this->r * scalaire;
	result.i = this->i * scalaire;
	result.j = this->j * scalaire;
	result.k = this->k * scalaire;

	return result;
}

Quaternion Quaternion::operator+(const Quaternion& quaternion) const
{
	Quaternion result;

	result.r = this->r + quaternion.r;
	result.i = this->i + quaternion.i;
	result.j = this->j + quaternion.j;
	result.k = this->k + quaternion.k;

	return result;
}

bool Quaternion::operator==(Quaternion q1)
{
	if (this->getAngle() == q1.getAngle() && this->getX() == q1.getX() && this->getY() == q1.getY() && this->getZ() == this->getZ())
	{
		return true;
	}
	else
		return false;
}

Matrix3x3 Quaternion::quaternToMatrix3()
{
	float tab[9];

	tab[0] = 1 - (2 * (this->getY() * this->getY()) + 2 * (this->getZ() * this->getZ()));
	tab[1] = 2 * this->getX() * this->getY() + 2 * this->getZ() * this->getAngle();
	tab[2] = 2 * this->getX() * this->getZ() - 2 * this->getY() * this->getAngle();
	tab[3] = 2 * this->getX() * this->getY() - 2 * this->getZ() * this->getAngle();
	tab[4] = 1 - (2 * (this->getX() * this->getX()) + 2 * this->getZ() * this->getZ());
	tab[5] = 2 * this->getY() * this->getZ() + 2 * this->getX() * this->getAngle();
	tab[6] = 2 * this->getX() * this->getZ() + 2 * this->getY() * this->getAngle();
	tab[7] = 2 * this->getY() * this->getZ() - 2 * this->getX()* this->getAngle();
	tab[8] = 1 - (2 * (this->getX() * this->getX()) + 2 * (this->getY() * this->getY()));

	Matrix3x3 result(tab);
	return result;
}

Matrix4x4 Quaternion::quaternToMatrix4()
{
	float tab[12];

	tab[0] = 1 - (2 * (this->getY() * this->getY()) + 2 * (this->getZ() * this->getZ()));
	tab[1] = 2 * this->getX() * this->getY() + 2 * this->getZ() * this->getAngle();
	tab[2] = 2 * this->getX() * this->getZ() - 2 * this->getY() * this->getAngle();
	tab[3] = this->getX();
	tab[4] = 2 * this->getX() * this->getY() - 2 * this->getZ() * this->getAngle();
	tab[5] = 1 - (2 * (this->getX() * this->getX()) + 2 * this->getZ() * this->getZ());
	tab[6] = 2 * this->getY() * this->getZ() + 2 * this->getX() * this->getAngle();
	tab[7] = this->getY();
	tab[8] = 2 * this->getX() * this->getZ() + 2 * this->getY() * this->getAngle();
	tab[9] = 2 * this->getY() * this->getZ() - 2 * this->getX()* this->getAngle();
	tab[10] = 1 - (2 * (this->getX() * this->getX()) + 2 * (this->getY() * this->getY()));
	tab[11] = this->getZ();

	Matrix4x4 result(tab);
	return result;
}

/*
Quaternion Quaternion::operator/(const float& scalaire) const
{
	Quaternion result;

	result.r = this->r / scalaire;
	result.i = this->i / scalaire;
	result.j = this->j / scalaire;
	result.k = this->k / scalaire;

	return result;
} */

void Quaternion::normalize()
{
	float d = (this->r * this->r) + (this->i * this->i) + (this->j * this->j) + (this->k * this->k);
	if (d == 0)
	{
		r = 1;
	}
	else
	{
		d = 1 / sqrt(d);
		r *= d;
		i *= d;
		j *= d;
		k *= d;
	}
}

void Quaternion::doRotation(Vector3D v)
{
	Quaternion quatern(0, v.getX(), v.getY(), v.getZ());
	Quaternion quatern2(this->getAngle(), this->getX(), this->getY(), this->getZ());
	quatern2.normalize();
	Quaternion newQuatern = quatern * quatern2;

	this->r = newQuatern.getAngle();
	this->i = newQuatern.getX();
	this->j = newQuatern.getY();
	this->k = newQuatern.getZ();
}

void Quaternion::updateAngularVelocity(Vector3D v, float timeFrame)
{
	Quaternion w(0, v.getX(), v.getY(), v.getZ());
	*this = *this + w * *this * (timeFrame / 2000);
}

void Quaternion::modulateToPI()
{
	this->r = std::fmodf(this->r, M_PI);
}

float Quaternion::getAngle()
{
	return this->r;
}

float Quaternion::getX()
{
	return this->i;
}

float Quaternion::getY()
{
	return this->j;
}

float Quaternion::getZ()
{
	return this->k;
}

void Quaternion::setAngle(float angle)
{
	this->r = angle;
}

void Quaternion::setX(float x)
{
	this->i = x;
}

void Quaternion::setY(float y)
{
	this->j = y;
}

void Quaternion::setZ(float z)
{
	this->k = z;
}