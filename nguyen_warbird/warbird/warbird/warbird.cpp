/*
Linh Ngoc Nguyen
COMP 465
Phase 2-3
Fixed camera from static to dynamic
get prevous camera, warp ship
Get gravity, timeQuantum, ship movement, light, texture.
Problem with missiles- missitle target the object but it disappears
Restart doesnot work
	keyboard command:
		v: change camera view
		x: previous camera
		t: change TQ value
		s: change speed
		p: point light
		h: headlight
		a: ambient light
		g: toogle on/off gravity
		w: warp ship
		f: fire missile
		arrow left: ship yaws left
		arrow right: ship yaws right
		arrow up: ship forward
		aroow down: ship backward
		control left: ship rolls right
		control right: ship rolls left
		control up: ship pitches down
		control down: ship pithces up
*/


// define your target operating system: __Windows__  __Linux__  __Mac__
# define __Windows__ 
# include "../includes465/include465.hpp"
# include "../includes465/texture.hpp"
# include "shape3d.hpp"
#include "Ship3D.hpp"
#include "Missile3D.hpp"
#include "MissileSite3D.hpp"

// Shapes
const int nShapes = 8; //number of shape
const int nSpheres = 5;//number of sphere
const int nSites = 2; //number of missile site
const int nMissiles = 3; //number of Missiles

int star = 9;

const int gravity = 90000000; //gravity
Shape3D * shape[nShapes];
Ship3D * warship;
Missile3D * missiles[nMissiles];
MissileSite3D * missileSite[nSites];
MissileSite3D * targetMissiles;
// Model for shapes
char * modelFile[nShapes] = { "ruber.tri", "unum.tri", "duo.tri", "primus.tri", "secundus.tri", "spaceship.tri","missile.tri", "missileSite.tri" }; // name of tri model file
char * fileName = "starField.raw";
int width = 1066, height = 600;

const GLuint sVertices[nShapes] = { 264 * 3, 264 * 3, 264 * 3, 264 * 3, 264 * 3, 1308 * 3, 1416 * 3,804 * 3 };
const GLuint nVertices = 264 * 3;  // 3 vertices per line (surface) of model file  
const GLuint shipVertices = 1308 * 3; //ship vertices
const GLuint mVertices = 1416 * 3;	//missiles vertices
const GLuint msVertices = 804 * 3;  //missitle site vertices
const GLuint starVertices = 6;


float boundingRadius[nShapes];  // modelFile's bounding radius


// display state and "state strings" for title display
// window title strings
char baseStr[50] = "Warbird {f, t, r} : ";
char fpsStr[15], viewStr[35] = " front view";
char titleStr[100];
char tqStr[15] = " Ace";
char spdStr[10] = " spd 10";

GLuint vao[nShapes];  // VertexArrayObject
GLuint buffer[nShapes];
GLuint ibo;
GLuint textVao;
GLuint textIBO;
GLuint textBuf;

GLuint shaderProgram;
char * vertexShaderFile = "simpleVertex.glsl";
char * fragmentShaderFile = "simpleFragment.glsl";
GLuint MVP, MV, NM;
GLuint ModelViewMatrix, NormalMatrix;  // Model View Projection matrix's handle
GLuint vPosition[nShapes];
GLuint vColor[nShapes];
GLuint vNormal[nShapes];
GLuint isTexture;
GLuint texture;
GLuint Texture;
GLuint TexturePosition;
GLuint vTextCoords;


glm::mat4 projectionMatrix;     // set in reshape()
glm::mat4 modelMatrix;          // set in shape[i]-->updateDraw()
glm::mat4 viewMatrix;           // set in keyboard()
glm::mat4 ModelViewProjectionMatrix; // set in display();
glm::mat4 modelViewMatrix;
glm::mat3 normalMatrix;

glm::vec3 warshipCam[2];

// vectors and values for lookAt
glm::vec3 eye, at, up;

glm::vec3 currentPlanetPos;
glm::vec3 objectPos;

float length;

glm::vec3 gravityVec = glm::vec3(0, 0, 0);
bool gravityOn = true;

// rotation variables

glm::vec3 translate[nShapes] = {
	glm::vec3(0, 0, 0),			 // Rubers' location
	glm::vec3(4000, 0, 0),
	glm::vec3(-9000, 0, 0),
	glm::vec3(900, 0, 0),
	glm::vec3(-7250, 0, 0),
	glm::vec3(5000, 1000, 5000),
	glm::vec3(4900,1000,4850),
	glm::vec3(0,0,0)
};

