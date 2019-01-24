/*
Shape3D.cpp

This contains the scale, rotation, translation, radiants of 3d planets.
Linh Nguyen
Phase 1
COMP 465
*/

# ifndef __INCLUDES465__
# include "../includes465/include465.hpp"
# define __INCLUDES465__
# endif

# define __SHAPE3D__

class Shape3D {

private :
	int id;
  glm::mat4 rotationMatrix;
  glm::mat4 scaleMatrix;
  glm::mat4 orientationMatrix;
  glm::mat4 tm, tmp;
  glm::vec3 scale;
  glm::mat4 translationMatrix;
  glm::vec3 translation, nTrans;
  glm::vec3 rotationAxis;
 

  float rotationAmount;
  float radians, modelSize, modelBR; 
  bool orbital;

public:

  Shape3D(glm::vec3 translates, float radianParam, float modelSize, float modelBR, int id) {
	if (id == 0)
		orbital = false;
	else
		orbital = true;
	scale = glm::vec3(modelSize * 1.0f / modelBR);
	scaleMatrix = glm::scale(glm::mat4(), glm::vec3(scale));
	tm = glm::mat4();
	orientationMatrix = glm::mat4(); 
	rotationMatrix = glm::mat4();
	translationMatrix = glm::translate(glm::mat4(), translates);
    rotationAxis=glm::vec3(0,1,0);
	rotationAmount = radianParam;
    }
 
 glm::mat4 getModelMatrix() {
	 if (orbital) // orbital rotation
		 return(rotationMatrix * translationMatrix * scaleMatrix);
	 else  // center rotation
		 return(translationMatrix * rotationMatrix * scaleMatrix);
  }


 glm::mat4 getOrientationMatrix() {
	 if (orbital) {// orbital rotation
		 orientationMatrix = (rotationMatrix * translationMatrix);
		 return orientationMatrix;
	 }
	 else { // center rotation
		 orientationMatrix = (translationMatrix * rotationMatrix);
		 return orientationMatrix;
	 }
 }

virtual void update() {
	 
		rotationMatrix = glm::rotate(rotationMatrix, rotationAmount, rotationAxis);
	

    }   
  };  