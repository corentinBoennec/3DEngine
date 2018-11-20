#pragma once
#include <chrono>
#include <vector>
#include <algorithm>

#include "Particule.hpp"
#include "RigidBody.hpp"
#include "Matrix\Matrix3x3.hpp"



namespace utils
{
	void timeGestion(float timeFrame); // permet de controller les FPS
	void integrator(std::vector<Particule*> tableParticule, float timeFrame); // appelle les fonctions de MAJ de la vélocité et de la position
	void integratorRigidBody(std::vector<RigidBody*> tableRigidBody, float timeFrame);
	Matrix4x4 quaternToMatrix(Quaternion q);
	Vector3D orthonormalChange(Matrix4x4 transformationMatrix, Vector3D v);
}
