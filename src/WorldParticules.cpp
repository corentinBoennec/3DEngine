#include "WorldParticules.hpp"

WorldParticules::WorldParticules()
{
}

void WorldParticules::addParticle(Particule * particule)
{
	this->particles.push_back(particule);
}

std::vector<ParticleContact> WorldParticules::getAllContact()
{
	// coeff de restitution "le même pour tous" pour le moment
	float restitution = 0.8f;

	std::vector<ParticleContact> contacts;
	for (int i = 0; i < particles.size(); i++)
	{
		for (int j = 0; j < particles.size(); j++)
		{
			// si la distance entre les particules est inferieur à la somme de leurs rayons. Et que les 2 particules ne sont pas une seule et même particule.
			// On demande aussi i < j pour annuler les doublons de collisions
			if (((particles[i]->getPosition().distance(particles[j]->getPosition())) < (particles[i]->getRadius() + particles[j]->getRadius())) && i < j)
			{
				// alors on à une collision
				Particule * tabPart[2] = { particles[i], particles[j] };
				ParticleContact contact(tabPart, restitution);
				contacts.push_back(contact);
			}
		}
	}

	return contacts;
}

std::vector<Particule*> WorldParticules::getParticles()
{
	return particles;
}