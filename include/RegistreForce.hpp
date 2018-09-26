#pragma once
#include "Particule.hpp"
#include "ParticuleForceGenerator.hpp"
#include <vector>
class RegistreForce
{
private: 
	struct EnregistrementForce{
		Particule * particule;
		ParticuleForceGenerator * forceGenerator;
	};

	typedef std::vector<EnregistrementForce> Registre;
	Registre registre;

public:
	void add(EnregistrementForce eF);
	void suppr(int index);
	int count();

};