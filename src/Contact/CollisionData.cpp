#include "Contact/CollisionData.hpp"

CollisionData::CollisionData(int nbMaxContact)
{
	this->contactRestant = nbMaxContact;
}

CollisionData::~CollisionData() {}

void CollisionData::addContact(Contact * contact)
{
	this->contacts.push_back(contact);
}

std::vector<Contact*> CollisionData::getContacts()
{
	return this->contacts;
}

int CollisionData::getContactRestant()
{
	return this->contactRestant;
}