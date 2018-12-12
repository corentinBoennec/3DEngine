#include "..\include\Box.hpp"

#include "GL/freeglut.h"
#include <algorithm>

Box::Box(Vector3D halfSizes, RigidBody* rigidbody)
{
	this->setRigidBody(*rigidbody);
	this->halfSizes = halfSizes;
	this->findVertices();
	//this->printAllVertices();
}

Box::Box() {}

Box::~Box() {}

std::vector<Vector3D> Box::getAllVertices()
{
	return this->allVertices;
}

void Box::findVertices()
{
	RigidBody * rigidbody = this->getRigidBody();

	// Définition de tous les vertex
	allVertices.push_back(Vector3D((rigidbody->getPosition().getX() + halfSizes.getX()), (rigidbody->getPosition().getY() + halfSizes.getY()), (rigidbody->getPosition().getZ() + halfSizes.getZ())));
	allVertices.push_back(Vector3D((rigidbody->getPosition().getX() - halfSizes.getX()), (rigidbody->getPosition().getY() + halfSizes.getY()), (rigidbody->getPosition().getZ() + halfSizes.getZ())));
	allVertices.push_back(Vector3D((rigidbody->getPosition().getX() + halfSizes.getX()), (rigidbody->getPosition().getY() - halfSizes.getY()), (rigidbody->getPosition().getZ() + halfSizes.getZ())));
	allVertices.push_back(Vector3D((rigidbody->getPosition().getX() - halfSizes.getX()), (rigidbody->getPosition().getY() - halfSizes.getY()), (rigidbody->getPosition().getZ() + halfSizes.getZ())));
	allVertices.push_back(Vector3D((rigidbody->getPosition().getX() + halfSizes.getX()), (rigidbody->getPosition().getY() + halfSizes.getY()), (rigidbody->getPosition().getZ() - halfSizes.getZ())));
	allVertices.push_back(Vector3D((rigidbody->getPosition().getX() - halfSizes.getX()), (rigidbody->getPosition().getY() + halfSizes.getY()), (rigidbody->getPosition().getZ() - halfSizes.getZ())));
	allVertices.push_back(Vector3D((rigidbody->getPosition().getX() + halfSizes.getX()), (rigidbody->getPosition().getY() - halfSizes.getY()), (rigidbody->getPosition().getZ() - halfSizes.getZ())));
	allVertices.push_back(Vector3D((rigidbody->getPosition().getX() - halfSizes.getX()), (rigidbody->getPosition().getY() - halfSizes.getY()), (rigidbody->getPosition().getZ() - halfSizes.getZ())));
}

void Box::printAllVertices()
{
	std::for_each(this->allVertices.begin(), this->allVertices.end(), [](Vector3D V) {
		std::cout << V.getX() << " " << V.getY() << " " << V.getZ() << std::endl;
		});
}

void Box::DrawBox()
{
	// Permet le dessin d'un beau pavé :)
	glBegin(GL_QUADS);

	// Front face
	glVertex3f(allVertices.at(1).getX(), allVertices.at(1).getY(), 0);
	glVertex3f(allVertices.at(3).getX(), allVertices.at(3).getY(), 0);
	glVertex3f(allVertices.at(7).getX(), allVertices.at(7).getY(), 0);
	glVertex3f(allVertices.at(5).getX(), allVertices.at(5).getY(), 0);

	// Back face
	glVertex3f(allVertices.at(0).getX(), allVertices.at(0).getY(), 0);
	glVertex3f(allVertices.at(2).getX(), allVertices.at(2).getY(), 0);
	glVertex3f(allVertices.at(6).getX(), allVertices.at(6).getY(), 0);
	glVertex3f(allVertices.at(4).getX(), allVertices.at(4).getY(), 0);

	// Left face
	glVertex3f(allVertices.at(2).getX(), allVertices.at(2).getY(), 0);
	glVertex3f(allVertices.at(3).getX(), allVertices.at(3).getY(), 0);
	glVertex3f(allVertices.at(7).getX(), allVertices.at(7).getY(), 0);
	glVertex3f(allVertices.at(6).getX(), allVertices.at(6).getY(), 0);

	// Right face
	glVertex3f(allVertices.at(0).getX(), allVertices.at(0).getY(), 0);
	glVertex3f(allVertices.at(1).getX(), allVertices.at(1).getY(), 0);
	glVertex3f(allVertices.at(5).getX(), allVertices.at(5).getY(), 0);
	glVertex3f(allVertices.at(4).getX(), allVertices.at(4).getY(), 0);

	//Top Face
	glVertex3f(allVertices.at(0).getX(), allVertices.at(0).getY(), 0);
	glVertex3f(allVertices.at(1).getX(), allVertices.at(1).getY(), 0);
	glVertex3f(allVertices.at(3).getX(), allVertices.at(3).getY(), 0);
	glVertex3f(allVertices.at(2).getX(), allVertices.at(2).getY(), 0);

	// Bottom face
	glVertex3f(allVertices.at(4).getX(), allVertices.at(4).getY(), 0);
	glVertex3f(allVertices.at(5).getX(), allVertices.at(5).getY(), 0);
	glVertex3f(allVertices.at(7).getX(), allVertices.at(7).getY(), 0);
	glVertex3f(allVertices.at(6).getX(), allVertices.at(6).getY(), 0);

	glEnd();
}