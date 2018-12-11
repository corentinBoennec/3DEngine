#pragma once
#include "Tree\QuadtreeNode.hpp"

class QuadTree
{
private:
	std::vector<QuadTreeNode> nodes;
	std::vector<RigidBody> Elements;

public:
	QuadTree(QuadTreeNode firstNode, std::vector<RigidBody> Elements);
	QuadTree();
	std::vector<QuadTreeNode> getNodes();
	std::vector<QuadTreeNode> getFinalLeaves();
	std::vector<RigidBody> getElements();
	void divideSpaceNTime(int nbDivision);
	void divideNodeAtDepth(int depth);
	void addElement(RigidBody newElement);

};