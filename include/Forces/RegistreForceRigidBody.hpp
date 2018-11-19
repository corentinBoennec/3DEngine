#pragma once

#include <vector>

#include "RigidBody.hpp"
#include "RigidBodyForceGenerator.hpp"

class RegistreForce
{
private:
	struct EnregistrementForce {
		RigidBody* particule;
		RigidBodyForceGenerator* forceGenerator;
	};

	typedef std::vector<EnregistrementForce> Registre;
	Registre registre;

public:
	RegistreForce();
	~RegistreForce();

	void update(float timeFrame);
	void add(RigidBody* rigidbody, RigidBodyForceGenerator* forceGenerator);
	void suppr(int index);
	void cleanRegistre();
	int count();
};