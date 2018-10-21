#include "Particule.hpp"
#include "ParticleContactResolver.hpp"
#include <vector>
class worldParticles
{
private:
	std::vector<Particule*> particles;
public:

	worldParticles();
	std::vector<Particule*> getParticles();
	void addParticle(Particule * particule);
	std::vector<ParticleContact> getAllContact();


	
};