#include "Scene.h"
#include <random>
#include <ctime>

const double MAX_GUN_POWER = 100;
const double MIN_GUN_POWER = 0;
const int MAX_BALLOONS = 10;

int Scene::score = 0;
int Scene::ducksRemaining = 3;
int Scene::balloonsRemaining = MAX_BALLOONS;
bool Scene::balloonsPlaced = false;

static double gravity = -32.0;
static double piOver180 = 0.01745329251;
static vec3 initialDuckPosition = vec3(0, 1.5, -95);

static default_random_engine randomEngine;


Scene::Scene() : displayListHandle(-1) { 
	this->aBalloon = Balloon::Balloon(false, vec3(0, 2, 4), vec3(0, 0, 0), vec3(1, 1, 1), vec3(0, 0, 0), vec4(1.0f, 0.0f, 0.0f, 1.0f));
	//Balloon::Balloon(bool isMoving, vec3 position, vec3 rotation, vec3 scale, vec3 velocity, vec4 color) ;
}

void Scene::runBeautyMode(int beautyMode) {
	double elapsed_time = double(glutGet(GLUT_ELAPSED_TIME)) / 1000.0;
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//set up camera at (0, 2, 0)
	gluLookAt(0, 2, 0, 0, 0, 10, 0, 1, 0);
	glPushMatrix();
	glTranslated(0, -2, 4);
	//glScaled(2, 2, 2);
	glScalef(20.0f, 20.0f, 20.0f);
	this->theWorld.renderSky(); // draw the background world		
	glPopMatrix();

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
	randomEngine.seed((unsigned long)time(nullptr)); // set random seed based on current time
	//glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	
	glLoadIdentity();

	//set up camera based on the camera mode selected:
	// --basic fixed
	// --follow duck flight
	// --first person view

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
		gluLookAt(theDuck.getPosition().x, theDuck.getPosition().y + .5, theDuck.getPosition().z, theDuck.getPosition().x, theDuck.getPosition().y, theDuck.getPosition().z + 10, 0, 1, 0);
		break;
	}

	//gluLookAt(0, 5, -100, 0, 0, 50, 0, 1, 0);
	glPushMatrix();
	this->theWorld.render(); // draw the background world
	glPopMatrix();

	//draw the balloons, from the vector of balloons
	//glPushMatrix();
	if (!balloonsPlaced)  //might want to change this eventually to be if balloons.size < 5 or something
		this->placeBalloons();
	//glTranslated(balloons[0].getPosition().x,balloons[0].getPosition().y, balloons[0].getPosition().z);
