#pragma once
#include <chrono>
#include <vector>
#include <algorithm>

#include "Vector3D.hpp"
#include "Particule.hpp"
#include "RigidBody.hpp"



namespace utils
{
	void timeGestion(float timeFrame); // permet de controller les FPS
	void integrator(std::vector<Particule*> tableParticule, float timeFrame); // appelle les fonctions de MAJ de la vélocité et de la position
	void integratorRigidBody(std::vector<RigidBody*> tableRigidBody, float timeFrame);
}
