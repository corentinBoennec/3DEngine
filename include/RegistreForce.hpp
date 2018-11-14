#pragma once

#include <vector>

#include "Particule.hpp"
#include "ParticuleForceGenerator.hpp"

class RegistreForce
{
private: 
	struct EnregistrementForce{
		Particule* particule;
		ParticuleForceGenerator* forceGenerator;
	};

	typedef std::vector<EnregistrementForce> Registre;
	Registre registre;

public:
	RegistreForce();
	~RegistreForce();

	void update(float timeFrame);
	void add(Particule* particule, ParticuleForceGenerator* forceGenerator);
	void suppr(int index);
	void cleanRegistre();
	int count();
};