#pragma once
#include "ParticuleForceGenerator.hpp"

class GravityGenerator : public ParticuleForceGenerator
{
private:
	Vector3D gravity;
public:
	GravityGenerator(Vector3D gravity);
	~GravityGenerator();
	void updateForce(Particule * particule, float time);

};