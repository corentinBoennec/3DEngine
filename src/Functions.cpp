#include "Functions.hpp"
#include <algorithm>

namespace utils
{
	void timeGestion(float timeFrame)
	{
		std::chrono::milliseconds now;
		std::chrono::milliseconds lastFrame = std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch()
			);

		now = std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch()
			);

		// calcul du temps entre la derni�re frame et "maintenant"
		std::chrono::milliseconds delta = now - lastFrame;
		lastFrame = now;

		// si le temps de calcul est inf�rieur � 1/30�me de seconde (timeFrame), alors on attend
		if (delta.count() < timeFrame)
		{
			Sleep(timeFrame - delta.count());
		}

	}

	void integrator(std::vector<Particule*> tableParticule, float timeFrame)
	{
		std::for_each(tableParticule.begin(), tableParticule.end(), [timeFrame](Particule *p_particule)
		{
			p_particule->updatePosition(timeFrame);
			p_particule->updateVelocity(timeFrame);
		});
	}
}