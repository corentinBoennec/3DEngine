#include "Functions.hpp"
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
			r_rigidbody->updatePositionOrientation(timeFrame);
			r_rigidbody->updateAllVelocity(timeFrame);
			r_rigidbody->calculDerivedData();
			r_rigidbody->clearAccumulator();
		});
	}

	Matrix4x4 quaternToMatrix(Quaternion q)
	{
			float tab[12];

			tab[0] = 1 - (2 * (q.getY() * q.getY()) + 2 * (q.getZ() * q.getZ()));
			tab[1] = 2 * q.getX() * q.getY() + 2 * q.getZ() * q.getAngle();
			tab[2] = 2 * q.getX() * q.getZ() - 2 * q.getY() *q.getAngle();
			tab[3] = q.getX();
			tab[4] = 2 * q.getX() * q.getY() - 2 * q.getZ() * q.getAngle();
			tab[5] = 1 - (2 * (q.getX() * q.getX()) + 2 * q.getZ() * q.getZ());
			tab[6] = 2 * q.getY() * q.getZ() + 2 * q.getX() * q.getAngle();
			tab[7] = q.getY();
			tab[8] = 2 * q.getX() * q.getZ() + 2 * q.getY() * q.getAngle();
			tab[9] = 2 * q.getY() * q.getZ() - 2 * q.getX()* q.getAngle();
			tab[10] = 1 - (2 * (q.getX() * q.getX()) + 2 * (q.getY() * q.getY()));
			tab[11] = q.getZ();

			Matrix4x4 result(tab);

			return result;
	}
	Vector3D orthonormalChange(Matrix4x4 transformationMatrix, Vector3D v)
	{
			Matrix3x3 m(transformationMatrix);
			Vector3D vectorInOtherBase = m * v;
			
			return vectorInOtherBase;
	}

	
}