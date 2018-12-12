#pragma once

#include "Contact/Contact.hpp"

#include <vector>

class CollisionData
{
public:
	CollisionData(int nbMaxContact);
	~CollisionData();
	void addContact(Contact* contact);
	std::vector<Contact*> getContacts();
	int getContactRestant();

private:
	std::vector<Contact*> contacts; //Table des contacts réels
	int contactRestant; //Nb max de contact
};