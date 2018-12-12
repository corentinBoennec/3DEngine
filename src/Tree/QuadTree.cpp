#include "Tree\QuadTree.hpp"

QuadTree::QuadTree(QuadTreeNode firstNode, std::vector<RigidBody*> Elements)
{
	this->nodes.push_back(firstNode);
	for each (RigidBody* r in Elements)
	{
		this->Elements.push_back(r);
	}
}
QuadTree::QuadTree()
{
}

void QuadTree::cleanQuadTree()
{
	this->nodes.at(0).destroyQuadTreeNode();
}

std::vector<QuadTreeNode> QuadTree::getNodes()
{
	return this->nodes;
}
std::vector<QuadTreeNode> QuadTree::getFinalLeaves()
{
	std::vector<QuadTreeNode> finalLeaves;
	for each (QuadTreeNode n in nodes)
	{
		if (!n.doGotChildren())
			finalLeaves.push_back(n);
	}
	return finalLeaves;
}
std::vector<RigidBody*> QuadTree::getElements()
{
	return this->Elements;
}
void QuadTree::divideSpaceNTime(int nbDivision)
{
	for (int i = 0; i < nbDivision; i++)
	{
		divideNodeAtDepth(i);
	}
}

void QuadTree::divideNodeAtDepth(int depth)
{
	int begin = 0;
	for (int i = 0; i <= depth - 1; i++)
	{
		begin += (int)pow(4, i);
	}
	int currentNbFeuilles = nodes.size();
	for (int i = begin; i < currentNbFeuilles; i++) //de la dernieres feuilles de la profondeurs précédente
	{
		if (nodes.at(i).getNbContainedElements() > 0)
		{
			nodes.at(i).divide();
			for (int j = 0; j < 4; j++)
			{
				this->nodes.push_back(nodes.at(i).getLeaves()[j]);
			}
		}
	}
}

void QuadTree::addElement(RigidBody * newElement)
{
	this->Elements.push_back(newElement);
}