#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "Functions.hpp"


int main(int argc, char **argv)
{
	// D�finition des constantes
	float constexpr timeFrame = (1000/30); // temps d'une frame en ms pour avoir 30 FPS

	std::vector<Particule*> tableParticule;

	// Attributs des particules
	Vector3D gravity(0, 0, -10);
	Vector3D position(0, 0, 5);
	Vector3D acceleration(0, 0, 0);
	float damping = 0.8;	
	Vector3D velocity(15, 15, 15);

	std::ofstream myfile; // fichier d'�criture des positions

	Particule particule(5, damping, position, velocity, acceleration, gravity);
	tableParticule.insert(tableParticule.begin(), &particule);


	myfile.open("updateParticule.txt");

	while (true)
	{
		utils::timeGestion(timeFrame); // gestion des FPS
		utils::integrator(tableParticule, timeFrame); // MAJ des positions et v�locit�
		particule.PrintPosition(myfile);
	}
	myfile.close();

	return 1;   
}