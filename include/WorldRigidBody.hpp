#pragma once

#include "RigidBody.hpp"
#include "Tree\QuadtreeNode.hpp"
#include <vector>
#include <math.h> 

struct contactBroad {
	RigidBody rb1;
	RigidBody rb2;
};


class WorldRigidBody
{
private:
	std::vector<RigidBody*> rigidbody;
	QuadTreeNode quadtree;

	
public:

	WorldRigidBody();
	std::vector<RigidBody*> getRigidBody();
	void addRigidBody(RigidBody * rigidbody);
	std::vector<contactBroad> getAllContactBroad(int nbDivideSpace);
};