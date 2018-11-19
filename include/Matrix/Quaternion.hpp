#pragma once

#include <math.h>
#include "Vector3D.hpp"
#include "Matrix/Matrix4x4.hpp"


class Quaternion
{
    private:
		float r; 
		float i;
		float j;
		float k;

    public:
        Quaternion();
        Quaternion(float r, float i, float j, float k);
        ~Quaternion();
        void normalize();
        void doRotation(Vector3D v);
        Quaternion operator *(const Quaternion& quaternion) const;
		Quaternion operator +(const Quaternion& quaternion) const;
		Quaternion operator *(const float& scalaire) const;
		Matrix4x4 quaternToMatrix();
};