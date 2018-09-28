#pragma once
#include "ParticuleForceGenerator.hpp"

class GravityGenerator : public ParticuleForceGenerator
{
private:
	Vector3D gravity;
public:
	~GravityGenerator();
	GravityGenerator(Vector3D gravity);
	void updateForce(Particule* particule);
