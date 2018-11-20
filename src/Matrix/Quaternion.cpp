#include "Matrix/Quaternion.hpp"


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

Quaternion Quaternion::operator+(const Quaternion& quaternion) const
{
	Quaternion result;

	result.r = this->r + quaternion.r;
	result.i = this->i + quaternion.i;
	result.j = this->j + quaternion.j;
	result.k = this->k + quaternion.k;

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

Quaternion Quaternion::operator/(const float& scalaire) const
{
	Quaternion result;

	result.r = this->r / scalaire;
	result.i = this->i / scalaire;
	result.j = this->j / scalaire;
	result.k = this->k / scalaire;

	return result;
};


void Quaternion::normalize()
{
    float d = (this->r * this->r) + (this->i * this->i) + (this->j * this->j) + (this->k * this->k);
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
    Quaternion quatern(0, v.getX(), v.getY(), v.getZ());
	*this = *this * quatern;
	
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
