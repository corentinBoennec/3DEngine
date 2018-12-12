#pragma once

#include "RigidBody.hpp"
#include "Tree\Quadtree.hpp"
#include <vector>
#include <math.h> 

struct contactBroad {
	RigidBody * rb1;
	RigidBody * rb2;
};


class WorldRigidBody
{
private:
	std::vector<RigidBody*> rigidBodies;
	QuadTree quadTree;

	
public:

	WorldRigidBody();
	WorldRigidBody(QuadTreeNode node, std::vector<RigidBody*> rigidBodies);
	std::vector<RigidBody*> getRigidBody();
	void addRigidBody(RigidBody * rigidbody);
	std::vector<contactBroad> getAllContactBroad(int nbDivideSpace);
};