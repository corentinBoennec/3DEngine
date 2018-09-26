#pragma once
#include "ParticuleForceGenerator.hpp"

class GravityGenerator : ParticuleForceGenerator
{
private:
	Vector gravity;
public:
	GravityGenerator();
	~GravityGenerator();
	GravityGenerator(Vector gravity);
	void updateForce(Particule * particule, float time);

};