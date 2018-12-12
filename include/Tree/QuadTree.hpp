#pragma once
#include "Tree\QuadtreeNode.hpp"

class QuadTree
{
private:
	std::vector<QuadTreeNode> nodes;
	std::vector<RigidBody> Elements;

public:
	QuadTree();

};