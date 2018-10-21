#include "worldParticles.hpp"

worldParticles::worldParticles()
{

}

void worldParticles::addParticle(Particule * particule)
{
	this->particles.push_back(particule);
}

std::vector<ParticleContact> worldParticles::getAllContact()
{
	// coeff de restitution "le m�me pour tous" pour le moment
	float restitution = 0.8f;

	std::vector<ParticleContact> contacts;
	for (int i = 0; i < particles.size() ; i++)
	{
		for (int j = 0; j < particles.size() ; j++)
		{
			// si la distance entre les particules est inferieur � la somme de leurs rayons. Et que les 2 particules ne sont pas une seule et m�me particule.
			// On demande aussi i < j pour annuler les doublons de collisions
			if (((particles[i]->getPosition().distance(particles[j]->getPosition())) < (particles[i]->getRadius() + particles[j]->getRadius())) && i < j)
			{
				// alors on � une collision
				Particule * tabPart[2] = { particles[i], particles[j] };
				ParticleContact contact(tabPart, restitution );
				contacts.push_back(contact);
			}
		}
	}

	return contacts;
}

std::vector<Particule*> worldParticles::getParticles()
{
	return particles;
}