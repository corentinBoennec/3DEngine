#include "Forces/ParticuleForceGenerator.hpp"

class ParticuleFlotation : public ParticuleForceGenerator
{
private:
	float maxDepth;
	float ObjectVolume;
	float liquidLevel;
	float liquidDensity;
	float totalImmertion;
public:
	ParticuleFlotation(float maxDepth, float ObjectVolume, float liquidLevel, float liquidDensity, float totalImmersion);
	void updateForce(Particule* particule, float timeFrame);
};