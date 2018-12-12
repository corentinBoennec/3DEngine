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
float linearDamping = 1.00f;
float angularDamping = 1.0f;

// Les positions se trouve sur un plan 2D allant de -10 à 10 sur l'axe x et de 0 à 20 sur l'axe z
Vector3D position(2.1, 0.0, 18.0);
Vector3D position2(9.1, 0.0, 17.0);
Vector3D position3(-7.5, 0.0, 4);

Vector3D velocity(0.25, 0.0, 0.0);
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
Vector3D planeNormal(-1.0, 0.0, 0.0);

//Déclaration des primitives ici pour pouvoir les utiliser dans OpenGL, d
Box box(halfSizeBox, sphere);
Plane plane(planeNormal, 9.1);

std::ofstream myfile;

// OpenGL functions

void reshapeFunc(int x, int y)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(90.0, (GLdouble)x / (GLdouble)y, 0.2, 50.0);
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
	glScalef(0.1, 0.1, 0.1); // Pas au top mais permet de tout bien voir
	glTranslatef(1.0 * sphere->getPosition().getX(), 1.0 * sphere->getPosition().getY(), 1.0 * sphere->getPosition().getZ()); // Positionnement de la boite
	box.DrawBox();
	glTranslatef(-1.0 * sphere->getPosition().getX(), -1.0 * sphere->getPosition().getY(), -1.0 * sphere->getPosition().getZ()); // Retour à l'origine pour placer le plan
	plane.DrawPlane();
	glPopMatrix();

	glutSwapBuffers();
}

void idleFunc(void) // Permet la mise à jour à chaque frame
{
	registre.add(sphere, &grav);
	registre.add(sphere2, &grav);
	registre.add(sphere3, &grav);

	//Detection des contacts
	if (broadContacts.size() > 0)
	{
		// Permet de ne pas dépasser le nombre de collision max tout en évitant de sortir du tableau
		int maxCollision;
		if (broadContacts.size() < collisionData.getContactRestant())
			maxCollision = broadContacts.size();
		else
			maxCollision = collisionData.getContactRestant();

		for (int i = 0; i < maxCollision; i++)
		{
			box = Box(halfSizeBox, broadContacts[i].rb1);
			plane = Plane(planeNormal, 9.1);
			utils::generateContacts(box, plane, &collisionData, &myfile);
		}

		if (collisionData.getContacts().size() > 0)
		{
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
	QuadTreeNode firstNode(tabPlan, tableRigidBody); // pas très beau, a changer
	worldR = WorldRigidBody(firstNode, tableRigidBody); // pas très beau, a changer
	broadContacts = worldR.getAllContactBroad(1); // Ne se met pas à jour à chaque frame car soucis de mémoire (Tous s'accumule)

	myfile.open("updateParticule.txt");

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

	delete(sphere);
	delete(sphere2);
	delete(sphere3);
	myfile.close();
	return 1;
}