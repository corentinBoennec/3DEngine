#include <iostream>
#include "Vector3D.hpp"
class Matrix3x3
{
private :
	float cells[9];

	
public :
	Matrix3x3();
	Matrix3x3(float tab[9]);
	float get(int i);
	float getDet();
	Matrix3x3 inverse();
	Matrix3x3 operator *(float a) const;
	Matrix3x3 transpose();
	Matrix3x3 operator* (const Matrix3x3& m) const;
	Vector3D operator* (Vector3D& v) const;
};