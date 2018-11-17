#include "Forces/ParticuleForceGenerator.hpp"

class AnchoredSpring : public ParticuleForceGenerator
{
private: 
	Vector3D anchorPoint;
	float K; // constante d'élasticité
	float length0;

public:
	AnchoredSpring(Vector3D anchorPoint, float K, float length0);
	~AnchoredSpring();
	void updateForce(Particule* particule, float timeFrame);


};