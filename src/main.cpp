#include <iostream>
#include <fstream>

#include "Functions.hpp"

int main(int argc, char **argv)
{
	// TODO : mieux commenter le code
	int constexpr timeFrame = 33;
	// TODO : créer une fonction de création d'objet pour simplifier la chose
	Vector gravity(0, 0, -10);
	Vector position(0, 0, 5);
	Vector velocity(15, 15, 15);
	Vector acceleration(0, 0, 0);
	float damping = 0.8;
	std::ofstream myfile;

	Particule particule(5, damping, position, velocity, acceleration, gravity);
	myfile.open("updateParticule.txt");

	while (true)
	{
		// TODO : faire un affichage graphique via OpenGL
		utils::timeGestion(timeFrame);
		particule.updatePosition(timeFrame);
		particule.updateVelocity(timeFrame);
		// TODO : Mettre ça dans une fonction
		myfile << "Position = (" << std::to_string(particule.getPosition().getX()) << ", " << std::to_string(particule.getPosition().getY()) << ", " << std::to_string(particule.getPosition().getZ()) << ")" << std::endl;

	}
	myfile.close();
	


	return 0;   
}