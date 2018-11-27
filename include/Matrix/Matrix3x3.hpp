#pragma once
#include <iostream>

class Vector3D;

class Matrix3x3
{
private :
	float cells[9] = {};

	
public :
	Matrix3x3();
	Matrix3x3(float tab[9]);

	float getWithIndice(int i);
	float getDeterminant();

	Matrix3x3 inverse();
	Matrix3x3 transpose();

	float getCells(int i);

	Matrix3x3 operator *(float a) const;
	Matrix3x3 operator* (const Matrix3x3& m) const;
	Vector3D Matrix3x3::operator*(Vector3D& v) const;
};