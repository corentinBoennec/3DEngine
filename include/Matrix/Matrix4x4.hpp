#include "Matrix/Matrix3x3.hpp"
#include "Matrix/Quaternion.hpp"

class Matrix4x4
{
private:
	float cells[16];


public:
	Matrix4x4();
	Matrix4x4(float tab[12]);
	float get(int i);
	float getDet();
	Matrix4x4 inverse();
	Matrix4x4 operator *(float a) const;
	Matrix4x4 operator* (const Matrix4x4& m) const;
	Vector3D operator *(const Quaternion& q) const;


};