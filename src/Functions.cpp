#include "Functions.hpp"

namespace utils
{
	float inverseMass(float mass)
	{
		return (float)1 / mass;
	}

	void timeGestion(int timeFrame)
	{
		std::chrono::milliseconds now;
		std::chrono::milliseconds lastFrame = std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch()
			);

		now = std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch()
			);
		std::chrono::milliseconds delta = now - lastFrame;
		lastFrame = now;

		if (delta.count() < timeFrame)
		{
			Sleep(timeFrame - delta.count());
		}

	}

}