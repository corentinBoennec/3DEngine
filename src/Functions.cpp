#include "Functions.hpp"

#include "Contact/Contact.hpp"

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
		if (tableRigidBody.size() > 0)
		{
			std::for_each(tableRigidBody.begin(), tableRigidBody.end(), [timeFrame](RigidBody *r_rigidbody)
				{
					r_rigidbody->updateAllVelocity(timeFrame);
					r_rigidbody->updatePositionOrientation(timeFrame);
					r_rigidbody->calculDerivedData();
					r_rigidbody->clearAccumulator();
				});
		}
		else
		{
			std::cout << "Il n'y a pas d'objet dans le monde...";
			exit(EXIT_FAILURE);
		}
	}

	float radToDegree(float angle)
	{
		angle = fmod(angle, 2 * M_PI);
		float angleDegree = angle * 180.0 / M_PI;
		return angleDegree;
	}

	float distFromPlan(Plan plan, Vector3D point)
	{
		float distance;

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

	void generateContacts(Box box, Plane plane, CollisionData* collisionData, std::ofstream* myfile)
	{
		std::vector<Vector3D> vertices = box.getAllVertices();
		for (int i = 0; i < vertices.size(); i++)
		{
			float distance = (plane.getNormal() * vertices.at(i)) + plane.getOffset();
			//std::cout << plane.getNormal() * vertices.at(i) << std::endl;
			if (distance <= 0)
			{
				//std::cout << vertices.at(i).getX() << " " << vertices.at(i).getY() << " " << vertices.at(i).getZ() << std::endl;
				Contact contact(vertices.at(i), plane.getNormal(), distance * -1);
				collisionData->addContact(&contact);
				*myfile << "Contact >" << " Point de contact > (" << contact.getContactPoint().getX() << ", " << contact.getContactPoint().getY() << ", " << contact.getContactPoint().getZ() << ") - Normal > (" << contact.getContactNormal().getX() << ", " << contact.getContactNormal().getY() << ", " << contact.getContactNormal().getZ() << ") - Interpénétration > " << contact.getInterpenetration() << std::endl;
			}
		}
	}
}