#include "ParticuleForceGenerator.hpp"

class ParticuleFlotation : public ParticuleForceGenerator
{
private:
	Particule* particule;
	float maxDepth;
	float ObjectVolume;
	float liquidLevel;
	float liquidDensity;
	float totalImmertion;
public:
	ParticuleFlotation(Particule * particule, float maxDepth, float ObjectVolume, float liquidLevel, float liquidDensity, float totalImmersion);
	void updateForce();

};