float sizeOfModel[nShapes] = {
	2000.0f,	// Ruber
	200.0f,
	400.0f,
	100.0f,
	150.0f,
	100.0f,
	35.0f,
	30.0f
};
float rotationAmount[nShapes] = {
	0.0f,		// Ruber
	0.004f,
	0.002f,
	0.004f,
	0.002f,
	0.0f,
	0.0f,
	0.0f
};

static const GLfloat point[] = {
	-80000.0f,  80000.0f, -80000.0f, 1.0f,
	-80000.0f, -80000.0f, -80000.0f, 1.0f,
	80000.0f, -80000.0f, -80000.0f, 1.0f,
	80000.0f,  80000.0f, -80000.0f, 1.0f,
	80000.0f, -80000.0f, -80000.0f, 1.0f,
	-80000.0f, 80000.0f, -80000.0f, 1.0f,
};

static const unsigned int indices[] = {
	3, 0, 1,
	3, 1, 2
};

// The order the texture coordinates are drawn
static const GLfloat textCoords[] = {
	0.0f, 0.0f,     // 0
	1.0f, 0.0f,     // 1
	1.0f, 1.0f,     // 2
	0.0f, 1.0f
};


glm::mat4 objUMatrix;
glm::mat4 objDMatrix;
glm::mat4 unumMatrix;
glm::mat4 duoMatrix;
glm::mat4 shipEye = glm::translate(glm::mat4(), glm::vec3(0.0f, 300.0f, 1000.0f));
glm::mat4 shipAt = glm::translate(glm::mat4(), glm::vec3(0.0f, 300.0f, 0.0f));
glm::mat4 warbirdMatrix;

glm::mat4 missileLocation;
glm::mat4 targetLocation;
glm::vec3 missilePosition;
glm::vec3 targetPosition;

int timerDelay = 40, frameCount = 0;  // A delay of 40 milliseconds is 25 updates / second
double currentTime, lastTime, timeInterval;
int numberofUpdates = 0;
int timeQ = 0;
const int numberOfTimeQuantums = 4;
int currentSpeed = 10;
int warpLocation = 1;
int currentCam = 0; //curent camera


//lights
GLuint isTheSun;

//Point Light vars
GLuint pointLightSetOn; // handle for bool in shader
GLuint pointLightLoc; //handle
GLuint pointLightIntensity; //handle
int pointLightOn = 1; //0 = off 1 = on
glm::vec3 PointLightIntensity = glm::vec3(0.5f, 0.5f, 0.5f);//RBG values of the light
glm::vec3 RuberPos = glm::vec3(0, 1000, 0);

//Ambient Light vars
GLuint ambientSetOn;
GLuint ambientLightIntensity;
int ambientOn = 0;
glm::vec3 AmbientLightIntensity = glm::vec3(0.5, 0.5, 0.5);//RBG values of the light

														   //Head Light vars
GLuint headLightSetOn; // handle for bool in shader
GLuint headLightLoc; //handle
GLuint headLightIntensity; //handle
int headLightOn = 0; //0 = off 1 = on
glm::vec3 HeadLightIntensity = glm::vec3(0.5f, 0.5f, 0.5f);//RBG values of the light

//texture
glm::mat4 starRotation;
glm::mat4 startTranslate;