//	balloons[0].render();

	this->checkForCollisions(w);

	for (auto iter = balloons.begin(); iter != balloons.end(); ++iter) {
		glPushMatrix();
		glTranslated(iter->getPosition().x,iter->getPosition().y, iter->getPosition().z);
		if(!iter->getShouldBeRemoved())
			iter->render();
		glPopMatrix();
	}

	//glPopMatrix();
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
		if (w.getCameraMode() != FIRST_PERSON) // dont render the duck in first person!
			this->theDuck.render();
		glPopMatrix();
	}
	else { // the duck is fired
		glPushMatrix();

		//update the position and actually move the duck to that position
		theDuck.updatePosition(timeStep, gravity);
		glTranslated(theDuck.getPosition().x, theDuck.getPosition().y, theDuck.getPosition().z);
		

		//make the duck stop when it hits the ground
		if (this->theDuck.hitTheGround()) {
			this->theDuck.setVelocity(vec3(0));
		}
		//cout << this->theDuck.getPosition().x << ", " << this->theDuck.getPosition().y << ", " << this->theDuck.getPosition().z << endl;
		glScaled(.5, .5, .5);
		if (w.getCameraMode() != FIRST_PERSON && !theDuck.hitABalloon()) // dont render the duck in first person!
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
			cos(theGun.getInclinationAngle() * piOver180) * this->theGun.getGunPower()
			);

	//	cout << "Inclincation: " << theGun.getInclinationAngle() << "Rotation: " << theGun.getRotationAngle() << endl;
		this->theDuck.setVelocity(velocity);
		this->theDuck.setLaunched(true);
	}
	else {
		ducksRemaining--;
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





void Scene::resetDuck() {
	this->theDuck.setPosition(initialDuckPosition);
	this->theDuck.setVelocity(vec3(0, 0, 0));
	this->theDuck.setLaunched(false);
	this->theDuck.setHitBalloon(false);

	//generate random values between 0 and 1 for a new color
	// uses C++11 unifrom distribution engine and not c-style rand()
	// adapted from C++ Primer
	// see genRandomDouble()
	double newRed = genRandomDouble(0,1);
	double newGreen = genRandomDouble(0,1);
	double newBlue = genRandomDouble(0,1);

	//set the new color
	vec3 newColor = vec3(newRed, newGreen, newBlue);
	this->theDuck.setColor(newColor);
	
}


// functions for changing the power of the gun from 0 to 50
void Scene::increaseGunPower(double higher) {
	if (this->theGun.getGunPower() < MAX_GUN_POWER)
		this->theGun.increaseGunPower(higher);
}

void Scene::decreaseGunPower(double lower) {
	if (this->theGun.getGunPower() > MIN_GUN_POWER)
		this->theGun.decreaseGunPower(lower);
}


//function for placing balloons at semi random
// yet hittable places
void Scene::placeBalloons() {

	int xPosition, yPosition, zPosition;
	Balloon b;
	/* for each balloon wanted, generate a random position
		and assign that position to the balloon after it is constructed.
		Then add it to the balloon vector. */

	for (int i = 0; i < MAX_BALLOONS; ++i) {

		//x (horizontal) position should be within -50 to 50
		xPosition = genRandomInt(-10, 10);

		//y (vertical) position is from 10 to 75
		yPosition = genRandomInt(3, 20);


		//z (depth) position shoul be between -80 and 80
		zPosition = genRandomInt(-80, -60);

		// set the position of the balloon and its point value based on the position
		b.setPosition(vec3(xPosition, yPosition, zPosition));
		b.setPointValue(yPosition + abs(zPosition));
		b.setShouldBeRemoved(false);

		//and place it in the vector of all balloons
		this->balloons.push_back(b);
	}
	balloonsPlaced = true;
}


//generates a random double between 'low' and 'high'
// uses C++11 standard random distribution and random engine
// from C++ primer 5th ed.

double genRandomDouble(double low, double high) {
	uniform_real_distribution<double> unif(low, high);
	return unif(randomEngine);
}

int genRandomInt(int low, int high) {
	uniform_int_distribution<int> unif(low, high);
	return unif(randomEngine);
}

void Scene::checkForCollisions(Window & w) {  //(Object movingItem, Object otherObjects[], Window & w) {
			//glTranslated(0, .25, .26); quarter due to scale 0, .0625, .065
			//glutSolidSphere(1.5f, 20, 20); .375
	double duckRadius = .375;
			//glTranslated(0, -.25, 0);
			//glutSolidSphere(1.25f, 20, 20);
	double balloonRadius = 1.5;

		for (auto iter = balloons.begin(); iter != balloons.end(); ++iter) {
			double distance = glm::sqrt((theDuck.getPosition().x - iter->getPosition().x) * (theDuck.getPosition().x - iter->getPosition().x) 
				+ ((theDuck.getPosition().y - 0.0625) - (iter->getPosition().y - 0.25)) * ((theDuck.getPosition().y - 0.0625) - (iter->getPosition().y - 0.25))
				+ ((theDuck.getPosition().z - 0.065) - iter->getPosition().z) * ((theDuck.getPosition().z - 0.065) - iter->getPosition().z));
			
			if(distance <= duckRadius+balloonRadius) { //something was hit!
				iter->setShouldBeRemoved(true);
				iter->setPosition(vec3(100, -100, 0)); //set to an unhittable position
				theDuck.setHitBalloon(true);
				balloonsRemaining--;
				resetDuck();
				if (balloonsRemaining == 0) {
					gameWon = true;
					gameOver = true;
				}
				//w.setPause(true);
			}
			
		}

		//nothing was hit and the duck hit the ground
		if (theDuck.hitTheGround()) {
			ducksRemaining--;
			resetDuck();
			if (ducksRemaining == 0) 
				gameOver = true;
		}
	
}
