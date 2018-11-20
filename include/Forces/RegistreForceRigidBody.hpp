#pragma once

#include <vector>

#include "RigidBody.hpp"
#include "RigidBodyForceGenerator.hpp"

class RegistreForceRigidBody
{
private:
	struct EnregistrementForce {
		RigidBody* particule;
		RigidBodyForceGenerator* forceGenerator;
	};

	typedef std::vector<EnregistrementForce> Registre;
	Registre registre;

public:
	RegistreForceRigidBody();
	~RegistreForceRigidBody();

	void update(float timeFrame);
	void add(RigidBody* rigidbody, RigidBodyForceGenerator* forceGenerator);
	void suppr(int index);
	void cleanRegistre();
	int count();
};