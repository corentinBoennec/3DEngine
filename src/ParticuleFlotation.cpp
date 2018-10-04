#include "ParticuleFlotation.hpp"

ParticuleFlotation::ParticuleFlotation(Particule * particule, float maxDepth, float ObjectVolume, float liquidLevel, float liquidDensity, float totalImmertion)
{
	this->particule = particule;
	this->maxDepth = maxDepth;
	this->ObjectVolume = ObjectVolume;
	this->liquidLevel = liquidLevel;
	this->liquidDensity = liquidDensity;
	this->totalImmertion = totalImmertion;
}

void ParticuleFlotation::updateForce()
{
	float immertion = (particule->getPosition().getZ() - this->liquidLevel - this->totalImmertion) / 2 * this->totalImmertion;
	Vector3D F;
	if (immertion <= 0)
	{
		F = Vector3D(0, 0, 0);
	}
	else if (immertion >= 1)
	{
		F = Vector3D(0, 0, 1) * this->ObjectVolume * this->liquidDensity;
	}
	else
	{
		F = Vector3D(0, 0, 1) * this->ObjectVolume * this->liquidDensity * immertion;
	}

	particule->addForce(F);
}