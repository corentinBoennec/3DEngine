#pragma once
#include <GL/glut.h>
#include <chrono>

#include "Vector.hpp"
#include "Particule.hpp"

namespace utils
{
	float inverseMass(float mass);
	void timeGestion(int timeFrame); // Permet de controller la vitesse d'affichage
}
