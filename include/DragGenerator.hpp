#pragma once
#include "Vector3D.hpp"
#include "ParticuleForceGenerator.hpp"

class DragGenerator : public ParticuleForceGenerator
{
private:
	float K1;
	float K2;
public:
	DragGenerator(float K1, float K2);
	~DragGenerator();
	void updateForce(Particule* particule, float timeFrame);

};