void init(void) {
	shaderProgram = loadShaders(vertexShaderFile, fragmentShaderFile);
	glUseProgram(shaderProgram);

	// Generate Vertex Arrays and Buffers
	glGenVertexArrays(nShapes, vao);
	glGenBuffers(nShapes, buffer);

	for (int i = 0; i < nShapes;i++) {
		boundingRadius[i] = loadModelBuffer(modelFile[i], sVertices[i], vao[i],
			buffer[i], shaderProgram, vPosition[i], vColor[i], vNormal[i], "vPosition", "vColor", "vNormal");
	}

	MVP = glGetUniformLocation(shaderProgram, "ModelViewProjection");
	MV = glGetUniformLocation(shaderProgram, "ModelView");
	NM = glGetUniformLocation(shaderProgram, "NormalMatrix");

	//light
	pointLightSetOn = glGetUniformLocation(shaderProgram, "PointLightOn");
	pointLightLoc = glGetUniformLocation(shaderProgram, "PointLightPosition");
	pointLightIntensity = glGetUniformLocation(shaderProgram, "PointLightIntensity");

	headLightSetOn = glGetUniformLocation(shaderProgram, "HeadLightOn");
	headLightLoc = glGetUniformLocation(shaderProgram, "HeadLightPosition");
	headLightIntensity = glGetUniformLocation(shaderProgram, "HeadLightIntensity");

	ambientLightIntensity = glGetUniformLocation(shaderProgram, "AmbientLightIntensity");
	ambientSetOn = glGetUniformLocation(shaderProgram, "AmbientOn");

	isTheSun = glGetUniformLocation(shaderProgram, "IsTheSun");

	// initially use a front view
	eye = glm::vec3(0.0f, 10000.0f, 20000.0f);   // eye is 1000 "out of screen" from origin
	at = glm::vec3(0.0f, 0.0f, 0.0f);   // looking at origin
	up = glm::vec3(0.0f, 1.0f, 0.0f);   // camera'a up vector
	viewMatrix = glm::lookAt(eye, at, up);

	// set render state values
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);

	// create shape
	for (int i = 0; i < nSpheres; i++) {
		shape[i] = new Shape3D(translate[i], rotationAmount[i], sizeOfModel[i], boundingRadius[i],i);
		
	}
	printf("%d Shapes created \n", nShapes);

	warship = new Ship3D(translate[5], rotationAmount[5], sizeOfModel[5], boundingRadius[5]);

	for (int i = 0; i < nMissiles;i++) {
		missiles[i] = new Missile3D(translate[6], rotationAmount[6], sizeOfModel[6], boundingRadius[6]);
	}

	for (int i = 0; i < nSites; i++)
		missileSite[i] = new MissileSite3D(translate[7], rotationAmount[7], sizeOfModel[7], boundingRadius[7]);

	missileSite[0]->setTranslationAmount(glm::vec3(0, sizeOfModel[1], 0));
	missileSite[1]->setTranslationAmount(glm::vec3(0, sizeOfModel[2], 0));

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &textVao);
	glBindVertexArray(textVao);

	glGenBuffers(1, &textBuf);
	glEnableVertexAttribArray(textBuf);
	glBindBuffer(GL_ARRAY_BUFFER, textBuf);

	glBufferData(GL_ARRAY_BUFFER, sizeof(point) + sizeof(textCoords), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(point), point);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(point), sizeof(textCoords), textCoords);

	TexturePosition = glGetAttribLocation(shaderProgram, "vPosition");
	glVertexAttribPointer(TexturePosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(TexturePosition);

	vTextCoords = glGetAttribLocation(shaderProgram, "vTexCoord");
	glVertexAttribPointer(vTextCoords, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(point)));
	glEnableVertexAttribArray(vTextCoords);

	isTexture = glGetUniformLocation(shaderProgram, "IsTexture");
	glUniform1i(isTexture, 0);
	texture = loadRawTexture(texture, fileName, width, height);
	if (texture != 0)
	{
		Texture = glGetUniformLocation(shaderProgram, "Texture");
		printf("Texture file %s, read, texture %1d generated and bound \n", fileName, Texture);
	}
	else
	{
		printf("Texture in file %s NOT LOADED \n");
	}



	lastTime = glutGet(GLUT_ELAPSED_TIME);  // get elapsed system time
}

void reshape(int width, int height) {
	glViewport(0, 0, width, height);
	projectionMatrix = glm::perspective(glm::radians(60.0f), (GLfloat)width / (GLfloat)height, 1.0f, 250000.0f);
}

void setGravity()
{
	objectPos = getPosition(warship->getShipOrientationMatrix());

	length = distance(objectPos, glm::vec3(0, 0, 0));


	objectPos = -1.0f * objectPos;
	if (length != 0)
		gravityVec = glm::normalize(objectPos) * (gravity / (length * length));
	else
		gravityVec = glm::vec3(0, 0, 0);
	warship->setPosition(getPosition(warship->getShipOrientationMatrix()) + gravityVec);
}

