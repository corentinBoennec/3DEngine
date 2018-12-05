#include "RigidBody.hpp"
#include "Plan.hpp"
#include <vector>

class QuadTreeNode
{
private:
	QuadTreeNode * leaves;
	std::vector<RigidBody*> containedElements;
	 // right / left / top / Bottom
	Plan plans[4];


public:
	QuadTreeNode();
	QuadTreeNode(Plan plans[4]);
	QuadTreeNode(Plan plans[4], std::vector<RigidBody*> containedElements);
	void divide();
	void addLeaf(QuadTreeNode leaf);
	int getNbContainedElements();
	RigidBody * getContainedElements();
	

};