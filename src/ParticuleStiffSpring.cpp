#include "ParticuleStiffSpring.hpp"

ParticuleStiffString::ParticuleStiffString(Vector3D anchor, float k, float damp)
{
	this->anchor = anchor;
	this->k = k;
	this->damp = damp;
}

ParticuleStiffString::~ParticuleStiffString(){}

void ParticuleStiffString::updateForce(Particule particule)
{
	Vector3D acceleration = particule.getPosition() * (-1) - particule.getVelocity() * damp;
	Vector3D F = acceleration * particule.getMass();
	particule.addForce(F);
}
