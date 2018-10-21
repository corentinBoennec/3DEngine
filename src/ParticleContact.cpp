#include "ParticleContact.hpp"

ParticleContact::ParticleContact(Particule * particule[2], float restitution)
{
	this->particule[0] = particule[0];
	this->particule[1] = particule[1];

	this->restitution = restitution;
	this->normal = (particule[0]->getPosition() - particule[1]->getPosition()).unit();
	if ((particule[0]->getRadius() + particule[1]->getRadius() - (particule[0]->getPosition() - particule[1]->getPosition()).norme()) > 0) // on test si la somme des rayons des particules est sup�rieur a la distance qui s�pare leurs centre. 
	{																																		//Si c'est le cas, la diff�rence devient la valeur de l'interp�n�tration. Sinon il n'y a pas d'interp�n�tration
		penetration = (particule[0]->getRadius() + particule[1]->getRadius() - (particule[0]->getPosition() - particule[1]->getPosition()).norme());
	}
	else
	{
		penetration = 0;
	}

}

void ParticleContact::resolve(float duration)
{
	this->resolveImpulsion();
	this->resolveInterPenetration();
}

void ParticleContact::resolveImpulsion()
{
	if ((particule[0]->getVelocity() * normal) > 0)   // si la particule [0] est dans la m�me direction que la normal on la renvoi dans le sens inverse de la normale apr�s collision. 
	{													//Sinon dans le sens oppos�. (on test cette direction � l'aide du signe du r�sultat du produit scalaire de la norme par la velocit�).
		particule[0]->setVelocity(normal * restitution * computeVs() * -1);
		particule[1]->setVelocity(normal * restitution * computeVs());
	}
	else
	{
		particule[0]->setVelocity(normal * restitution * computeVs());
		particule[1]->setVelocity(normal * restitution * computeVs() * -1);
	}
}

void ParticleContact::resolveInterPenetration()
{
	float coeff0 = particule[0]->getMass() / (particule[0]->getMass() + particule[1]->getMass());  // coefficient pour pond�rer le d�placement en fonction de la masse des objets
	float coeff1 = 1 - coeff0;
	if ((particule[0]->getVelocity() * normal) > 0)  // on test la direction d'ou vient la particule par rapport a la norme de fa�on � la renvoyer dans la direction oppos� grace a un produit scalaire dont on test le signe
	{
		particule[0]->setPosition(particule[0]->getPosition() + (normal * penetration * coeff0 * -1));
		particule[1]->setPosition(particule[1]->getPosition() + (normal * penetration * coeff1));
	}
	else
	{
		particule[0]->setPosition(particule[0]->getPosition() + (normal * penetration * coeff0));
		particule[1]->setPosition(particule[1]->getPosition() + (normal * penetration * coeff1 * -1));
	}

}

float ParticleContact::computeVs()
{
	return ( (this->particule[0]->getVelocity() - this->particule[1]->getVelocity()) * ((this->particule[0]->getPosition() - this->particule[1]->getPosition()).unit()) );
}