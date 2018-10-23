#include "ParticleContact.hpp"

ParticleContact::ParticleContact(Particule * particule[2], float restitution)
{
	this->particule[0] = particule[0];
	this->particule[1] = particule[1];

	this->restitution = restitution;
	this->normal = (particule[0]->getPosition() - particule[1]->getPosition()).unit();
	if (particule[0]->getRadius() + particule[1]->getRadius() - (particule[0]->getPosition().distance(particule[1]->getPosition())) > 0) // on test si la somme des rayons des particules est sup�rieur a la distance qui s�pare leurs centre. 
	{																																		//Si c'est le cas, la diff�rence devient la valeur de l'interp�n�tration. Sinon il n'y a pas d'interp�n�tration
		penetration = (particule[0]->getRadius() + particule[1]->getRadius() - (particule[0]->getPosition().distance(particule[1]->getPosition())));
	}
	else
	{
		penetration = 0;
	}

}

void ParticleContact::resolve(float duration)
{
	this->resolveInterPenetration();
	this->resolveImpulsion();

}

void ParticleContact::resolveImpulsion()
{
	float Vs = computeVs();
		particule[0]->setVelocity(normal * restitution * Vs);
		particule[1]->setVelocity(normal * restitution * Vs * -1);
}

void ParticleContact::resolveInterPenetration()
{

	float coeff0 = particule[0]->getMass() / (particule[0]->getMass() + particule[1]->getMass());  // coefficient pour pond�rer le d�placement en fonction de la masse des objets
	float coeff1 = 1 - coeff0;
	
	particule[0]->setPosition(particule[0]->getPosition() + (normal * (penetration * coeff0 )));
	particule[1]->setPosition(particule[1]->getPosition() + (normal * (penetration * coeff1 * -1)));
	

}

float ParticleContact::computeVs()
{
	// cette valeur doit �tre positive, elle designe une vitesse
	float velocity = (this->particule[0]->getVelocity() - this->particule[1]->getVelocity()) * normal;
	if (velocity >= 0)
		return velocity;
	else
		return (-velocity);
}