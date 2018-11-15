#include <vector>
#include "ParticleContact.hpp"

class ParticleContactResolver {

	friend class ParticleContact;

private:
	int maxIteration;
	int iterationCount;
	std::vector<ParticleContact> contacts;

public:
	ParticleContactResolver();
	void setIterations(ParticleContact * contact);
	void resolveContact(float timeFrame);

};