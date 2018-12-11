#include "Tree\QuadtreeNode.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

QuadTreeNode::QuadTreeNode(Plan plans[4])
{
	this->plans[0] = plans[0];
	this->plans[1] = plans[1];
	this->plans[2] = plans[2];
	this->plans[3] = plans[3];

	/*for (int i = 0; i < 4; i++)
	{
		this->leaves[i] = NULL;
	}*/
	this->gotChildren = false;
}

QuadTreeNode::QuadTreeNode()
{
	
}

QuadTreeNode::QuadTreeNode(Plan plans[4], std::vector<RigidBody> containedElements)
{
	this->plans[0] = plans[0];
	this->plans[1] = plans[1];
	this->plans[2] = plans[2];
	this->plans[3] = plans[3];
	for (int i = 0; i < containedElements.size(); i++)
	{
		this->containedElements.push_back(containedElements[i]);
	}
	/*for (int i = 0; i < 4; i++)
	{
		this->leaves[i] = NULL;
	}*/
	this->gotChildren = false;
	
}
QuadTreeNode::QuadTreeNode(QuadTreeNode * quadTree)
{
	this->plans[0] = quadTree->plans[0];
	this->plans[1] = quadTree->plans[1];
	this->plans[2] = quadTree->plans[2];
	this->plans[3] = quadTree->plans[3];
	for (int i = 0; i < quadTree->containedElements.size(); i++)
	{
		this->containedElements.push_back(quadTree->containedElements[i]);
	}
	if (quadTree->gotChildren)
	{
		for (int i = 0; i < 4; i++)
		{
			this->leaves[0] = quadTree->leaves[0];
			this->leaves[1] = quadTree->leaves[1];
			this->leaves[2] = quadTree->leaves[2];
			this->leaves[3] = quadTree->leaves[3];
		}
	}
	this->gotChildren = quadTree->gotChildren;
	
}
void QuadTreeNode::divide(/*int iteration, int maxIteration*/)
{
	//if (iteration < maxIteration)
	//{

		//on defini les 2/3 droites/plans qui coupe l'espace du QuadTreeNode/OctreeNode
		Plan midplanX = Plan((this->plans[0].getPosition() + this->plans[1].getPosition()) / 2, Vector3D(1,0,0));
		Plan midplanY = Plan((this->plans[2].getPosition() + this->plans[3].getPosition()) / 2, Vector3D(0,0,1));

		std::vector<RigidBody> containedElements1;
		std::vector<RigidBody> containedElements2;
		std::vector<RigidBody> containedElements3;
		std::vector<RigidBody> containedElements4;

		bool up;
		bool right;
		// On regarde dans quel feuille chaque élément doit allé en fonction de la position de son centre par rapport aux plan qui découpe l'expace
		for (int i = 0; i < this->getNbContainedElements(); i++)
		{	
			if (utils::distFromPlan(midplanX, containedElements.at(i).getCenterBoudingSphere()) > 0)
				right = true;
			else
				right = false;
			if (utils::distFromPlan(midplanY, containedElements.at(i).getCenterBoudingSphere()) > 0)
				up = true;
			else
				up = false;

			if (!right && up)
				containedElements1.push_back(this->containedElements.at(i));
			if (right && up)
				containedElements2.push_back(this->containedElements.at(i));
			if (right && !up)
				containedElements3.push_back(this->containedElements.at(i));
			if (!right && !up)
				containedElements4.push_back(this->containedElements.at(i));

		}

		//On construit un tableau de plan constituer des 4 cotés du noeud parents et des 2 plan coupant dans les 2 directions
		Plan tabPlans[6] = { midplanX, midplanY, plans[0], plans[1], plans[2], plans[3] };

		//On defini un tableau à double entrée qui dit si oui ou non pour chaque élément du noeud parents et chaque mur l'élement traverse le mur. 
		bool ** isWallCrossed = new bool*[getNbContainedElements()];
		for (int i = 0; i < getNbContainedElements(); i++)
		{
			isWallCrossed[i] = new bool[6];
		}

		//pour chaque élément du noued parents
		for (int i = 0; i < this->getNbContainedElements(); i++)
		{
			//pour chaque mur
			for (int j = 0; j < 6; j++)
			{
				//si la distance entre le mur et le centre du volume englobant est plus petite que le rayon du volume englobant
				

				if (fabs(utils::distFromPlan(tabPlans[j], containedElements.at(i).getCenterBoudingSphere())) < containedElements.at(i).getRadiusBoudingSphere())
				{
					//On dit que l'élément I traverse le mur J
					isWallCrossed[i][j] = true;
				}
				else
				{
					//sinon on dit qu'il ne le traverse pas
					isWallCrossed[i][j] = false;
				}
			}
		}

		//On défini les  4 noeuds fils
		//En définissant les 4 plans qui encadre leur espace et les éléments qui traversent leurs murs
		Plan plans1[4] = { midplanX, this->plans[1], this->plans[2], midplanY };
		for (int i = 0; i < this->getNbContainedElements(); i++)
		{
			if (utils::distFromPlan(midplanX, containedElements.at(i).getCenterBoudingSphere()) > 0)
				right = true;
			else
				right = false;
			if (utils::distFromPlan(midplanY, containedElements.at(i).getCenterBoudingSphere()) > 0)
				up = true;
			else
				up = false;
			// si un des mur qui compose ce noeud fils est traversé, l'objet est présent dans ce noeud. 
			// cette étape n'est pas parfaite, elle detecte certain cas qui pourrait peut être être évités
			if ((isWallCrossed[i][0]) || (isWallCrossed[i][1]) || (isWallCrossed[i][3]) || (isWallCrossed[i][4]))
			{
				//si l'element n'a pas déja été ajouter dans ce noeuds on l'ajoute
				if (std::find(containedElements1.begin(), containedElements1.end(), containedElements.at(i)) == containedElements1.end()) {
					containedElements1.push_back(containedElements.at(i));
				}
				//sinon il est deja présent
			}
		}
		
		


		Plan plans2[4] = { this->plans[0], midplanX, this->plans[2],  midplanY };
		for (int i = 0; i < this->getNbContainedElements(); i++)
		{
			// si un des mur qui compose ce noeud fils est traversé, l'objet est présent dans ce noeud.
			if (isWallCrossed[i][2] || isWallCrossed[i][0] || isWallCrossed[i][4] || isWallCrossed[i][1])
			{
				//si l'element n'a pas déja été ajouter dans ce noeuds on l'ajoute
				if (std::find(containedElements2.begin(), containedElements2.end(), containedElements.at(i)) == containedElements2.end()) {
					containedElements2.push_back(containedElements.at(i));
				}
				//sinon il est deja présent
			}
		}
		


		Plan plans3[4] = { this->plans[0], midplanX, midplanY,  this->plans[3] };
		for (int i = 0; i < this->getNbContainedElements(); i++)
		{
			// si un des mur qui compose ce noeud fils est traversé, l'objet est présent dans ce noeud.
			if (isWallCrossed[i][2] || isWallCrossed[i][0] || isWallCrossed[i][5] || isWallCrossed[i][1])
			{
				//si l'element n'a pas déja été ajouter dans ce noeuds on l'ajoute
				if (std::find(containedElements3.begin(), containedElements3.end(), containedElements.at(i)) == containedElements3.end()) {
					containedElements3.push_back(containedElements.at(i));
				}
				//sinon il est deja présent
			}
		}

		Plan plans4[4] = { midplanX, this->plans[1], midplanY,  this->plans[3] };
		for (int i = 0; i < this->getNbContainedElements(); i++)
		{
			// si un des mur qui compose ce noeud fils est traversé, l'objet est présent dans ce noeud.
			if (isWallCrossed[i][0] || isWallCrossed[i][1] || isWallCrossed[i][3] || isWallCrossed[i][5])
			{
				//si l'element n'a pas déja été ajouter dans ce noeuds on l'ajoute
				if (std::find(containedElements4.begin(), containedElements4.end(), containedElements.at(i)) == containedElements4.end()) {
					containedElements4.push_back(containedElements.at(i));
				}
				//sinon il est deja présent
			}
		}

		
		// On crée les noeuds fils
		QuadTreeNode * leaf1 = new QuadTreeNode(plans1, containedElements1);
		QuadTreeNode * leaf2 = new QuadTreeNode(plans2, containedElements2);
		QuadTreeNode * leaf3 = new QuadTreeNode(plans3, containedElements3);
		QuadTreeNode * leaf4 = new QuadTreeNode(plans4, containedElements4);

		//On efface la mémoire alloué à notre tableau mur/éléments
		for (int i = 0; i < getNbContainedElements(); i++)
		{
			delete(isWallCrossed[i]);
		}
		delete(isWallCrossed);

		QuadTreeNode * tmpLeaves = new QuadTreeNode[4];
		tmpLeaves[0] = leaf1;
		tmpLeaves[1] = leaf2;
		tmpLeaves[2] = leaf3;
		tmpLeaves[3] = leaf4;

		//on ajoute a notre noeuds parents ses 4 fils
		this->addLeaves(tmpLeaves);
		
		/*for (int i = 0; i < 4; i++)
		{
			leaves[i]->divide(iteration + 1, maxIteration);

		}	*/	

		//delete(tmpLeaves);
}


