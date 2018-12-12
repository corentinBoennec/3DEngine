/* Pour la démonstration de la phase n°4, toute la partie orientation à été sois mis en commentaire,
sois elle n'est pas effective et les valeurs passées sont juste pour le bon fonctionnement de la simulation*/

#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "Functions.hpp"
#include "Matrix/Matrix3x3.hpp"
#include "Matrix/Matrix4x4.hpp"
#include "RigidBody.hpp"
#include "Forces/GravityGeneratorRigidBody.hpp"
#include "Forces/RegistreForceRigidBody.hpp"
#include "WorldRigidBody.hpp"

#include "Tree\Plan.hpp"
#include "Tree\QuadtreeNode.hpp"
#include "Tree\QuadTree.hpp"
#include "Box.hpp"
#include "Plane.hpp"
#include "Contact/CollisionData.hpp"

// Définition des constantes
float constexpr timeFrame = (1000.f / 30.f); // temps d'une frame en ms pour avoir 30 FPS

std::vector<RigidBody*> tableRigidBody;

Plan rightWall(Vector3D(10, 0, 0), Vector3D(1, 0, 0));
Plan leftWall(Vector3D(-10, 0, 0), Vector3D(1, 0, 0));
Plan topWall(Vector3D(0, 0, 20), Vector3D(0, 0, 1));
Plan bottomWall(Vector3D(0, 0, 0), Vector3D(0, 0, 1));

Plan tabPlan[4] = { rightWall, leftWall, topWall, bottomWall };
// Les normales pointes vers la droite et le haut

Vector3D gravity(0, 0, -10);
float linearDamping = 0.95f;
float angularDamping = 1.0f;

// Les positions se trouve sur un plan 2D allant de -10 à 10 sur l'axe x et de 0 à 20 sur l'axe z
Vector3D position(3.0, 0.0, 18.0);
Vector3D position2(7.0, 0.0, 17.0);
Vector3D position3(-7.5, 0.0, 4);

Vector3D velocity(1, 0.0, 0.0);
Vector3D angularVelocity(4.0, 0.0, 0.0);
Quaternion orientation(1, 2, 2, 2);

RigidBody * sphere = new RigidBody(1, linearDamping, angularDamping, position, velocity, angularVelocity, gravity, orientation, 1);
RigidBody * sphere2 = new RigidBody(2, linearDamping, angularDamping, position2, velocity, angularVelocity, gravity, orientation, 1);
RigidBody * sphere3 = new RigidBody(3, linearDamping, angularDamping, position3, velocity, angularVelocity, gravity, orientation, 1);

// Forces
RegistreForceRigidBody registre;
GravityGeneratorRigidBody grav(gravity);

// Déclaration du monde contenant tous les corps rigides
WorldRigidBody worldR;
std::vector<contactBroad> broadContacts;

CollisionData collisionData(5);

Vector3D halfSizeBox(2.0, 2.0, 2.0);
Vector3D planeNormal(1.0, 0.0, 0.0);

//Déclaration des primitives ici pour pouvoir les utiliser dans OpenGL, d
Box box(halfSizeBox, sphere);
Plane plane(planeNormal, 7);

// OpenGL functions

void reshapeFunc(int x, int y)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(100.0, (GLdouble)x / (GLdouble)y, 0, 100.0);
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
	glScalef(0.5, 0.5, 0.0);
	glTranslatef(1.0 * sphere->getPosition().getX(), 1.0 * sphere->getPosition().getY(), 1.0 * sphere->getPosition().getZ());
	box.DrawBox();
	glTranslatef(-1.0 * sphere->getPosition().getX(), -1.0 * sphere->getPosition().getY(), -1.0 * sphere->getPosition().getZ());
	plane.DrawPlane();
	glPopMatrix();

	glutSwapBuffers();
}

void idleFunc(void)
{
	registre.add(sphere, &grav);
	registre.add(sphere2, &grav);
	registre.add(sphere3, &grav);

	broadContacts = worldR.getAllContactBroad(1);
	std::cout << broadContacts.size();
	//Detection des contacts
	if (broadContacts.size() > 0)
	{
		int maxCollision;
		if (broadContacts.size() < collisionData.getContactRestant())
			maxCollision = broadContacts.size();
		else
			maxCollision = collisionData.getContactRestant();

		// Faire une boucle qui prend en compte le nombre max de collision
		for (int i = 0; i < maxCollision; i++)
		{
			box = Box(halfSizeBox, broadContacts[i].rb1);
			plane = Plane(planeNormal, 22);
			utils::generateContacts(box, plane, &collisionData);
		}

		if (collisionData.getContacts().size() > 0)
		{
			collisionData.printData();
			exit(EXIT_SUCCESS);
		}
	}
	else
		std::cout << "Il n'y a aucune collision détéctée." << std::endl;

	registre.update(timeFrame); // MAJ des forces
	utils::integratorRigidBody(worldR.getRigidBody(), timeFrame); // MAJ des positions et vélocité
	registre.cleanRegistre();
	worldR.cleanTree();

	glutPostRedisplay();
}

int main(int argc, char **argv)
{


	tableRigidBody.insert(tableRigidBody.begin(), sphere);
	tableRigidBody.push_back(sphere2);
	tableRigidBody.push_back(sphere3);
	QuadTreeNode firstNode(tabPlan, tableRigidBody);// pas très beau, a changer
	worldR = WorldRigidBody(firstNode, tableRigidBody);// pas très beau, a changer

	float tab[9];
	for (int i = 0; i < 9; i++)
	{
		if (i % 4 == 0)
			tab[i] = (2.0 / 5.0) * sphere->getMass() * (1 * 1);
		else
			tab[i] = 0;
	}
	Matrix3x3 inertiaTensor(tab);
	sphere->setInertiaTensor(inertiaTensor);


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

	/*delete(sphere);
	delete(sphere2);
	delete(sphere3);*/
	return 1;
}