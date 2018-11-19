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


void Quaternion::normalize()
{
    auto d = (this->r * this->r) + (this->i * this->i) + (this->j * this->j) + (this->k * this->k);
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

Matrix4x4 Quaternion::quaternToMatrix()
{
	float tab[12];

	tab[0] = 1 - (2 * (this->j * this->j) + 2 * (this->k * this->k));
	tab[1] = 2 * this->i * this->j + 2 * this->k * this->r;
	tab[2] = 2 * this->i * this->k - 2 * this->j * this->r;
	tab[3] = i;
	tab[4] = 2 * this->i * this->j - 2 * this->k * this->r;
	tab[5] = 1 - (2 * (this->i * this->i) + 2 * (this->k * this->k));
	tab[6] = 2 * this->j * this->k + 2 * this->i * this->r;
	tab[7] = j;
	tab[8] = 2 * this->i * this->k + 2 * this->j * this->r;
	tab[9] = 2 * this->j * this->k - 2 * this->i * this->r;
	tab[10] = 1 - (2 * (this->i * this->i) + 2 * (this->j * this->j));
	tab[11] = k;

	Matrix4x4 result(tab);

	return result;
}
