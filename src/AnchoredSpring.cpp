#include "AnchoredSpring.hpp"

AnchoredSpring::AnchoredSpring(Vector3D anchorPoint, float K, float length0)
{
	this->anchorPoint = anchorPoint;
	this->K = K;
	this->length0 = length0;
}

AnchoredSpring::~AnchoredSpring()
{

}


void AnchoredSpring::updateForce(Particule* particule, float timeFrame) 
{
	Vector3D delta = this->anchorPoint - particule->getPosition();
	Vector3D F = (delta / delta.norme()) * -1 * this->K * (delta.norme() - this->length0);
	particule->addForce(F * (timeFrame / 1000));
}