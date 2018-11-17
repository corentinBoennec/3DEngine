#include "Contact/ParticleContactResolver.hpp"

ParticleContactResolver::ParticleContactResolver()
{
	this->maxIteration = 0;
	this->iterationCount = 0;
}

void ParticleContactResolver::setIterations(ParticleContact * contact)
{
	// On insert le nouveau contact dans la liste pour que celle ci soit triée par ordre croissant
	// Selon les vitesse d'eloignements.
	int i = 0;
	while (i < contacts.size() && contacts[i].computeVs() > contact->computeVs())
	{
		i++;
	}
	contacts.insert(contacts.begin() + i, *contact);

	// On augmente de 1 le nombre de contact et on actualise le nombre max de collisions à calculer.
	this->iterationCount += 1;
	this->maxIteration = 2 * iterationCount;
}

void ParticleContactResolver::resolveContact(float timeFrame)
{
	//on resoud tout les contacts. (pourrait être mieux géré pour pouvoir acceuillir les nouveaux contacts générés par la résolution des premiers.)
	std::vector<ParticleContact>::iterator it;
	it = contacts.begin();
	int i = 0;
	while ((it != contacts.end()) && (i != maxIteration) )
	{
		contacts[i].resolve(timeFrame);
		i++;
		it++;
	}
}