// update and display animation state in window title
void updateTitle() {
	if (warship->isActive() && (missileSite[0]->isSiteActive() || missileSite[1]->isSiteActive()))
	{
		sprintf(titleStr, "Warbird: %d Speed: %s Unum %d Secundus %d View: %s TQ %s F/S %s ", warship->numberMissiles(), spdStr,
			missileSite[0]->getNumberMissiles(), missileSite[1]->getNumberMissiles(), viewStr, tqStr, fpsStr);
	}
	else if (warship->isActive() && (!missileSite[0]->isSiteActive() || !missileSite[1]->isSiteActive()))
	{
		sprintf(titleStr, "Good Job! Cadet passes flight training.");
	}
	else {
		sprintf(titleStr, "Game Over, YCadet resigns from War College. Press 'r' to restart the game");
	}
	// printf("title string = %s \n", titleStr);
	glutSetWindowTitle(titleStr);
}

void camUpdate(void) {

	switch (currentCam) {
	case 0:
		eye = glm::vec3(0.0f, 10000.0f, 20000.0f);
		at = glm::vec3(0.0f, 0.0f, 0.0f);
		up = glm::vec3(0.0f, 1.0f, 0.0f);
		strcpy(viewStr, "Front view");

		break;
	case 1:
		eye = glm::vec3(0.0f, 20000.0f, 0.0f);
		at = glm::vec3(0.0f, 0.0f, 0.0f);
		up = glm::vec3(0.0f, 0.0f, -1.0f);
		strcpy(viewStr, "Top view");

		break;
	case 2:
		eye = glm::vec3(unumMatrix[3].x, 4000.0f, unumMatrix[3].z);
		at = glm::vec3(unumMatrix[3].x, unumMatrix[3].y, unumMatrix[3].z);
		up = glm::vec3(0.0f, 0.0f, 1.0f);
		strcpy(viewStr, " unum view");

		break;
	case 3:
		eye = glm::vec3(duoMatrix[3].x, 4000.0f, duoMatrix[3].z);
		at = glm::vec3(duoMatrix[3].x, duoMatrix[3].y, duoMatrix[3].z);
		up = glm::vec3(0.0f, 0.0f, 1.0f);
		strcpy(viewStr, " duo view");

		break;
	case 4:
		shipEye = glm::translate(warbirdMatrix, glm::vec3(0.0f, 300.0f, 1000.0f));;
		shipAt = glm::translate(warbirdMatrix, glm::vec3(0.0f, 300.0f, 0.0f));;
		eye = glm::vec3(shipEye[3].x, shipEye[3].y, shipEye[3].z);
		at = glm::vec3(shipAt[3].x, shipAt[3].y, shipAt[3].z);
		up = glm::vec3(warbirdMatrix[1].x, warbirdMatrix[1].y, warbirdMatrix[1].z);
		strcpy(viewStr, " ship view");

		break;

	}

}

