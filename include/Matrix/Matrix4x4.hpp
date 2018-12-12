#pragma once

class Matrix4x4
{
private:
	float cells[16] = {};

public:
	Matrix4x4();
	Matrix4x4(float tab[12]);

	float getWithIndice(int i);
	float getDeterminant();
	float* getTab();

	Matrix4x4 inverse();

	Matrix4x4 operator *(float a) const;

	/*Matrix4x4 operator* (const Matrix4x4& m) const;
	Quaternion operator *(const Quaternion& q) const;*/
};