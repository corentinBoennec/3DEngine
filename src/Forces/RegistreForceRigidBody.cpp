#include "Forces/RegistreForceRigidBody.hpp"

RegistreForce::RegistreForce() {}

RegistreForce::~RegistreForce() {}


void RegistreForce::update(float timeFrame)
{
	for (auto eF : this->registre)
	{
		eF.forceGenerator->updateForce(eF.particule, timeFrame);
	}
}

void RegistreForce::add(RigidBody* particule, RigidBodyForceGenerator* forceGenerator)
{
	EnregistrementForce eF;
	eF.particule = particule;
	eF.forceGenerator = forceGenerator;
	this->registre.push_back(eF);
}

void RegistreForce::suppr(int index)
{
	this->registre.erase(registre.begin() + index);
}

void RegistreForce::cleanRegistre()
{
	this->registre.clear();
}

int RegistreForce::count()
{
	return (int)this->registre.size();
}