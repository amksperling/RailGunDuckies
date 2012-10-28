#include "Scene.h"
#include <random>
#include <ctime>

const double MAX_GUN_POWER = 50;
const double MIN_GUN_POWER = 0;

static double gravity = -.1;
static double piOver180 = 0.01745329251;
static vec3 initialDuckPosition = vec3(0, 1.5, -95);

Scene::Scene() : displayListHandle(-1) { }

void Scene::renderWorld() {
	if (this->displayListHandle == GLuint(-1)) {
		this->displayListHandle = glGenLists(1);
		glNewList(this->displayListHandle, GL_COMPILE);

		// draw the skybox
		skyBox();
		// draw the ground
		ground();
		glEndList();
	}
	glCallList(this->displayListHandle);
}


void Scene::skySide() {
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glBegin(GL_QUADS);

	glNormal3f(0, 1, 0);
	glColor3ub(255, 255, 255);
	glVertex2d(-100, 100);
	glVertex2d(100, 100);
	glColor3ub(0, 0, 150);
	glVertex2d(100, 0);
	glVertex2d(-100, 0);
	
	glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void Scene::ground() {
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glBegin(GL_QUADS);
	glTranslated(0, 0, -100);
	glRotated(90, 1, 0, 0);
	glColor3ub(0, 100, 0);
	glNormal3f(0, 1, 0);
	glVertex2d(-100, 0);
	glColor3ub(0, 40, 0);
	glVertex2d(-100, 200);
	glVertex2d(100, 200);
	glColor3ub(0, 100, 0);
	glVertex2d(100, 0);

	glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void Scene::skyBox() {
	glPushMatrix();

	glPushMatrix();
	glTranslated(0, 0, 100);
	skySide();
	glPopMatrix();
	glRotated(90, 0 , 1, 0);

	glPushMatrix();
	glTranslated(0, 0, 100);
	skySide();
	glPopMatrix();
	glRotated(90, 0 , 1, 0);

	glPushMatrix();
	glTranslated(0, 0, 100);
	skySide();
	glPopMatrix();
	glRotated(90, 0 , 1, 0);

	glPushMatrix();
	glTranslated(0, 0, 100);
	skySide();
	glPopMatrix();
	glRotated(90, 0 , 1, 0);


	// need something for the top
	glPushMatrix();
	glTranslated(0, 100, 0);
	glRotated(-90, 1, 0, 0);
	glRotated(180, 0, 0, 1);
	skySide();
	glPopMatrix();

	glPopMatrix();

}

//// pla
//void Scene::placeGun() {
//	Balloon a;
//
//	glPushMatrix();
//	glTranslated(0, .5, 0);
////	this->theGun.render();
//	glTranslated(0, 10, 20);
//	this->balloons.push_back(a);
//	this->balloons.at(0).render();
//	glTranslated(-5, 0 ,0);
//	this->balloons.at(0).render();
//	glTranslated(10, 0 ,0);
//	this->balloons.at(0).render();
//
//	glPopMatrix();
//
//}
//
//
//void Scene::placeDuck() {
//	glPushMatrix();
//
//	glTranslated(0, 1, 0);
//	this->theDuck.render();
//	glPopMatrix();
//
//}

////Display the properly lit duck
////Duck beauty mode
//void Scene::duckBeauty() {
//	double elapsed_time = double(glutGet(GLUT_ELAPSED_TIME)) / 1000.0;
//
//	glPushMatrix();
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//
//	gluLookAt(0, 2, 0, 0, 0, 10, 0, 1, 0);
//	glPushMatrix();
//	renderWorld();
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslated(0, 1, 7);
//	glScaled(2, 2, 2);
//	glRotated(elapsed_time * 30, 0, 1, 0);
//	this->theDuck.render();
//	glPopMatrix();
//
//	glPopMatrix();
//}
//
////Rail Gun beauty mode
//void Scene::railGunBeauty() {
//	double elapsed_time = double(glutGet(GLUT_ELAPSED_TIME)) / 1000.0;
//
//	glPushMatrix();
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//
//	gluLookAt(0, 2, 0, 0, 0, 10, 0, 1, 0);
//	glPushMatrix();
//	renderWorld();
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslated(0, 1, 7);
//	glRotated(elapsed_time * 30, 0, 1, 0);
//	this->theGun.render();
//	glPopMatrix();
//
//	glPopMatrix();
//}
//
////Balloon beauty mode
//void Scene::balloonBeauty() {
//	double elapsed_time = double(glutGet(GLUT_ELAPSED_TIME)) / 1000.0;
//
//	glPushMatrix();
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//
//	gluLookAt(0, 2, 0, 0, 0, 10, 0, 1, 0);
//	glPushMatrix();
//	renderWorld();
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslated(0, 3, 5);
//	glRotated(elapsed_time * 30, 0, 1, 0);
//	this->aBalloon.render();
//	glPopMatrix();
//
//	glPopMatrix();
//}

void Scene::runBeautyMode(int beautyMode) {
	double elapsed_time = double(glutGet(GLUT_ELAPSED_TIME)) / 1000.0;
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//set up camera at (0, 2, 0)
	gluLookAt(0, 2, 0, 0, 0, 10, 0, 1, 0);
//	glPushMatrix();
	this->theWorld.render(); // draw the background world		
	//glPopMatrix();

	//draw the objects based on the input
	switch (beautyMode) {
	case DUCK_BEAUTY:
		
		glPushMatrix();
		glTranslated(0, 1.25, 7);
		glScaled(2, 2, 2);
		glRotated(elapsed_time * 30, 0, 1, 0);
		this->theDuck.setColor(vec3(1, 1, 0));
		this->theDuck.render();
		glPopMatrix();
		break;

	case RAILGUN_BEAUTY:
		glPushMatrix();
		glTranslated(0, 1, 7);
		glRotated(elapsed_time * 30, 0, 1, 0);
		this->theGun.drawRailGun();
		glPopMatrix();
		break;

	case BALLOON_BEAUTY:
		glPushMatrix();
		glTranslated(0, 2, 4);
		glRotated(elapsed_time * 30, 0, 1, 0);
		this->aBalloon.render();
		glPopMatrix();
		break;

	default:
		break;
	}//end switch

	//glPopMatrix();

	//glPushMatrix();
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//glOrtho(0, 1280, 0, 720, 1, 10);
	//glLoadIdentity();
	//glutStrokeString(GLUT_STROKE_MONO_ROMAN, string);
	//glPopMatrix();
}


void Scene::runGameMode(bool runForever, double timeStep, Window & w) {

	//glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	
	glLoadIdentity();


	//set up camera at (0, 2, 0)

	switch (w.getCameraMode()) {

	//basic fixed camera position
	case MAIN:
		gluLookAt(0, 5, -100, 0, 0, 50, 0, 1, 0);
		break;

	// camera stays in one position but looks at the position of the duck
	case FLIGHT_FOLLOWER:
		gluLookAt(0, 5, -100, theDuck.getPosition().x, theDuck.getPosition().y, theDuck.getPosition().z, 0, 1, 0);
		break;

	// camera is always at the position of the duck and looks foward "through the duck's eyes"
	case FIRST_PERSON:
		gluLookAt(theDuck.getPosition().x, theDuck.getPosition().y, theDuck.getPosition().z, theDuck.getPosition().x, theDuck.getPosition().y, theDuck.getPosition().z + 10, 0, 1, 0);
		break;
	}

	//gluLookAt(0, 5, -100, 0, 0, 50, 0, 1, 0);
	glPushMatrix();
	this->theWorld.render(); // draw the background world
	glPopMatrix();

	//draw the rail gun and the duck on top
	//push for gun
	glPushMatrix();
	glTranslated(0, .5, -93);
	glRotated(180, 0, 1, 0);
	glRotated(theGun.getInclinationAngle(), 1, 0, 0);
	glRotated(-theGun.getRotationAngle(), 0, 1, 0);
	this->theGun.drawRailGun();
	
	glPopMatrix();

	//push for duck
	//set its initial position
	if (!this->theDuck.isMoving()) {
		glPushMatrix();
		glTranslated(initialDuckPosition.x, initialDuckPosition.y, initialDuckPosition.z);
		glRotated(-theGun.getInclinationAngle(), 1, 0, 0);
		glRotated(-theGun.getRotationAngle(), 0, 1, 0);
		glScaled(.5, .5, .5);
		this->theDuck.render();
		glPopMatrix();
	}
	else { // the duck is fired
		glPushMatrix();
		theDuck.updatePosition(timeStep, gravity);
		glTranslated(theDuck.getPosition().x, theDuck.getPosition().y, theDuck.getPosition().z);
		//GLfloat angleX = -glm::asin(theDuck.getVelocity().x / launchSpeed) / piOver180;
		//GLfloat angleY = glm::asin(theDuck.getVelocity().y / launchSpeed) / piOver180;
		//GLfloat angleZ = -glm::acos(duckyVelocity.z / launchSpeed) / radianConversion;

		//glRotatef(angleX, 0, 1, 0);
		//glRotatef(angleY, 0, 0, 1);
		if (this->theDuck.hitTheGround()) {
			this->theDuck.setVelocity(vec3(0));
		}
		cout << this->theDuck.getPosition().x << ", " << this->theDuck.getPosition().y << ", " << this->theDuck.getPosition().z << endl;
		glScaled(.5, .5, .5);
		theDuck.render();
		glPopMatrix();
	}
	

	//glPopMatrix();
}

void Scene::fire() {

	if(!this->theDuck.isMoving()) {
		vec3 velocity = vec3(
			-sin(theGun.getRotationAngle() * piOver180) * this->theGun.getGunPower(),
			sin(theGun.getInclinationAngle() * piOver180) * this->theGun.getGunPower(),
			-cos(theGun.getInclinationAngle() * piOver180) * this->theGun.getGunPower()
			);

		cout << "Inclincation: " << theGun.getInclinationAngle() << "Rotation: " << theGun.getRotationAngle() << endl;
		this->theDuck.setVelocity(velocity);
		this->theDuck.setLaunched(true);
	}
	else {
		resetDuck();
	}
}

void Scene::moveRailGun(int x, int y, const Window & w) {

	double futureXAngle;
	double futureYAngle;

	if((double)x < ((double)w.getWidth())/2) futureXAngle = ((double)w.getWidth()/2 - (double)x)/((double)w.getWidth()/2) * -90;
	else futureXAngle = (((double)x - ((double)w.getWidth()/2))/((double)w.getWidth()/2)) * 90;

	futureYAngle = ((double)w.getHeight() - (double)y)/((double)w.getHeight()) * 90;
	
	this->theGun.setRotationAngle(futureXAngle);
	this->theGun.setInclinationAngle(futureYAngle);
}

double randomnumgen(double low, double high);

void Scene::resetDuck() {
	this->theDuck.setPosition(initialDuckPosition);
	this->theDuck.setVelocity(vec3(0, 0, 0));
	this->theDuck.setLaunched(false);

	double lower_bound = 0;
	double upper_bound = 1;
//	theDuck.setDLH();
	std::uniform_real_distribution<double> unif(lower_bound,upper_bound);
	std::default_random_engine re;
	srand(time(0));
	double newRed = rand() * 1 / double(RAND_MAX) + 0 ;//unif(re);
	double newGreen = rand() * 1 / double(RAND_MAX) + 0;//unif(re);
	double newBlue = rand() * 1 / double(RAND_MAX) + 0;//unif(re);

//	this->theDuck.setDLH();
	vec3 newColor = vec3(newRed, newGreen, newBlue);
	this->theDuck.setColor(newColor);
	
}

double randomnumgen(double low, double high)
{
  double range=(high-low);
  double num = fmod(rand(),range)+low;
  return(num);
}

void Scene::increaseGunPower(double higher) {
	if (this->theGun.getGunPower() < MAX_GUN_POWER)
		this->theGun.increaseGunPower(higher);
}

void Scene::decreaseGunPower(double lower) {
	if (this->theGun.getGunPower() > MIN_GUN_POWER)
		this->theGun.decreaseGunPower(lower);
}