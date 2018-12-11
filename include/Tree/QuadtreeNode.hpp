#pragma once
#include "RigidBody.hpp"
#include "Plan.hpp"
#include <vector>
#include "Functions.hpp"

class QuadTreeNode
{
private:
	QuadTreeNode * leaves;
	std::vector<RigidBody> containedElements;
	 // right / left / top / Bottom
	Plan plans[4];
	bool gotChildren;


public:
	QuadTreeNode();
	QuadTreeNode(Plan plans[4]);
	QuadTreeNode(Plan plans[4], std::vector<RigidBody> containedElements);
	QuadTreeNode(QuadTreeNode * quadTree);
	void divide(/*int iteration, int maxIteration*/);
	void addLeaves(QuadTreeNode leaves[4]);
	int getNbContainedElements();
	std::vector<RigidBody> getContainedElements();
	void printTree();
	std::vector<QuadTreeNode> getAllFinalLeaves();
	std::vector<QuadTreeNode> getAllFinalLeaves2();
	std::vector<QuadTreeNode> getAllFinalLeaves3();
	void addElement(RigidBody element);
	bool doGotChildren();
	QuadTreeNode * getLeaves();
};