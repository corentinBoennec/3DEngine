#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "Functions.hpp"
#include "worldParticles.hpp"
#include "SimpleSpring.hpp"
#include "RegistreForce.hpp"
#include "DragGenerator.hpp"
#include "GravityGenerator.hpp"

// TODO: Mettre les fichiers dans des dossiers

int main(int argc, char **argv)
{
	// Définition des constantes
	float constexpr timeFrame = (1000.f/30.f); // temps d'une frame en ms pour avoir 30 FPS

	std::vector<Particule*> tableParticule;
	worldParticles world;	

	/* Cas 1 - Contact */
	// Attributs des particules
	Vector3D gravity(0, 0, -10);
	Vector3D position1(0, -15, 5);
	Vector3D acceleration(0, 0, 0);
	float damping = 0.8f;	
	Vector3D velocity1(0, 7, 0);

	
	Vector3D position2(0, 15, 5);
	Vector3D velocity2(0, -7, 0);

	
	/*Cas 2 - Ressort*/
	/*Vector3D gravity(0, 0, -10);
	Vector3D acceleration(0, 0, 0);
	float damping = 0.8f;

	Vector3D position1(0, 0, 0);
	Vector3D velocity1(0, 0, 0);

	Vector3D position2(0, 50, 0);
	Vector3D velocity2(0, 0, 0);*/

	Particule particule1(5, damping, position1, velocity1, acceleration, gravity, 5, 1);
	Particule particule2(5, damping, position2, velocity2, acceleration, gravity, 5, 2);

	tableParticule.insert(tableParticule.begin(), &particule1);
	world.addParticle(&particule1);
	tableParticule.insert(tableParticule.begin(), &particule2);
	world.addParticle(&particule2);

	// Forces
	RegistreForce registre;
	DragGenerator drag(1, 1);
	GravityGenerator grav(gravity);

	//SimpleSpring spring(&particule2, 5, 10);

	std::ofstream myfile; // fichier d'écriture des positions

	myfile.open("updateParticule.txt");

	while (true)
	{
		//registre.add(&particule1, &drag);
		registre.add(&particule1, &grav);
		//registre.add(&particule2, &drag);
		registre.add(&particule2, &grav);

		utils::timeGestion(timeFrame); // gestion des FPS
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
		myfile << std::endl;

		registre.update(timeFrame); // MAJ des forces
		//spring.updateForce(&particule1, timeFrame); // MAJ des forces du ressort
		utils::integrator(world.getParticles(), timeFrame); // MAJ des positions et vélocité
		registre.cleanRegistre();
	}
	myfile.close();

	return 1;   
}