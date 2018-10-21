#include "Particule.hpp"
#include "ParticleContact.hpp"
#include <vector>
class worldParticles
{
private:
	std::vector<Particule> particles;
public:
	worldParticles();
	void addParticle(Particule particule);
	std::vector<ParticleContact> getAllContact();


	
};