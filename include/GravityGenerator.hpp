#pragma once
#include "ParticuleForceGenerator.hpp"

class GravityGenerator : public ParticuleForceGenerator
{
private:
	Vector3D gravity;
public:
<<<<<<< HEAD
	~GravityGenerator();
	GravityGenerator(Vector3D gravity);
	void updateForce(Particule* particule);
=======
	GravityGenerator(Vector3D gravity);
	~GravityGenerator();
	void updateForce(Particule * particule, float time);

>>>>>>> 7d1e2ad34ecc19a9b2d26c89fdbb521659dcd761
};