void display(void) {
	//clear buffer
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	viewMatrix = glm::lookAt(eye, at, up);

	// update model matrix, set MVP, draw
	//Planets

	glUniform1i(isTexture, 1);
	glBindVertexArray(textVao);
	glBindBuffer(GL_ARRAY_BUFFER, textBuf);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	ModelViewProjectionMatrix = projectionMatrix * viewMatrix;;
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(ModelViewProjectionMatrix));
	modelViewMatrix = viewMatrix * modelMatrix;
	normalMatrix = glm::mat3(modelViewMatrix);
	glUniformMatrix3fv(NM, 1, GL_FALSE, glm::value_ptr(normalMatrix));
	glUniformMatrix4fv(MV, 1, GL_FALSE, glm::value_ptr(modelViewMatrix));
	glDrawElements(GL_TRIANGLES, starVertices, GL_UNSIGNED_INT, BUFFER_OFFSET(0));

	starRotation = glm::rotate(glm::mat4(), PI/2, glm::vec3(0.0, 1.0, 0.0));
	ModelViewProjectionMatrix = projectionMatrix * viewMatrix * starRotation;
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(ModelViewProjectionMatrix));
	modelViewMatrix = viewMatrix * modelMatrix;
	normalMatrix = glm::mat3(modelViewMatrix);
	glUniformMatrix3fv(NM, 1, GL_FALSE, glm::value_ptr(normalMatrix));
	glUniformMatrix4fv(MV, 1, GL_FALSE, glm::value_ptr(modelViewMatrix));
	glDrawElements(GL_TRIANGLES, starVertices, GL_UNSIGNED_INT, BUFFER_OFFSET(0));

	starRotation = glm::rotate(glm::mat4(), -PI/2, glm::vec3(0.0, 1.0, 0.0));
	ModelViewProjectionMatrix = projectionMatrix * viewMatrix * starRotation;
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(ModelViewProjectionMatrix));
	modelViewMatrix = viewMatrix * modelMatrix;
	normalMatrix = glm::mat3(modelViewMatrix);
	glUniformMatrix3fv(NM, 1, GL_FALSE, glm::value_ptr(normalMatrix));
	glUniformMatrix4fv(MV, 1, GL_FALSE, glm::value_ptr(modelViewMatrix));
	glDrawElements(GL_TRIANGLES, starVertices, GL_UNSIGNED_INT, BUFFER_OFFSET(0));

	starRotation = glm::rotate(glm::mat4(), PI, glm::vec3(0.0, 1.0, 0.0));

	ModelViewProjectionMatrix = projectionMatrix * viewMatrix * starRotation;
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(ModelViewProjectionMatrix));
	modelViewMatrix = viewMatrix * modelMatrix;
	normalMatrix = glm::mat3(modelViewMatrix);
	glUniformMatrix3fv(NM, 1, GL_FALSE, glm::value_ptr(normalMatrix));
	glUniformMatrix4fv(MV, 1, GL_FALSE, glm::value_ptr(modelViewMatrix));
	glDrawElements(GL_TRIANGLES, starVertices, GL_UNSIGNED_INT, BUFFER_OFFSET(0));

	starRotation = glm::rotate(glm::mat4(), PI/2, glm::vec3(1.0, 0.0, 0.0));

	ModelViewProjectionMatrix = projectionMatrix * viewMatrix * starRotation;
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(ModelViewProjectionMatrix));
	modelViewMatrix = viewMatrix * modelMatrix;
	normalMatrix = glm::mat3(modelViewMatrix);
	glUniformMatrix3fv(NM, 1, GL_FALSE, glm::value_ptr(normalMatrix));
	glUniformMatrix4fv(MV, 1, GL_FALSE, glm::value_ptr(modelViewMatrix));
	glDrawElements(GL_TRIANGLES, starVertices, GL_UNSIGNED_INT, BUFFER_OFFSET(0));

	starRotation = glm::rotate(glm::mat4(), -PI/2, glm::vec3(1.0, 0.0, 0.0));

	ModelViewProjectionMatrix = projectionMatrix * viewMatrix * starRotation;
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(ModelViewProjectionMatrix));
	modelViewMatrix = viewMatrix * modelMatrix;
	normalMatrix = glm::mat3(modelViewMatrix);
	glUniformMatrix3fv(NM, 1, GL_FALSE, glm::value_ptr(normalMatrix));
	glUniformMatrix4fv(MV, 1, GL_FALSE, glm::value_ptr(modelViewMatrix));
	glDrawElements(GL_TRIANGLES, starVertices, GL_UNSIGNED_INT, BUFFER_OFFSET(0));

	glUniform1i(isTexture, 0);


	camUpdate();

	for (int i = 0; i < nSpheres; i++) {
		//if it is primus, it will orbit around duo
		if (i == 3  ) {
			modelMatrix = (shape[2]->getOrientationMatrix())*(shape[i]->getModelMatrix());
			
		}
		else {
			modelMatrix = shape[i]->getModelMatrix();
		}

		if (i == 0)
			glUniform1i(isTheSun, 1);
		else
			glUniform1i(isTheSun, 0);

		//light draw
		glUniform1i(pointLightSetOn, pointLightOn);
		glUniform3fv(pointLightLoc, 1, glm::value_ptr(RuberPos)); // set location of PointLight
		glUniform3fv(pointLightIntensity, 1, glm::value_ptr(PointLightIntensity)); //sets RGB values in shader

		glUniform1i(headLightSetOn, headLightOn);
		glUniform3fv(headLightLoc, 1, glm::value_ptr(RuberPos)); // set location of HeadLight
		glUniform3fv(headLightIntensity, 1, glm::value_ptr(HeadLightIntensity)); //sets RGB values in shader

		glUniform1i(ambientSetOn, ambientOn);
		glUniform3fv(ambientLightIntensity, 1, glm::value_ptr(AmbientLightIntensity));


		ModelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;
		glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(ModelViewProjectionMatrix));
		modelViewMatrix = viewMatrix * modelMatrix;
		normalMatrix = glm::mat3(modelViewMatrix);
		glBindVertexArray(vao[i]);
		glDrawArrays(GL_TRIANGLES, 0, nVertices);
	}
	//Ship
	modelMatrix = warship->getModelShipMatrix();
	ModelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(ModelViewProjectionMatrix));
	modelViewMatrix = viewMatrix * modelMatrix;
	normalMatrix = glm::mat3(modelViewMatrix);
	glBindVertexArray(vao[5]);
	glDrawArrays(GL_TRIANGLES, 0, shipVertices);

	//missiles
	for (int i = 0;i < nMissiles;i++) {
		modelMatrix = missiles[i]->getModelMissileMatrix();
		ModelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;
		glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(ModelViewProjectionMatrix));
		modelViewMatrix = viewMatrix * modelMatrix;
		normalMatrix = glm::mat3(modelViewMatrix);
		glUniformMatrix3fv(NM, 1, GL_FALSE, glm::value_ptr(normalMatrix));
		glUniformMatrix4fv(MV, 1, GL_FALSE, glm::value_ptr(ModelViewProjectionMatrix));
		glBindVertexArray(vao[6]);
		glDrawArrays(GL_TRIANGLES, 0, mVertices);
	}

	//missileSites
	for (int i = 0; i < nSites;i++) {
		modelMatrix = missileSite[i]->getModelSiteMatrix();
		ModelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;
		glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(ModelViewProjectionMatrix));
		modelViewMatrix = viewMatrix * modelMatrix;
		normalMatrix = glm::mat3(modelViewMatrix);
		glUniformMatrix3fv(NM, 1, GL_FALSE, glm::value_ptr(normalMatrix));
		glUniformMatrix4fv(MV, 1, GL_FALSE, glm::value_ptr(modelViewMatrix));
		glBindVertexArray(vao[7]);
		glDrawArrays(GL_TRIANGLES, 0, msVertices);

	}

	unumMatrix = shape[1]->getOrientationMatrix();
	duoMatrix = shape[2]->getOrientationMatrix();
	warbirdMatrix = warship->getShipOrientationMatrix();


	glutSwapBuffers();
	frameCount++;
	// see if a second has passed to set estimated fps information
	currentTime = glutGet(GLUT_ELAPSED_TIME);  // get elapsed system time
	timeInterval = currentTime - lastTime;
	if (timeInterval >= 1000) {
		sprintf(fpsStr, " fps %4d", (int)(frameCount / (timeInterval / 1000.0f)));
		lastTime = currentTime;
		frameCount = 0;
		updateTitle();
	}
}


