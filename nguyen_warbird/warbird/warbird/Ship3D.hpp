/*
Ship3D.hpp
This contains the scale, rotation, translation, radiants of 3d ship.
Linh Nguyen
Phase 1
COMP 465
*/

# ifndef __INCLUDES465__
# include "../includes465/include465.hpp"
# define __INCLUDES465__
# endif

# define __SHIP3D__

class Ship3D {

private:

	int id;
	glm::mat4 rotationMatrix;
	glm::mat4 scaleMatrix;
	glm::mat4 identity;
	glm::vec3 scale;
	glm::mat4 translationMatrix;
	glm::vec3 rotationAxis;
	glm::mat4 orientationMatrix;
	glm::vec3 initialTranslate;
	float radians;
	bool orbital;
	bool active;
	int numberOfMissiles;
public:

	Ship3D(glm::vec3 translateParam, float radiantParams, float modelSize, float modelBR) {
		scale = glm::vec3(modelSize * 1.0f / modelBR);
		scaleMatrix = glm::scale(glm::mat4(), glm::vec3(scale));
		rotationMatrix = glm::mat4();  // no initial orientation
		identity = glm::mat4();
		// rotate between 0.1 and 2.0 degrees
		radians = radiantParams;
		initialTranslate = translateParam;
		// random initial placement +/- 500 from origin in X, Y, Z
		translationMatrix = glm::translate(glm::mat4(), translateParam);
		orientationMatrix = glm::mat4();
		rotationAxis = glm::vec3(0, 1, 0);
		active = true;
		numberOfMissiles = 9;

	}

	glm::mat4 getShipOrientationMatrix()
	{
		orientationMatrix = translationMatrix * rotationMatrix;
		return orientationMatrix;
	}

	glm::mat4 getModelShipMatrix() {
		return orientationMatrix * scaleMatrix;
	}

	void setShipOrientationMatrix(glm::mat4 nwo)
	{
		orientationMatrix = nwo;

	}

	void setTranslationMatrix(glm::vec3 translation) {
		translationMatrix = glm::translate(identity, translation);
	}

	void setPosition(glm::vec3 newPosition) {

		orientationMatrix[3][0] = newPosition.x;
		orientationMatrix[3][1] = newPosition.y;
		orientationMatrix[3][2] = newPosition.z;
	}

	void setForward(int speed)
	{
		glm::vec3 destination = glm::vec3(speed*rotationMatrix[2].x, speed*rotationMatrix[2].y, speed*rotationMatrix[2].z);
		translationMatrix = glm::translate(translationMatrix, glm::vec3(-destination.x, -destination.y, -destination.z));
	}

	void setBack(int speed)
	{
		glm::vec3 destination = glm::vec3(speed*rotationMatrix[2].x, speed*rotationMatrix[2].y, speed*rotationMatrix[2].z);
		translationMatrix = glm::translate(translationMatrix, glm::vec3(destination.x, destination.y, destination.z));
	}

	void setPitch(float p)
	{
		rotationAxis = glm::vec3(1.0f, 0.0f, 0.0f);
		rotationMatrix = glm::rotate(rotationMatrix, p, rotationAxis);
	}

	void setRoll(float r)
	{
		rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
		rotationMatrix = glm::rotate(rotationMatrix, r, rotationAxis);
	}

	void setYaws(float y)
	{
		rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);
		rotationMatrix = glm::rotate(rotationMatrix, y, rotationAxis);
	}

	bool isActive() {
		return active;
	}

	void destroy() {

		active = false;
	}

	int numberMissiles() {
		return numberOfMissiles;
	}

	void reduceMissiles() {
		if (numberOfMissiles > 0)
			numberOfMissiles = numberOfMissiles - 1;
	}

	void warpShip(glm::mat4 objPos, int planetId)
	{
		if (planetId == 1)
		{
			translationMatrix = objPos * glm::translate(glm::mat4(), glm::vec3(0.0f, 200.0f, -1500.0f));
			rotationMatrix = glm::rotate(glm::mat4(), 3.5f, glm::vec3(0.0f, 1.0f, 0.0f));
		}
		if (planetId == 2)
		{
			translationMatrix = objPos * glm::translate(glm::mat4(), glm::vec3(0.0f, 200.0f, 3500.0f));
			rotationMatrix = glm::rotate(glm::mat4(), -0.5f, glm::vec3(0.0f, 1.0f, 0.0f));
		}
	}

	void restart() {
		active = true;
		orientationMatrix = glm::translate(orientationMatrix, initialTranslate);
		numberOfMissiles = 9;

	}


	void update() {

		if (!active)
			return;
		rotationMatrix = glm::rotate(rotationMatrix, radians, rotationAxis);

		orientationMatrix = orientationMatrix * rotationMatrix * translationMatrix;
	}
};