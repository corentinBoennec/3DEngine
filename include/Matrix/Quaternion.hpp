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
		void updateAngularVelocity(Vector3D v, float timeFrame);
		void modulateToPI();

        Quaternion operator *(const Quaternion& quaternion) const;
		Quaternion operator *(const float& scalaire) const;
		Quaternion operator +(const Quaternion& quaternion) const;

		Matrix3x3 quaternToMatrix3();
		Matrix4x4 quaternToMatrix4();

		//Quaternion operator/(const float& scalaire) const;

		//Getter
		float getAngle();
		float getX();
		float getY();
		float getZ();
};