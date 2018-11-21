#pragma once

#include <vector>

#include "Particule.hpp"
#include "RigidBody.hpp"

namespace utils
{
	void integratorRigidBody(std::vector<RigidBody*> tableRigidBody, float timeFrame);
	void timeGestion(float timeFrame); // permet de controller les FPS
	void integrator(std::vector<Particule*> tableParticule, float timeFrame); // appelle les fonctions de MAJ de la vélocité et de la position
}




