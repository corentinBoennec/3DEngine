#include "WorldRigidBody.hpp"

WorldRigidBody::WorldRigidBody()
{
	
}

WorldRigidBody::WorldRigidBody(QuadTreeNode node, std::vector<RigidBody> rigidBodies)
{
	this->quadTree = QuadTree(node, rigidBodies);
	this->rigidBodies = rigidBodies;
}

void WorldRigidBody::addRigidBody(RigidBody rigidbody)
{
	this->rigidBodies.push_back(rigidbody);
	quadTree.addElement(rigidbody);
}

std::vector<RigidBody> WorldRigidBody::getRigidBody()
{
	return rigidBodies;
}

std::vector<contactBroad> WorldRigidBody::getAllContactBroad(int nbDivideSpace)
{
	// on divise l'espace le nombre de fois demandé.
	quadTree.divideSpaceNTime(nbDivideSpace);
	std::vector<contactBroad> allContactBroad;
	std::vector<QuadTreeNode> finalLeaves;
	contactBroad tmpContact;
	finalLeaves = quadTree.getFinalLeaves();
	std::cout << finalLeaves.size() << std::endl;
	// pour chaque feuille finale
	for (int i = 0; i < finalLeaves.size(); i++)
	{
		// Si la feuilles contient 2 éléments ou plus
		if (finalLeaves.at(i).getNbContainedElements() >= 2)
		{
			// Pour chaque paire pair d'éléments possible dans la feuille on ajoute un contact broad
			for (int j = 0; j < finalLeaves.at(i).getNbContainedElements(); j++)
			{
				for (int k = j+1; k < finalLeaves.at(i).getNbContainedElements(); k++)
				{
					tmpContact.rb1 = finalLeaves.at(i).getContainedElements().at(j);
					tmpContact.rb2 = finalLeaves.at(i).getContainedElements().at(k);
					allContactBroad.push_back(tmpContact);
				}
			}
		}
	}

	return allContactBroad;
	
}

