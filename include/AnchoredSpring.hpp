#include "ParticuleForceGenerator.hpp"

class AnchoredSpring : public ParticuleForceGenerator
{
private: 
	Particule * particule;
	Vector3D anchorPoint;
	float K; // constante d'�lasticit�
	float length0;

public:
	AnchoredSpring(Particule * particule, Vector3D anchorPoint, float K, float length0);
	~AnchoredSpring();
	void updateForce();
	void updatePosition();


};