void checkCollision() {
	objectPos = getPosition(warship->getShipOrientationMatrix());
	if (warship->isActive()) {//planets collision
		for (int i = 0; i < nSpheres;i++) {
			length = distance(objectPos, getPosition(shape[i]->getOrientationMatrix()));
			if (length < (sizeOfModel[5] + 10 + sizeOfModel[i]))
			{
				warship->destroy();

				currentCam = 0;
			}
		}
		for (int i = 0; i < nMissiles;i++)
		{
			if (missiles[i]->isMissileActive())
			{
				length = distance(objectPos, getPosition(missiles[i]->getMissileOrientationMatrix()));
				if (length < (sizeOfModel[6] + 10 + sizeOfModel[5]))
				{
					warship->destroy();
					missiles[i]->getDestroyed();
					currentCam = 0;
				}
			}
		}


	}

	for (int i = 0; i < nMissiles; i++)
	{
		if (missiles[i]->isMissileActive())
		{
			objectPos = getPosition(missiles[i]->getMissileOrientationMatrix());
			for (int j = 0; j < nSites;j++)
			{
				glm::vec3 siteTarget = getPosition(missileSite[j]->getSiteOrientationMatrix());
				length = distance(objectPos, siteTarget);

				if (length < (sizeOfModel[7] + 10 + sizeOfModel[6]))
				{
					missiles[i]->getDestroyed();
					missileSite[j]->isDestroyed();
				
					currentCam = 0;
				}
			}

		}
	}

}

