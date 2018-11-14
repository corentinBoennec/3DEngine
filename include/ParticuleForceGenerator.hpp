#pragma once
#include "Particule.hpp"


class ParticuleForceGenerator
{
public:
	virtual void updateForce(Particule* particule, float time) = 0;
};