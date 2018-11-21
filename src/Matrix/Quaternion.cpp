#define _USE_MATH_DEFINES
#include "Matrix/Quaternion.hpp"
#include "Vector3D.hpp"

Quaternion::Quaternion(){}

Quaternion::Quaternion(float r, float i, float j, float k)
{
    this->r = r;
    this->i = i;
    this->j = j;
    this->k = k;
}

Quaternion::~Quaternion(){}

Quaternion Quaternion::operator *(const Quaternion& quaternion) const
{
    Quaternion result;

    result.r = this->r * quaternion.r;
    result.i = this->i * quaternion.i;
    result.j = this->j * quaternion.j;
    result.k = this->k * quaternion.k;

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
    float d = (this->i * this->i) + (this->j * this->j) + (this->k * this->k);
    if (d == 0)
    {
		r = 1;
        i = 0;
        j = 0;
        k = 0;
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
	// Comment ça peut fonctionner ? L'angle vaut toujours 0, du coup pas de rotation :/
	Quaternion quatern(0, v.getX(), v.getY(), v.getZ());
	Quaternion quatern2(this->getAngle(), this->getX(), this->getY(), this->getZ());
	Quaternion newQuatern = quatern * quatern2;
	this->r = newQuatern.getAngle();
	this->i = newQuatern.getX();
	this->j = newQuatern.getY();
	this->k = newQuatern.getZ();
}

// A quoi elle sert ? - Pris dans le cours -
void Quaternion::updateAngularVelocity(Vector3D v, float timeFrame)
{
	Quaternion w(0, v.getX(), v.getY(), v.getZ());
	*this = *this + w * *this * (timeFrame / 2000);
}

void Quaternion::modulateToPI()
{
	this->r = (this->r, 2 * M_PI);
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
