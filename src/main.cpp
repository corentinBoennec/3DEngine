#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>


#include "Functions.hpp"

#include "WorldParticules.hpp"
#include "Spring/SimpleSpring.hpp"
#include "Forces/RegistreForce.hpp"
#include "Forces/DragGenerator.hpp"
#include "Forces/GravityGenerator.hpp"

#include "Matrix/Matrix3x3.hpp"
#include "Matrix/Matrix4x4.hpp"
#include "RigidBody.hpp"
#include "Forces/GravityGeneratorRigidBody.hpp"
#include "Forces/RegistreForceRigidBody.hpp"
#include "WorldRigidBody.hpp"
#include "Tree\Plan.hpp"
#include "Tree\QuadtreeNode.hpp"
#include "Tree\QuadTree.hpp"


// TODO: Update les différentes accélération
// TODO: Update les rotations via DoRotation
// TODO: Update angularVelocity via la fonction

// Définition des constantes
float constexpr timeFrame = (1000.f / 30.f); // temps d'une frame en ms pour avoir 30 FPS

/*std::vector<Particule*> tableParticule;
WorldParticules world;

Cas 2 - Ressort
Vector3D gravity(0, 0, -10);
Vector3D acceleration(0, 0, 0);
float damping = 0.8f;

Vector3D position1(2.0, 0.0, 0.0);
Vector3D velocity1(-0.3, 0.0, 0.0);

Vector3D position2(-4.0, 0.0, 0.0);
Vector3D velocity2(0.0, 0.0, 0.0);

Particule particule1(5, damping, position1, velocity1, acceleration, gravity, 0.5);
Particule particule2(5, damping, position2, velocity2, acceleration, gravity, 0.5);

SimpleSpring spring(&particule2, 1, 2);

// Forces
RegistreForce registre;
DragGenerator drag(1, 1);
GravityGenerator grav(gravity);
*/

std::vector<RigidBody> tableRigidBody;


Plan rightWall(Vector3D(10, 0, 0), Vector3D(1, 0, 0));
Plan leftWall(Vector3D(-10, 0, 0), Vector3D(1, 0, 0));
Plan topWall(Vector3D(0, 0, 20), Vector3D(0, 0, 1));
Plan bottomWall(Vector3D(0, 0, 0), Vector3D(0, 0, 1));

Plan tabPlan[4] = { rightWall, leftWall, topWall, bottomWall };
// Les normales pointes vers la droite et le haut

Vector3D gravity(0, 0, -10);
float linearDamping = 0.95f;
float angularDamping = 1.0f;

Vector3D position(6, 0.0, 18.9);
Vector3D position2(-6.1, 0.0, 18.9);
Vector3D position3(1, 0.0, 14);


Vector3D velocity(-0.5, 0.0, 0.0);
Vector3D angularVelocity(4.0, 0.0, 0.0);
Quaternion orientation(1, 2, 2, 2);

RigidBody sphere(1, linearDamping, angularDamping, position, velocity, angularVelocity, gravity, orientation, 0.1);
RigidBody sphere2(2, linearDamping, angularDamping, position2, velocity, angularVelocity, gravity, orientation, 0.1);
RigidBody sphere3(3, linearDamping, angularDamping, position3, velocity, angularVelocity, gravity, orientation, 0.1);

// Forces
RegistreForceRigidBody registre;
GravityGeneratorRigidBody grav(gravity);


// OpenGL functions

void reshapeFunc(int x, int y)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(90.0, (GLdouble)x / (GLdouble)y, 0.5, 50.0);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, x, y);
}

void Draw_Spheres(void)
{
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -15.0);

	glColor3f(0.8, 0.2, 0.1);
	glPushMatrix();
	glTranslatef(1.0 * sphere.getPosition().getX(), 1.0 * sphere.getPosition().getY(), 1.0 * sphere.getPosition().getZ());
	glRotatef(1.0 * utils::radToDegree(sphere.getOrientation().getAngle()), 1.0 * sphere.getOrientation().getX(), 1.0 * sphere.getOrientation().getY(), 1.0 * sphere.getOrientation().getZ());
	//std::cout << sphere.getPosition().getX() << " " << sphere.getPosition().getY() << " " << sphere.getPosition().getZ();
	//std::cout << sphere.getOrientation().getAngle() << " " << sphere.getOrientation().getX() << " " << sphere.getOrientation().getY() << " " << sphere.getOrientation().getZ() << std::endl;
	glutSolidSphere(sphere.getRadiusBoudingSphere(), 20, 50);
	glPopMatrix();

	glutSwapBuffers();
}

void idleFunc(void)
{
	registre.add(&sphere, &grav);
	
	// Detection des contacts
	// std::vector<ParticleContact> contacts = worldR.getAllContact();

	// résolutions des contacts
	/*ParticleContactResolver resolver = ParticleContactResolver();
	for (auto &contact : contacts)
	{
		resolver.setIterations(&contact);
	}
	resolver.resolveContact(timeFrame);*/

	registre.update(timeFrame); // MAJ des forces
	//utils::integratorRigidBody(worldR.getRigidBody(), timeFrame); // MAJ des positions et vélocité
	registre.cleanRegistre();
	
	glutPostRedisplay();
	
}

int main(int argc, char **argv)
{

	
	tableRigidBody.insert(tableRigidBody.begin(), sphere);
	tableRigidBody.push_back(sphere2);
	tableRigidBody.push_back(sphere3);
	QuadTreeNode firstNode(tabPlan, tableRigidBody);// pas très beau, a changer
	WorldRigidBody worldR(firstNode, tableRigidBody);// pas très beau, a changer 
	std::vector<contactBroad> broadContacts = worldR.getAllContactBroad(2);


	std::cout << broadContacts.size();
	
	std::cout << "fin ";

	
	/*float tab[9];
	for (int i = 0; i < 9; i++)
	{
		if (i % 4 == 0)
			tab[i] = (2.0 / 5.0) * sphere.getMass() * sphere.getRadius() * sphere.getRadius();
		else
			tab[i] = 0;
	}
	Matrix3x3 inertiaTensor(tab);
	sphere.setInertiaTensor(inertiaTensor);

	tableRigidBody.insert(tableRigidBody.begin(), &sphere);
	worldR.addRigidBody(&sphere);

	/*std::ofstream myfile; // fichier d'écriture des positions

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
		integrator(world.getParticles(), timeFrame); // MAJ des positions et vélocité
		registre.cleanRegistre();
	}
	myfile.close();*/
	/*
	utils::timeGestion(timeFrame); // gestion des FPS

	// Initialisation de GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(1720, 980);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("3DEngine");
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glClearColor(0.0, 0.0, 0.0, 0.0);

	// Callback functions
	glutDisplayFunc(Draw_Spheres);
	glutReshapeFunc(reshapeFunc);
	glutIdleFunc(idleFunc);

	glutMainLoop();

	*/
	return 1;  
}