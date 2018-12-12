#pragma once

#include "Primitive.hpp"

#include <vector>

class Box : public Primitive
{
private:
	Vector3D halfSizes; // contient la longueur des trois semi côté
	std::vector<Vector3D> allVertices;

public:
	Box(Vector3D halfSizes, RigidBody* rigidbody);
	Box();
	~Box();
	std::vector<Vector3D> getAllVertices();
	void findVertices(); // Il faut utiliser la Matrix Offset normalement
	void printAllVertices();
	void DrawBox();
};