#pragma once
#include <chrono>
#include <Windows.h>
#include <vector>
#include <algorithm>

#include "Vector3D.hpp"
#include "Particule.hpp"

namespace utils
{
	void timeGestion(float timeFrame); // permet de controller les FPS
	void integrator(std::vector<Particule*> tableParticule, float timeFrame); // appelle les fonctions de MAJ de la v�locit� et de la position
}
