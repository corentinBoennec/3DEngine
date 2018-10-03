#pragma once
#include "ParticuleForceGenerator.hpp"

class ParticuleStiffString
{
private:
	Vector3D anchor;
	float k;
	float damp;

public:
	ParticuleStiffString(Vector3D anchor, float k, float damp);
	~ParticuleStiffString();
	void updateForce(Particule particule);
};
