#include "AnchoredSpring.hpp"

AnchoredSpring::AnchoredSpring(Particule * particule, Vector3D anchorPoint, float K, float length0)
{
	this->particule = particule;
	this->anchorPoint = anchorPoint;
	this->K = K;
	this->length0 = length0;
}

AnchoredSpring::~AnchoredSpring()
{

}


void AnchoredSpring::updateForce() 
{
	Vector3D delta = this->anchorPoint - this->particule->getPosition();
	Vector3D F = (delta / delta.norme()) * -1 * this->K * (delta.norme() - this->length0);

	this->particule->addForce(F);
}