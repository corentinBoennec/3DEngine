#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "Functions.hpp"
#include "worldParticles.hpp"

int main(int argc, char **argv)
{
	// Définition des constantes
	float constexpr timeFrame = (1000.f/30.f); // temps d'une frame en ms pour avoir 30 FPS

	std::vector<Particule*> tableParticule;
	worldParticles world;

	/* cas 1 */
	// Attributs des particules
	/*Vector3D gravity(0, 0, -10);
	Vector3D position1(0, -15, 5);
	Vector3D acceleration(0, 0, 0);
	float damping = 0.8f;	
	Vector3D velocity1(0, 7, 0);

	
	Vector3D position2(0, 15, 5);
	Vector3D velocity2(0, -7, 0);*/

	/* cas 2 */
	Vector3D gravity(0, 0, -10);
	Vector3D position1(0, 0.1, 50);
	Vector3D acceleration(0, 0, 0);
	float damping = 0.8f;	
	Vector3D velocity1(0, 0, 0);

	
	Vector3D position2(0, 0, 5);
	Vector3D velocity2(0, 0, 0);
	

	Particule particule1(5, damping, position1, velocity1, acceleration, gravity, 5);
	Particule particule2(5, damping, position2, velocity2, acceleration, gravity, 5);
	tableParticule.insert(tableParticule.begin(), &particule1);
	world.addParticle(&particule1);
	tableParticule.insert(tableParticule.begin(), &particule2);
	world.addParticle(&particule2);


	std::ofstream myfile; // fichier d'écriture des positions

	myfile.open("updateParticule.txt");

	while (true)
	{
		utils::timeGestion(timeFrame); // gestion des FPS
		utils::integrator(world.getParticles(), timeFrame); // MAJ des positions et vélocité
		// Detection des contacts
		std::vector<ParticleContact> contacts = world.getAllContact();
	
		// résolutions des contacts
		ParticleContactResolver resolver = ParticleContactResolver();
		for (auto &contact : contacts)
		{
			resolver.setIterations(&contact);
		}
		resolver.resolveContact(timeFrame);
		particule1.PrintPosition(myfile);
		particule2.PrintPosition(myfile);


	}
	myfile.close();

	return 1;   
}