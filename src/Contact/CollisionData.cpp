#include "Contact/CollisionData.hpp"

CollisionData::CollisionData(int nbMaxContact)
{
	this->contactRestant = nbMaxContact;
}

CollisionData::~CollisionData(){}

void CollisionData::addContact(Contact * contact)
{
	this->contacts.push_back(contact);
}

void CollisionData::printData()
{
	if (this->contacts.size() > 0)
	{
		for (int i = 0; i < this->contacts.size(); i++)
		{
			std::cout << "Contact n°" << i << " : Point de contact > (" << this->contacts[i]->getContactPoint().getX() << ", " << this->contacts[i]->getContactPoint().getY() << ", " << this->contacts[i]->getContactPoint().getZ() << ") - Normal > (" << this->contacts[i]->getContactNormal().getX() << ", " << this->contacts[i]->getContactNormal().getY() << ", " << this->contacts[i]->getContactNormal().getZ() << ") - Interpénétration > " << this->contacts[i]->getInterpenetration() << std::endl;
		}
	}
}

std::vector<Contact*> CollisionData::getContacts()
{
	return this->contacts;
}

int CollisionData::getContactRestant()
{
	return this->contactRestant;
}
