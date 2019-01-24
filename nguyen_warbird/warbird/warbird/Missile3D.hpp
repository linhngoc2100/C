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

# define __MISSILE3D__

class Missile3D {

private:

	int id;
	glm::mat4 rotationMatrix;
	glm::mat4 scaleMatrix;
	glm::vec3 scale;
	glm::vec3 targetVec;
	glm::vec3 missileVec;
	glm::vec3 distance;
	glm::mat4 translationMatrix;
	glm::vec3 rotationAxis;
	glm::mat4 orientationMatrix;
	glm::mat4 identity;
	glm::mat4 locations;
	float radians;
	bool orbital;
	bool fired;
	bool missileOn;
	float speed;
	bool target;
	bool smartMissiles;
	int numberofUpdates;
	int maxiumUpdate;



public:

	Missile3D(glm::vec3 translateParam, float radiantParams, float modelSize, float modelBR) {
		scale = glm::vec3(modelSize * 1.0f / modelBR);
		scaleMatrix = glm::scale(glm::mat4(), glm::vec3(scale));
		identity = glm::mat4();
		rotationMatrix = glm::mat4();  // no initial orientation

									   // rotate between 0.1 and 2.0 degrees
		radians = radiantParams;
		// random initial placement +/- 500 from origin in X, Y, Z
		translationMatrix = glm::translate(glm::mat4(), translateParam);
		orientationMatrix = identity;
		rotationAxis = glm::vec3(0, 1, 0);
		missileOn = false;
		fired = false;
		target = false;
		speed = 10.0f;
		numberofUpdates = 0;


	}

	glm::mat4 getMissileOrientationMatrix()
	{

		return orientationMatrix;
	}

	glm::mat4 getModelMissileMatrix() {
		return orientationMatrix * scaleMatrix;
	}


	glm::mat4 gettowardTarget()
	{
		return locations;
	}
	int getNumberOfUpdates() {
		return numberofUpdates;
	}

	void setMissileOrientation(glm::mat4 mO)
	{
		orientationMatrix = mO;
	}

	void setPosition(glm::vec3 newPosition) {
		orientationMatrix[3][0] = newPosition.x;
		orientationMatrix[3][1] = newPosition.y;
		orientationMatrix[3][2] = newPosition.z;
	}

	void towardTarget(glm::mat4 targetPos)
	{
		locations = targetPos;


	}


	bool hasFired()
	{
		return fired;
	}

	void fireMissile()
	{
		fired = true;
	}

	bool isMissileActive()
	{
		return missileOn;
	}

	void setMissileActive()
	{
		missileOn = true;
	}

	bool hasTarget()
	{
		return target;
	}



	void getDestroyed()
	{
		missileOn = false;
		fired = false;
		target = false;
		numberofUpdates = 0;

	}


	void update() {

		rotationMatrix = identity;
		translationMatrix = identity;


		if (fired == true)
		{

			numberofUpdates = numberofUpdates + 1;
			distance = glm::vec3(0, 0, -speed);
			if (numberofUpdates > 200)
				target = true;
			translationMatrix = glm::translate(identity, distance);

			if (numberofUpdates > 2000)
			{
				printf("\n %s", "Missile destroyed for being too long");
				getDestroyed();

			}


			if (missileOn == true && target == true)
			{


				targetVec = getPosition(locations) - getPosition(getMissileOrientationMatrix());
				missileVec = getIn(getMissileOrientationMatrix());
				targetVec = glm::normalize(targetVec);
				missileVec = glm::normalize(missileVec);

				glm::vec3 newAxix = glm::cross(targetVec, missileVec);
				float direction = newAxix.x + newAxix.y + newAxix.z;
				float newRad = glm::acos(glm::dot(targetVec, missileVec));
				if (direction > 0)
				{
					newRad = glm::acos(glm::dot(targetVec, missileVec));
				}
				else
				{
					newRad = (2 * PI) - glm::acos(glm::dot(targetVec, missileVec));
				}
				rotationMatrix = glm::rotate(rotationMatrix, newRad, newAxix);

			}


		}

		orientationMatrix = orientationMatrix * translationMatrix * rotationMatrix;
		//translationMatrix = glm::translate(translationMatrix, translation);

	}
};