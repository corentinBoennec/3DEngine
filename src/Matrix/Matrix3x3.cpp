#include "Matrix/Matrix3x3.hpp"


Matrix3x3::Matrix3x3()
{
	for (int i = 1; i <= 9; i++)
	{
		cells[i] = 0;
	}
}

Matrix3x3::Matrix3x3(float tab[9])
{
	for (int i = 1; i <= 9; i++)
	{
		cells[i] = tab[i];
	}
}

float Matrix3x3::get(int i)
{
	return cells[i];
}

float Matrix3x3::getDet()
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
	float det = getDet();
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