#include "Tree\QuadtreeNode.hpp"

QuadTreeNode::QuadTreeNode(Plan plans[4])
{
	this->plans[0] = plans[0];
	this->plans[1] = plans[1];
	this->plans[2] = plans[2];
	this->plans[3] = plans[3];
}

QuadTreeNode::QuadTreeNode(Plan plans[4], std::vector<RigidBody*> containedElements)
{
	this->plans[0] = plans[0];
	this->plans[1] = plans[1];
	this->plans[2] = plans[2];
	this->plans[3] = plans[3];
	for (int i = 0; i < containedElements.size(); i++)
	{
		this->containedElements.push_back(containedElements[i]);
	}
	this->leaves = NULL;
	
}
void QuadTreeNode::divide()
{
	Plan midplanX = Plan((this->plans[0].getPosition() + this->plans[1].getPosition()) / 2, this->plans[0].getDirection());
	Plan midplanY = Plan((this->plans[2].getPosition() + this->plans[3].getPosition()) / 2, this->plans[0].getDirection());

	// fill all containedElements comparing the distance between all of their walls and the Elements with the elements radius
	Plan tabPlans[6] = { midplanX, midplanY, plans[0], plans[1], plans[2], plans[3] };
	int nb = getNbContainedElements();
	bool ** isWallCrossed = new bool*[nb];
	for (int i = 0; i < nb; i++)
	{
		isWallCrossed[i] = new bool[6];
	}
	for (int i = 0; i < this->getNbContainedElements(); i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (utils::distFromPlan(tabPlans[j], containedElements.at(i)->/* recupère le centre volume englobant*/) < containedElements.at(i)->/* recupère le radius du volume englobant*/)
			{
				isWallCrossed[j] = true;
			}
			else
			{
				isWallCrossed[j] = false;
			}
		}
	}

	Plan plans1[4] = { midplanX, this->plans[1], this->plans[2], midplanY };
	std::vector<RigidBody*> containedElements1;
	for (int i = 0; i < this->getNbContainedElements(); i++)
	{
		if (isWallCrossed[i][0] || isWallCrossed[i][1] || isWallCrossed[i][3] || isWallCrossed[i][4])
		{
			containedElements1.push_back(containedElements.at(i));
		}
	}
	QuadTreeNode leaf1 = QuadTreeNode(plans1, containedElements1);

	Plan plans2[4] = { this->plans[0], midplanX, this->plans[2],  midplanY };
	std::vector<RigidBody*> containedElements2;
	for (int i = 0; i < this->getNbContainedElements(); i++)
	{
		if (isWallCrossed[i][0] || isWallCrossed[i][1] || isWallCrossed[i][3] || isWallCrossed[i][4])
		{
			containedElements1.push_back(containedElements.at(i));
		}
	}

	QuadTreeNode leaf2 = QuadTreeNode(plans2);
	Plan plans3[4] = { this->plans[0], midplanX, midplanY,  this->plans[3]};
	std::vector<RigidBody*> containedElements3;
	//fill here

	QuadTreeNode leaf3 = QuadTreeNode(plans3);
	Plan plans4[4] = { midplanX, this->plans[1], midplanY,  this->plans[3] };
	std::vector<RigidBody*> containedElements4;
	//fill here

	QuadTreeNode leaf4 = QuadTreeNode(plans4);


	this->addLeaf(leaf1);
	this->addLeaf(leaf2);
	this->addLeaf(leaf3);
	this->addLeaf(leaf4);
	 
}

void QuadTreeNode::addLeaf(QuadTreeNode leaf)
{

}

int QuadTreeNode::getNbContainedElements()
{
	return this->containedElements.size();
}

std::vector<RigidBody*> QuadTreeNode::getContainedElements()
{
	return this->containedElements;
}