void QuadTreeNode::addLeaves(QuadTreeNode leaves[4])
{
	this->leaves = new QuadTreeNode[4];
	this->leaves[0] = new QuadTreeNode(leaves[0]);
	this->leaves[1] = new QuadTreeNode(leaves[1]);
	this->leaves[2] = new QuadTreeNode(leaves[2]);
	this->leaves[3] = new QuadTreeNode(leaves[3]);
	this->gotChildren = true;

}

int QuadTreeNode::getNbContainedElements()
{
	return this->containedElements.size();
}

std::vector<RigidBody> QuadTreeNode::getContainedElements()
{
	return this->containedElements;
}

/*void QuadTreeNode::printTree()
{
	//afficher le nombre d'élément de ce noeud
	std::cout << this->getNbContainedElements() << std::endl;
	std::cout << "enfant" << this->gotChildren << std::endl;
	if (this->gotChildren)
	{
		for (int i = 0; i < 4; i++)
		{
			leaves[i]->printTree();
		}
	}
	
}

std::vector<QuadTreeNode> QuadTreeNode::getAllFinalLeaves()
{
	std::vector<QuadTreeNode> finalLeaves;
	if (this->gotChildren)
	{
		for (int i = 0; i < 4; i++)
		{
			finalLeaves.insert(finalLeaves.end(), this->leaves[i]->getAllFinalLeaves().begin(), this->leaves[i]->getAllFinalLeaves().end()); 
		}
	}
	return finalLeaves;
}

std::vector<QuadTreeNode> QuadTreeNode::getAllFinalLeaves2()
{
	std::vector<QuadTreeNode> finalLeaves;

	for (int i = 0; i < 4; i++)
	{
		
		for (int j = 0; j < 4; j++)
		{
			finalLeaves.push_back(leaves[i]->leaves[j]);
		}
	}
	return finalLeaves;
}

std::vector<QuadTreeNode> QuadTreeNode::getAllFinalLeaves3()
{
	std::vector<QuadTreeNode> finalLeaves;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				finalLeaves.push_back(leaves[i].leaves[j]->leaves[k]);
			}
		}
	}
	return finalLeaves;
}*/

void QuadTreeNode::addElement(RigidBody element)
{
	this->containedElements.push_back(element);
}

QuadTreeNode * QuadTreeNode::getLeaves()
{
	return leaves;
}

bool QuadTreeNode::doGotChildren()
{
	return gotChildren;
}

