/*
Missile3D.hpp
This contains the scale, rotation, translation, radiants of 3d missiles.
Linh Nguyen
Phase 1
COMP 465
*/

# ifndef __INCLUDES465__
# include "../includes465/include465.hpp"
# define __INCLUDES465__
# endif

# define __MISSILESITE3D__

class MissileSite3D {

private:

	int id;
	glm::mat4 rotationMatrix;
	glm::mat4 scaleMatrix;
	glm::vec3 scale;
	glm::mat4 translationMatrix;
	glm::vec3 rotationAxis;
	glm::mat4 orientationMatrix;
	glm::vec3 translationAmount;
	glm::mat4 identity;
	float radians;
	bool active;
	bool orbital;
	int numberMissile;
	int missileUpdates;


public:

	MissileSite3D(glm::vec3 translateParam, float radiantParams, float modelSize, float modelBR) {
		scale = glm::vec3(modelSize * 3.0f / modelBR);
		scaleMatrix = glm::scale(glm::mat4(), glm::vec3(scale));
		rotationMatrix = glm::mat4();  // no initial orientation

									   // rotate between 0.1 and 2.0 degrees
		radians = radiantParams;
		// random initial placement +/- 500 from origin in X, Y, Z
		translationMatrix = glm::translate(glm::mat4(), translateParam);
		identity = glm::mat4();
		orientationMatrix = glm::mat4();
		rotationAxis = glm::vec3(0, 1, 0);
		numberMissile = 5;
		active = true;

	}

	glm::mat4 getModelSiteMatrix() {
		return  orientationMatrix * scaleMatrix;
	}

	glm::mat4 getSiteOrientationMatrix()
	{

		return orientationMatrix;
	}



	void setTranslationAmount(glm::vec3 translation) {
		translationAmount = translation;
	}


	void setPosition(glm::vec3 newPosition) {
		orientationMatrix[3][0] = newPosition.x;
		orientationMatrix[3][1] = newPosition.y;
		orientationMatrix[3][2] = newPosition.z;
	}

	int getNumberMissiles()
	{
		return numberMissile;
	}

	void reduceMissileNumber()
	{
		if (numberMissile != 0)
		{
			numberMissile = numberMissile - 1;
		}
		else
		{
			active = false;
		}
	}

	void destroyed()
	{
		active = false;
	}

	bool isDestroyed()
	{
		return active;
	}

	bool isSiteActive()
	{
		return active;
	}

	void restart()
	{
		active = true;
		numberMissile = 5;
	}

	void update() {
		translationMatrix = glm::translate(identity, translationAmount);
		rotationMatrix = identity;
		orientationMatrix = orientationMatrix * translationMatrix * rotationMatrix;
	}
};