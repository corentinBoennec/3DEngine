#include "Matrix\Matrix4x4.hpp"
#include <iostream>

Matrix4x4::Matrix4x4(){}

Matrix4x4::Matrix4x4(float tab[12])
{
	for (int i = 0; i < 12; i++)
	{
		cells[i] = tab[i];
	}
	cells[12] = 0;
	cells[13] = 0;
	cells[14] = 0;
	cells[15] = 1;
}


float Matrix4x4::getWithIndice(int i)
{
	return cells[i];
}

float Matrix4x4::getDeterminant()
{
	float result = (cells[8] * cells[5] * cells[2]) 
		+ (cells[4] * cells[9] * cells[2]) 
		+ (cells[8] * cells[1] * cells[6]) 
		- (cells[0] * cells[9] * cells[6]) 
		- (cells[4] * cells[1] * cells[10]) 
		- (cells[0] * cells[5] * cells[9]);

	return result;
}

float* Matrix4x4::getTab()
{
	return this->cells;
}

Matrix4x4 Matrix4x4::inverse()
{
	float det = this->getDeterminant();
	float tab[16];
	if (det != 0)
	{
		tab[0] = -(cells[9] * cells[6] + cells[5] * cells[10]);
		tab[1] = (cells[9] * cells[2] + -cells[1] * cells[10]);
		tab[2] = -(cells[5] * cells[2] + cells[1] * cells[6]);
		tab[3] = (cells[9] * cells[6] * cells[3]) - (cells[5] * cells[10] * cells[3]) - (cells[9] * cells[2] * cells[7]) + (cells[1] * cells[10] * cells[7]) + (cells[5] * cells[2] * cells[11]) - (cells[1] * cells[6] * cells[11]);
		tab[4] = (cells[8] * cells[6] - cells[4] * cells[10]);
		tab[5] = -(cells[8] * cells[2] + cells[0] * cells[10]);
		tab[6] = (cells[4] * cells[2] - cells[0] * cells[6]);
		tab[7] = -(cells[8] * cells[6] * cells[3]) - (cells[4] * cells[10] * cells[3]) + (cells[8] * cells[2] * cells[7]) - (cells[0] * cells[10] * cells[7]) - (cells[4] * cells[2] * cells[11]) + (cells[0] * cells[6] * cells[11]);
		tab[8] = -(cells[8] * cells[5] + cells[4] * cells[9]);
		tab[9] = (cells[8] * cells[1] - cells[0] * cells[9]);
		tab[10] = -(cells[4] * cells[1] + cells[0] * cells[5]);
		tab[11] = (cells[8] * cells[5] * cells[3]) - (cells[4] * cells[9] * cells[3]) - (cells[8] * cells[1] * cells[7]) + (cells[0] * cells[9] * cells[7]) + (cells[4] * cells[1] * cells[11]) + (cells[0] * cells[5] * cells[11]);
		tab[12] = 0;
		tab[13] = 0;
		tab[14] = 0;
		tab[15] = 1;
		Matrix4x4 result(tab);
		return result = result * (1 / det);
	}
	else
	{
		exit(EXIT_FAILURE);
	}
}

void Matrix4x4::quaternToMatrix4(Quaternion q)
{
	float tab[12];

	tab[0] = 1 - (2 * (q.getY() * q.getY()) + 2 * (q.getZ() * q.getZ()));
	tab[1] = 2 * q.getX() * q.getY() + 2 * q.getZ() * q.getAngle();
	tab[2] = 2 * q.getX() * q.getZ() - 2 * q.getY() *q.getAngle();
	tab[3] = q.getX();
	tab[4] = 2 * q.getX() * q.getY() - 2 * q.getZ() * q.getAngle();
	tab[5] = 1 - (2 * (q.getX() * q.getX()) + 2 * q.getZ() * q.getZ());
	tab[6] = 2 * q.getY() * q.getZ() + 2 * q.getX() * q.getAngle();
	tab[7] = q.getY();
	tab[8] = 2 * q.getX() * q.getZ() + 2 * q.getY() * q.getAngle();
	tab[9] = 2 * q.getY() * q.getZ() - 2 * q.getX()* q.getAngle();
	tab[10] = 1 - (2 * (q.getX() * q.getX()) + 2 * (q.getY() * q.getY()));
	tab[11] = q.getZ();

	Matrix4x4 result(tab);

	*this = result;
}

Matrix4x4 Matrix4x4::operator *(float a) const
{
	float tab[16];
	for (int i = 0; i < 16; i++)
	{
		tab[i] = cells[i] * a;  // doit-on multiplier le 1 de la derniere case ou la derniere ligne doit-elle rester 0 0 0 1?
	}

	Matrix4x4 result(tab);
	return result;
}


/*Matrix4x4 Matrix4x4::operator* (const Matrix4x4& m) const{}
Quaternion Matrix4x4::operator *(const Quaternion& q) const{}*/
