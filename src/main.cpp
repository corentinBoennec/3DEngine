#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

#include "Functions.hpp"


int main(int argc, char **argv)
{
	// Définition des constantes
	float constexpr timeFrame = (1000/30); // temps d'une frame en ms pour avoir 30 FPS

	// Attributs des particules
	Vector gravity(0, 0, -10);
	Vector position(0, 0, 5);
	Vector acceleration(0, 0, 0);
	float damping = 0.8;	

	Vector velocity1(15, 15, 15);
	Vector velocity2(11, 17, 9);
	Vector velocity3(-8, 10, 50);

	std::ofstream myfile; // fichier d'écriture des positions

	Particule particule1(5, damping, position, velocity1, acceleration, gravity, 1);
	Particule particule2(10, damping, position, velocity2, acceleration, gravity, 2);
	Particule particule3(20, damping, position, velocity3, acceleration, gravity, 3);

	myfile.open("updateParticule.txt");

	while (true)
	{
		utils::timeGestion(timeFrame); // gestion des FPS

		// MAJ des positions et vélocité
		utils::integrator(particule1, timeFrame);
		utils::integrator(particule2, timeFrame);
		utils::integrator(particule3, timeFrame);

		particule1.PrintPosition(myfile);
		particule2.PrintPosition(myfile);
		particule3.PrintPosition(myfile);

		myfile << std::endl; // pour la "Mise en page" :)
	}
	myfile.close();

	/* tentative infructueuse de l'utilisation d'OpenGL :'(
	// init GLUT et crée une fenêtre
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(320, 320);
	glutCreateWindow("3DEngine");

	// register callbacks
	glutDisplayFunc(callgluts::renderScene);
	glutReshapeFunc(callgluts::windowResize);
	//glutIdleFunc(callgluts::renderScene);

	// cycle d'évènement de GLUT 
	glutMainLoop();
	*/

	return 1;   
}