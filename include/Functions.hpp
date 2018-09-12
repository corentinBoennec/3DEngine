#pragma once
#include <GL/glut.h>
#include <chrono>

#include "Vector.hpp"
#include "Particule.hpp"

namespace utils
{
	void timeGestion(float timeFrame); // permet de controller les FPS
	void integrator(Particule& particule, float timeFrame); // appelle les fonctions de MAJ de la vélocité et de la position
}

// test OpenGL 
/*namespace callgluts
{
	void windowResize(int w, int h);
	void renderScene(void);
}*/
