#include "Particule.hpp"
#include "Vector3D.hpp"

class ParticleContact
{
private:
	Particule * particule[2];
	float restitution;
	Vector3D normal;
	float penetration;

public:
	ParticleContact(Particule * particule[2], float restitution);
	void resolve(float duration);
	float computeVs();
	void resolveImpulsion();
	void resolveInterPenetration();
};