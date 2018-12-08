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

	for (int i = 0; i < 4; i++)
	{
		this->leaves[i] = NULL;
	}
	this->gotChildren = false;
}

QuadTreeNode::QuadTreeNode()
{
	
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
	for (int i = 0; i < 4; i++)
	{
		this->leaves[i] = NULL;
	}
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
	if (quadTree->leaves[0] != NULL)
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
void QuadTreeNode::divide(int iteration, int maxIteration)
{
	if (iteration < maxIteration)
	{

		//on defini les 2/3 droites/plans qui coupe l'espace du QuadTreeNode/OctreeNode
		Plan midplanX = Plan((this->plans[0].getPosition() + this->plans[1].getPosition()) / 2, Vector3D(1,0,0));
		Plan midplanY = Plan((this->plans[2].getPosition() + this->plans[3].getPosition()) / 2, Vector3D(0,0,1));

		std::vector<RigidBody*> containedElements1;
		std::vector<RigidBody*> containedElements2;
		std::vector<RigidBody*> containedElements3;
		std::vector<RigidBody*> containedElements4;


		// On regarde dans quel feuille chaque �l�ment doit all� en fonction de la position de son centre par rapport aux plan qui d�coupe l'expace
		for (int i = 0; i < this->getNbContainedElements(); i++)
		{
			bool up;
			bool right;
			if (utils::distFromPlan(midplanX, containedElements.at(i)->getCenterBoudingSphere()) > 0)
				right = true;
			else
				right = false;
			if (utils::distFromPlan(midplanY, containedElements.at(i)->getCenterBoudingSphere()) > 0)
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

		//On construit un tableau de plan constituer des 4 cot�s du noeud parents et des 2 plan coupant dans les 2 directions
		Plan tabPlans[6] = { midplanX, midplanY, plans[0], plans[1], plans[2], plans[3] };

		//On defini un tableau � double entr�e qui dit si oui ou non pour chaque �l�ment du noeud parents et chaque mur l'�lement traverse le mur. 
		bool ** isWallCrossed = new bool*[getNbContainedElements()];
		for (int i = 0; i < getNbContainedElements(); i++)
		{
			isWallCrossed[i] = new bool[6];
		}

		//pour chaque �l�ment du noued parents
		for (int i = 0; i < this->getNbContainedElements(); i++)
		{
			//pour chaque mur
			for (int j = 0; j < 6; j++)
			{
				//si la distance entre le mur et le centre du volume englobant est plus petite que le rayon du volume englobant
				

				if (fabs(utils::distFromPlan(tabPlans[j], containedElements.at(i)->getCenterBoudingSphere())) < containedElements.at(i)->getRadiusBoudingSphere())
				{
					//On dit que l'�l�ment I traverse le mur J
					isWallCrossed[i][j] = true;
				}
				else
				{
					//sinon on dit qu'il ne le traverse pas
					isWallCrossed[i][j] = false;
				}
			}
		}

		//On d�fini les  4 noeuds fils
		//En d�finissant les 4 plans qui encadre leur espace et les �l�ments qui traversent leurs murs
		Plan plans1[4] = { midplanX, this->plans[1], this->plans[2], midplanY };
		for (int i = 0; i < this->getNbContainedElements(); i++)
		{
			// si un des mur qui compose ce noeud fils est travers�, l'objet est pr�sent dans ce noeud.
			if (isWallCrossed[i][0] || isWallCrossed[i][1] || isWallCrossed[i][3] || isWallCrossed[i][4])
			{
				//si l'element n'a pas d�ja �t� ajouter dans ce noeuds on l'ajoute
				if (std::find(containedElements1.begin(), containedElements1.end(), containedElements.at(i)) == containedElements1.end()) {
					containedElements1.push_back(containedElements.at(i));
				}
				//sinon il est deja pr�sent
			}
		}
		
		


		Plan plans2[4] = { this->plans[0], midplanX, this->plans[2],  midplanY };
		for (int i = 0; i < this->getNbContainedElements(); i++)
		{
			// si un des mur qui compose ce noeud fils est travers�, l'objet est pr�sent dans ce noeud.
			if (isWallCrossed[i][2] || isWallCrossed[i][0] || isWallCrossed[i][4] || isWallCrossed[i][1])
			{
				//si l'element n'a pas d�ja �t� ajouter dans ce noeuds on l'ajoute
				if (std::find(containedElements2.begin(), containedElements2.end(), containedElements.at(i)) == containedElements2.end()) {
					containedElements2.push_back(containedElements.at(i));
				}
				//sinon il est deja pr�sent
			}
		}
		


		Plan plans3[4] = { this->plans[0], midplanX, midplanY,  this->plans[3] };
		for (int i = 0; i < this->getNbContainedElements(); i++)
		{
			// si un des mur qui compose ce noeud fils est travers�, l'objet est pr�sent dans ce noeud.
			if (isWallCrossed[i][2] || isWallCrossed[i][0] || isWallCrossed[i][5] || isWallCrossed[i][1])
			{
				//si l'element n'a pas d�ja �t� ajouter dans ce noeuds on l'ajoute
				if (std::find(containedElements3.begin(), containedElements3.end(), containedElements.at(i)) == containedElements3.end()) {
					containedElements3.push_back(containedElements.at(i));
				}
				//sinon il est deja pr�sent
			}
		}

		Plan plans4[4] = { midplanX, this->plans[1], midplanY,  this->plans[3] };
		for (int i = 0; i < this->getNbContainedElements(); i++)
		{
			// si un des mur qui compose ce noeud fils est travers�, l'objet est pr�sent dans ce noeud.
			if (isWallCrossed[i][0] || isWallCrossed[i][1] || isWallCrossed[i][3] || isWallCrossed[i][5])
			{
				//si l'element n'a pas d�ja �t� ajouter dans ce noeuds on l'ajoute
				if (std::find(containedElements4.begin(), containedElements4.end(), containedElements.at(i)) == containedElements4.end()) {
					containedElements4.push_back(containedElements.at(i));
				}
				//sinon il est deja pr�sent
			}
		}

		
		// On cr�e les noeuds fils
		QuadTreeNode * leaf1 = new QuadTreeNode(plans1, containedElements1);
		QuadTreeNode * leaf2 = new QuadTreeNode(plans2, containedElements2);
		QuadTreeNode * leaf3 = new QuadTreeNode(plans3, containedElements3);
		QuadTreeNode * leaf4 = new QuadTreeNode(plans4, containedElements4);

		//On efface la m�moire allou� � notre tableau mur/�l�ments
		for (int i = 0; i < getNbContainedElements(); i++)
		{
			delete(isWallCrossed[i]);
		}
		delete(isWallCrossed);

		//on ajoute a notre noeuds parents ses 4 fils
		QuadTreeNode * leaves[4];
		leaves[0] = leaf1;
		leaves[1] = leaf2;
		leaves[2] = leaf3;
		leaves[3] = leaf4;

		this->addLeaves(leaves);
		
		for (int i = 0; i < 4; i++)
		{
			leaves[i]->divide(iteration + 1, maxIteration);

		}		

		for (int i = 0; i < 4; i++)
		{
			delete(leaves[i]);
		}
	}
}

void QuadTreeNode::addLeaves(QuadTreeNode * leaves[4])
{
	/* NOTE */ //impl�mentation douteuse sans doute mieux a faire.
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

std::vector<RigidBody*> QuadTreeNode::getContainedElements()
{
	return this->containedElements;
}

void QuadTreeNode::printTree()
{
	//afficher le nombre d'�l�ment de ce noeud
	std::cout << this->getNbContainedElements() << std::endl;
	std::cout << "enfant" << this->gotChildren << std::endl;
	if (this->gotChildren)
	{
		for (int i = 0; i < 4; i++)
		{
			leaves[i]->printTree();
		}
	}
	
	//si ses fils ne sont pas vide
	/*if (this->gotChildren == true)
	{
		for (int i = 0; i < 4; i++)
		{
			this->leaves[i]->printTree();
		}
	}*/
		//lancer pour les fils
}

