#include "Functions.hpp"

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
			Sleep(timeFrame - delta.count());
		}

	}

	void integrator(Particule& particule, float timeFrame)
	{
		particule.updatePosition(timeFrame);
		particule.updateVelocity(timeFrame);
	}

}

/*namespace callgluts
{
	void windowResize(int w, int h) {

		// Prevent a divide by zero, when window is too short
		// (you cant make a window of zero width).
		if (h == 0)
			h = 1;

		float ratio = w * 1.0 / h;

		// Use the Projection Matrix
		glMatrixMode(GL_PROJECTION);

		// Reset Matrix
		glLoadIdentity();

		// Set the viewport to be the entire window
		glViewport(0, 0, w, h);

		// Set the correct perspective.
		gluPerspective(45, ratio, 1, 100);

		// Get Back to the Modelview
		glMatrixMode(GL_MODELVIEW);
	}

	void renderScene(void) {

		// Clear Color and Depth Buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Reset transformations
		glLoadIdentity();
		glColor3d(1, 1, 1);

		glPushMatrix();
		glTranslated(0.0, 0.0, -10);
		glutSolidSphere(0.2, 50, 50);
		glPopMatrix();

		glutSwapBuffers();
	}
}*/