#include "Forces/RegistreForceRigidBody.hpp"

RegistreForceRigidBody::RegistreForceRigidBody() {}

RegistreForceRigidBody::~RegistreForceRigidBody() {}


void RegistreForceRigidBody::update(float timeFrame)
{
	for (auto eF : this->registre)
	{
		eF.forceGenerator->updateForce(eF.particule, timeFrame);
	}
}

void RegistreForceRigidBody::add(RigidBody* particule, RigidBodyForceGenerator* forceGenerator)
{
	EnregistrementForce eF;
	eF.particule = particule;
	eF.forceGenerator = forceGenerator;
	this->registre.push_back(eF);
}

void RegistreForceRigidBody::suppr(int index)
{
	this->registre.erase(registre.begin() + index);
}

void RegistreForceRigidBody::cleanRegistre()
{
	this->registre.clear();
}

int RegistreForceRigidBody::count()
{
	return (int)this->registre.size();
}