void missileUpdates()
{
	for (int i = 0; i < nMissiles;i++)
	{
		if (missiles[i]->hasFired())
		{
			numberofUpdates = missiles[i]->getNumberOfUpdates();
			if (numberofUpdates > 50)
			{
				missiles[i]->setMissileActive();
			}
		}
	}
	if (missiles[0]->hasFired())
	{
		if (missiles[0]->isMissileActive()) {
			if (!missiles[0]->hasTarget())
			{

				missileLocation = missiles[0]->getMissileOrientationMatrix();
				targetLocation = missileSite[0]->getSiteOrientationMatrix();
				missilePosition = getPosition(missileLocation);
				targetPosition = getPosition(targetLocation);

				length = distance(missilePosition, targetPosition);
				targetLocation = missileSite[1]->getSiteOrientationMatrix();
				targetPosition = getPosition(targetLocation);
				if (distance(missilePosition, targetPosition) > length)
				{

					targetMissiles = missileSite[0];
				}
				else
				{

					length = distance(missilePosition, targetPosition);
					targetMissiles = missileSite[1];
				}

				if (length < 5000)
				{
					missiles[0]->towardTarget(targetMissiles->getSiteOrientationMatrix());
				}


			}
			else {
				missiles[0]->towardTarget(targetMissiles->getSiteOrientationMatrix());

			}
		}
	}
	else {
		missiles[0]->setMissileOrientation(glm::translate(warship->getShipOrientationMatrix(), glm::vec3(-33, 0, -30)));
	}

	if (missiles[1]->hasFired() == false)
	{
		glm::mat4 siteOne = missileSite[0]->getSiteOrientationMatrix();
		missiles[1]->setMissileOrientation(glm::rotate(siteOne, PI / 2, glm::vec3(1, 0, 0)));

		missileLocation = missiles[1]->getMissileOrientationMatrix();
		targetLocation = warship->getShipOrientationMatrix();
		missilePosition = getPosition(missileLocation);
		targetPosition = getPosition(targetLocation);

		length = distance(missilePosition, targetPosition);

		if (length < 5000)
		{

			missiles[1]->fireMissile();
			missiles[1]->towardTarget(warship->getShipOrientationMatrix());
			missileSite[0]->reduceMissileNumber();
		}
	}

	if (missiles[1]->isMissileActive())
	{
		missiles[1]->towardTarget(warship->getShipOrientationMatrix());
	}


	if (missiles[2]->hasFired() == false)
	{
		missiles[2]->setMissileOrientation(glm::rotate(missileSite[1]->getSiteOrientationMatrix(), PI / 2, glm::vec3(1, 0, 0)));
		missileLocation = missiles[2]->getMissileOrientationMatrix();
		targetLocation = warship->getShipOrientationMatrix();
		missilePosition = getPosition(missileLocation);
		targetPosition = getPosition(targetLocation);

		length = distance(missilePosition, targetPosition);
		if (length < 5000)
		{
			missiles[2]->fireMissile();
			missiles[2]->towardTarget(warship->getShipOrientationMatrix());
			missileSite[1]->reduceMissileNumber();
		}
	}

	if (missiles[2]->isMissileActive())
	{
		missiles[2]->towardTarget(warship->getShipOrientationMatrix());
	}

	for (int i = 0; i < nMissiles;i++)
		missiles[i]->update();

}


// Animate scene objects by updating their transformation matrices
// timerDelay = 40, or 25 updates / second
void update(int i) {
	glutTimerFunc(timerDelay, update, 1);
	for (int i = 0; i < nSpheres; i++) shape[i]->update();

	if (gravityOn)
		setGravity();
	warship->update();

	missileSite[0]->setPosition(getPosition(shape[1]->getOrientationMatrix()));
	missileSite[1]->setPosition(getPosition(shape[2]->getOrientationMatrix()));
	missileSite[0]->update();
	missileSite[1]->update();

	missiles[0]->update();

	missileUpdates();
	checkCollision();


}

//update time Quantum

void updateTimer(int timeQuantum) {
	switch (timeQuantum)
	{
	case 0:
		timerDelay = 40;
		strcpy(tqStr, " Ace");
		break;
	case 1:
		timerDelay = 100;
		strcpy(tqStr, " Novice");
		break;
	case 2:
		timerDelay = 250;
		strcpy(tqStr, " Pratice");
		break;
	case 3:
		timerDelay = 500;
		strcpy(tqStr, " Debug");
		break;
	}
}

