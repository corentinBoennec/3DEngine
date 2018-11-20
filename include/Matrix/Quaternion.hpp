#pragma once

#include <math.h>
#include "Vector3D.hpp"


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
		Quaternion operator/(const float& scalaire) const;
		

		//Getter
		float getAngle();
		float getX();
		float getY();
		float getZ();
};