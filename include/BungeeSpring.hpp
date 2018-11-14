#pragma once
#include "ParticuleForceGenerator.hpp"

class BungeeSpring : public ParticuleForceGenerator
{
private:
	Particule otherParticule;
	float k;
	float length0;
public:
	BungeeSpring(Particule* otherParticule, float k, float length0);
	~BungeeSpring();
	void updateForce(Particule* particule, float timeFrame);
};