// Quit or set the view
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 033: case 'q':  case 'Q': exit(EXIT_SUCCESS); break;
	case 'v': case 'V':  // camera
		currentCam = (currentCam + 1) % 5;
		break;
	case 'x': case 'X':  // camera
		currentCam = (currentCam - 1) % 5;
		break;
	case 'f': case 'F':
		if (!missiles[0]->hasFired() && warship->numberMissiles() != 0)
		{
			warship->reduceMissiles();
			missiles[0]->fireMissile();

		}
		break;

	case 'g': case 'G':
		if (gravityOn) {
			gravityOn = false;
			printf("gravity Off %f\n", length);
		}
		else
			gravityOn = true;
		break;
	case 't': case 'T':
		timeQ = (timeQ + 1) % numberOfTimeQuantums;
		updateTimer(timeQ);
		strcat(titleStr, tqStr);
		printf("Next TQ value \n");
		break;
	case 'w': case 'W':

		if (warship->isActive()) {

			if (warpLocation == 1)
			{

				objUMatrix = shape[1]->getOrientationMatrix();
				warship->warpShip(objUMatrix, 1);
				warpLocation = 2;
			}
			else if (warpLocation == 2)
			{
				objDMatrix = shape[2]->getOrientationMatrix();
				warship->warpShip(objDMatrix, 2);

				warpLocation = 1;
			}
		}
		break;
	case 'p': case 'P':
		pointLightOn = (pointLightOn + 1) % 2;
		break;
	case 'a': case 'A':
		ambientOn = (ambientOn + 1) % 2;
		break;
	case 'h': case 'H':
		headLightOn = (headLightOn + 1) % 2;
		break;
	case 'r': case 'R':
		if (warship->isActive() == false)
		{
			warship->restart();
			for (int i = 0; i < nMissiles;i++)
				missiles[i]->getDestroyed();
			for (int j = 0; j < nSites;j++)
				missileSite[j]->restart();
		}
	case 's': case 'S':
		if (currentSpeed == 10)
		{
			currentSpeed = 50;
			strcpy(spdStr, " spd 50");
		}
		else if (currentSpeed == 50)
		{
			currentSpeed = 200;
			strcpy(spdStr, " spd 200");
		}
		else
		{
			currentSpeed = 10;
			strcpy(spdStr, " spd 10");
		}
		strcat(titleStr, spdStr);
		break;
	}
}

void specialKeyboard(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP:
		if (glutGetModifiers() == GLUT_ACTIVE_CTRL)
			warship->setPitch(0.02f);
		else
			warship->setForward(currentSpeed);
		break;
	case GLUT_KEY_DOWN:
		if (glutGetModifiers() == GLUT_ACTIVE_CTRL)
			warship->setPitch(-0.02f);
		else
			warship->setBack(currentSpeed);
		break;
	case GLUT_KEY_LEFT:
		if (glutGetModifiers() == GLUT_ACTIVE_CTRL)
			warship->setRoll(-0.02f);
		else
			warship->setYaws(0.02f);
		break;
	case GLUT_KEY_RIGHT:
		if (glutGetModifiers() == GLUT_ACTIVE_CTRL)
			warship->setRoll(0.02f);
		else
			warship->setYaws(-0.02f);
		break;

}
}


void cleanUp(void) {
	glDeleteBuffers(nShapes, buffer);
	glDeleteBuffers(1, &ibo);
	freeTexture(texture);   // in includes465/texture.hpp
	printf("cleaned up\n");
}
int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
# ifdef __MAC__
	// Can't change the version in the GLUT_3_2_CORE_PROFILE
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_3_2_CORE_PROFILE);
# endif
# ifndef __MAC__
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
# endif
	glutInitWindowSize(800, 600);
	// set OpenGL and GLSL versions to 3.3 for Comp 465/L, comment to see highest versions
# ifndef __MAC__
	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
# endif
	glutCreateWindow("warbird : front view");
	// initialize and verify glew
	glewExperimental = GL_TRUE;  // needed my home system 
	GLenum err = glewInit();
	if (GLEW_OK != err)
		printf("GLEW Error: %s \n", glewGetErrorString(err));
	else {
		printf("Using GLEW %s \n", glewGetString(GLEW_VERSION));
		printf("OpenGL %s, GLSL %s\n",
			glGetString(GL_VERSION),
			glGetString(GL_SHADING_LANGUAGE_VERSION));
	}
	// initialize scene
	init();
	// set glut callback functions
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeyboard);
	glutTimerFunc(timerDelay, update, 1);
	glutIdleFunc(display);
	glutMainLoop();
	printf("done\n");
	return 0;
}


