#include "Particule.hpp"
#include "Contact/ParticleContactResolver.hpp"
#include <vector>

class WorldParticules
{
private:
	std::vector<Particule*> particles;
public:

	WorldParticules();
	std::vector<Particule*> getParticles();
	void addParticle(Particule * particule);
	std::vector<ParticleContact> getAllContact();
};