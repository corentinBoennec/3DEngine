#include "Functions.hpp"

#include <chrono>
#include <algorithm>
#include <thread>

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

		// calcul du temps entre la dernière frame et "maintenant"
		std::chrono::milliseconds delta = now - lastFrame;
		lastFrame = now;

		// si le temps de calcul est inférieur à 1/30ème de seconde (timeFrame), alors on attend
		if (delta.count() < timeFrame)
		{
			unsigned int sleepingDuration = static_cast<unsigned int>(timeFrame - delta.count());
			std::this_thread::sleep_for(std::chrono::milliseconds(sleepingDuration));
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


	void integratorRigidBody(std::vector<RigidBody*> tableRigidBody, float timeFrame)
	{
		std::for_each(tableRigidBody.begin(), tableRigidBody.end(), [timeFrame](RigidBody *r_rigidbody)
		{
			r_rigidbody->updateAllVelocity(timeFrame);
			r_rigidbody->updatePositionOrientation(timeFrame);
			r_rigidbody->calculDerivedData();
			r_rigidbody->clearAccumulator();
		});
	}

	float radToDegree(float angle)
	{
		angle = fmod(angle, 2 * M_PI);
		float angleDegree = angle * 180.0 / M_PI;
		return angleDegree;
	}

	float distFromPlan(Plan plan, Vector3D point)
	{
		float distance;  /*NOTE*/ //Probabelement pas mais pourrait être faux
		
		distance = (point - plan.getPosition()) * plan.getDirection();
		
		
		return distance;
	}

	bool sameSideAsNormal(Plan plan, Vector3D point)
	{
		if (plan.getDirection() * (plan.getPosition() - point) >= 0)
		{
			return true;
		}
		else 
		{
			return false;
		}
	}

}



