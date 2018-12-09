#include "WorldRigidBody.hpp"

WorldRigidBody::WorldRigidBody()
{

}

void WorldRigidBody::addRigidBody(RigidBody* rigidbody)
{
	this->rigidbody.push_back(rigidbody);
}

std::vector<RigidBody*> WorldRigidBody::getRigidBody()
{
	return rigidbody;
}

std::vector<contactBroad> WorldRigidBody::getAllContactBroad(int nbDivideSpace)
{
	quadtree.divide(0, nbDivideSpace);
	std::vector<contactBroad> allContactBroad;
	contactBroad tmpContact;
	QuadTreeNode * finalLeaves = quadtree.getAllFinalLeaves();

	// pour chaque feuille finale
	for (int i = 0; i < pow(4.0, nbDivideSpace); i++)
	{
		// Si la feuilles contient 2 éléments ou plus
		if (finalLeaves[i].getNbContainedElements() >= 2)
		{
			// Pour chaque paire pair d'éléments possible dans la feuille on ajoute un contact broad
			for (int j = 0; j < finalLeaves[i].getNbContainedElements(); j++)
			{
				for (int k = j+1; k < finalLeaves[i].getNbContainedElements(); k++)
				{
					tmpContact.rb1 = finalLeaves[i].getContainedElements().at(j);
					tmpContact.rb2 = finalLeaves[i].getContainedElements().at(k);
					allContactBroad.push_back(tmpContact);
				}
			}
		}
	}

	return allContactBroad;
	
}

