#pragma once
#include "ParticuleForceGenerator.hpp"

class SimpleSpring : public ParticuleForceGenerator
{
private:
	Particule otherParticule;
	float k; // constante d'élasticité du matériau
	float length0; // longueur initiale du ressort

public:
	SimpleSpring(Particule* otherParticule, float k, float lenght0);
	~SimpleSpring();
	void updateForce(Particule* particule, float timeFrame);
};

