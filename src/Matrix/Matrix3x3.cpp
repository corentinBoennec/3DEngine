#include "Matrix/Matrix3x3.hpp"
#include "Matrix/Quaternion.hpp"

Matrix3x3::Matrix3x3()
{
	for (int i = 0; i < 9; i++)
	{
		cells[i] = 0;
	}
}

Matrix3x3::Matrix3x3(float tab[9])
{
	for (int i = 0; i < 9; i++)
	{
		cells[i] = tab[i];
	}
}

float Matrix3x3::getWithIndice(int i)
{
	return cells[i];
}

float Matrix3x3::getDeterminant()
{
	float det = (cells[0] * cells[4] * cells[8]) + (cells[3] * cells[7] * cells[2]) + (cells[6] * cells[1] * cells[5]) - (cells[0] * cells[7] * cells[5]) - (cells[6] * cells[4] * cells[2]) - (cells[3] * cells[1] * cells[8]);
	return det;
}

Matrix3x3 Matrix3x3::inverse()
{
	float comTab[9];
	comTab[0] = (cells[4] * cells[8]) - (cells[5] * cells[7]);
	comTab[1] = (cells[2] * cells[7]) - (cells[1] * cells[8]);
	comTab[2] = (cells[1] * cells[5]) - (cells[2] * cells[4]);
	comTab[3] = (cells[5] * cells[6]) - (cells[3] * cells[8]);
	comTab[4] = (cells[0] * cells[8]) - (cells[2] * cells[6]);
	comTab[5] = (cells[2] * cells[3]) - (cells[0] * cells[5]);
	comTab[6] = (cells[3] * cells[7]) - (cells[4] * cells[6]);
	comTab[7] = (cells[1] * cells[6]) - (cells[0] * cells[7]);
	comTab[8] = (cells[0] * cells[4]) - (cells[1] * cells[3]);

	Matrix3x3 coMatrix(comTab);
	float det = getDeterminant();
	if (det != 0)
	{
		 Matrix3x3 inverse = coMatrix * (1 / det);
		 return inverse;
	}
	else
	{
		exit(EXIT_FAILURE);
		// return somthing for non inversible matrix
	}
}

Matrix3x3 Matrix3x3::transpose()
{
	float transposeTab[9];
	transposeTab[0] = cells[0];
	transposeTab[1] = cells[3];
	transposeTab[2] = cells[6];
	transposeTab[3] = cells[1];
	transposeTab[4] = cells[4];
	transposeTab[5] = cells[7];
	transposeTab[6] = cells[2];
	transposeTab[7] = cells[5];
	transposeTab[8] = cells[8];

	Matrix3x3 transpose(transposeTab);

	return transpose;

}

void Matrix3x3::quaternToMatrix3(Quaternion q)
{
	float tab[9];

	tab[0] = 1 - (2 * (q.getY() * q.getY()) + 2 * (q.getZ() * q.getZ()));
	tab[1] = 2 * q.getX() * q.getY() + 2 * q.getZ() * q.getAngle();
	tab[2] = 2 * q.getX() * q.getZ() - 2 * q.getY() *q.getAngle();
	tab[3] = 2 * q.getX() * q.getY() - 2 * q.getZ() * q.getAngle();
	tab[4] = 1 - (2 * (q.getX() * q.getX()) + 2 * q.getZ() * q.getZ());
	tab[5] = 2 * q.getY() * q.getZ() + 2 * q.getX() * q.getAngle();
	tab[6] = 2 * q.getX() * q.getZ() + 2 * q.getY() * q.getAngle();
	tab[7] = 2 * q.getY() * q.getZ() - 2 * q.getX()* q.getAngle();
	tab[8] = 1 - (2 * (q.getX() * q.getX()) + 2 * (q.getY() * q.getY()));

	Matrix3x3 result(tab);
	*this = result;
}


Matrix3x3 Matrix3x3::operator*(float a) const
{
	float m[9];
	for (int i = 0; i < 9; i++)
	{
		m[i] = this->cells[i] * a;
	}

	Matrix3x3 result = Matrix3x3(m);

	return result;
}
 
Matrix3x3 Matrix3x3::operator*(const Matrix3x3& m) const
{
	float tab[9];
	tab[0] = this->cells[0] * m.cells[0] + this->cells[1] * m.cells[3] + this->cells[2] * m.cells[6];
	tab[0] = this->cells[0] * m.cells[1] + this->cells[1] * m.cells[4] + this->cells[2] * m.cells[7];
	tab[0] = this->cells[0] * m.cells[2] + this->cells[1] * m.cells[5] + this->cells[2] * m.cells[8];
	tab[0] = this->cells[3] * m.cells[0] + this->cells[4] * m.cells[3] + this->cells[5] * m.cells[6];
	tab[0] = this->cells[3] * m.cells[1] + this->cells[4] * m.cells[4] + this->cells[5] * m.cells[7];
	tab[0] = this->cells[3] * m.cells[2] + this->cells[4] * m.cells[5] + this->cells[5] * m.cells[8];
	tab[0] = this->cells[6] * m.cells[0] + this->cells[7] * m.cells[3] + this->cells[8] * m.cells[6];
	tab[0] = this->cells[6] * m.cells[1] + this->cells[7] * m.cells[4] + this->cells[8] * m.cells[7];
	tab[0] = this->cells[6] * m.cells[2] + this->cells[7] * m.cells[5] + this->cells[8] * m.cells[8];

	Matrix3x3 result(tab);

	return result;
	
}

Vector3D Matrix3x3::operator*(Vector3D& v) const
{
	float x, y, z;
	x = this->cells[0] * v.getX() + this->cells[1] * v.getY() + this->cells[2] * v.getZ();
	y = this->cells[3] * v.getX() + this->cells[4] * v.getY() + this->cells[5] * v.getZ();
	z = this->cells[6] * v.getX() + this->cells[7] * v.getY() + this->cells[8] * v.getZ();

	Vector3D result(x, y, z);

	return result;
}