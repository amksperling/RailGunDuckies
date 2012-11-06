#include "Scene.h"
#include <stdio.h>  
#include <iostream>
#include <sstream> //Checka

using namespace std;


const double MAX_GUN_POWER = 100;
const double MIN_GUN_POWER = 0;
static int MAX_BALLOONS = 10;
const int MAX_DUCKS = 3;

int Scene::score = 0;
int Scene::ducksRemaining = MAX_DUCKS;
int Scene::balloonsRemaining = MAX_BALLOONS;
bool Scene::balloonsPlaced = false;
bool Scene::gameOver = false;
bool Scene::gameWon = false;

static const double gravity = -32.2;
static const double degToRad = 0.01745329251;
static const double radToDeg = 57.2957795131;
static const vec3 initialDuckPosition = vec3(0, 1.2, -94);
static const vec3 initialGunPosition = vec3(0, .5, -93);

static default_random_engine randomEngine;

//This constructor initializes all object paramaters for our objects
Scene::Scene() : displayListHandle(-1) { 
	// order for input into function \/
	// (bool isMoving, vec3 position, vec3 rotation, vec3 scale, vec3 velocity, vec4 color) ; color not currently set up, so may be ignored
	this->aBalloon = Balloon::Balloon(false, vec3(0, 2, 4), vec3(0, 0, 0), vec3(1, 1, 1), vec3(0, 0, 0), vec4(1.0f, 0.0f, 0.0f, 1.0f));
	//this->theDuck = Duckie::Duckie(false, vec3(0, 1.25, 7), vec3(0, 0, 0), vec3(2, 2, 2), vec3(0, 0, 0), vec4(1, 1, 0, 1));
	this->theGun = RailGun::RailGun(false, vec3(0, 1, 7), vec3(0, 0, 0), vec3(1, 1, 1), vec3(0, 0, 0), vec4(1.0f, 0.0f, 0.0f, 1.0f));
	this->skyBox = SkyBox::SkyBox(false, vec3(0, 0, 0), vec3(0, 0, 0), vec3(1, 1, 1), vec3(0, 0, 0), vec4(0.0f, 0.0f, 0.0f, 1.0f));
	this->theWorld = World::World(false, vec3(0, -2, 4), vec3(0, 0, 0), vec3(20, 20, 20), vec3(0, 0, 0), vec4(0.0f, 0.0f, 0.0f, 1.0f));
	this->difficulty = NORMAL;
	this->difficulty_string = "Normal";
}

void Scene::runBeautyMode(int beautyMode) {
	double elapsed_time = double(glutGet(GLUT_ELAPSED_TIME)) / 1000.0;
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//set up camera at (0, 2, 0)
	gluLookAt(0, 2, 0, 0, 0, 10, 0, 1, 0);
	glPushMatrix();
	this->theWorld.setUpForRender();
	this->theWorld.render(); // draw the background world		
	glPopMatrix();

	//draw the objects based on the input
	switch (beautyMode) {
	case DUCK_BEAUTY:
		
		glPushMatrix();
		glTranslated(0, 1.25, 7);
		glScaled(2, 2, 2);
		//this->theDuck.setUpForRender();
		glRotated(elapsed_time * 30, 0, 1, 0);
		this->theDuck.setColor(vec3(1, 1, 0));
		
		this->theDuck.render();
		glPopMatrix();
		break;

	case RAILGUN_BEAUTY:
		glPushMatrix();
		//glTranslated(0, 1, 7);
		this->theGun.setUpForRender();
		glRotated(elapsed_time * 30, 0, 1, 0);
		this->theGun.render();
		glPopMatrix();
		break;

	case BALLOON_BEAUTY:
		glPushMatrix();
		//glTranslated(0, 2, 4);
		this->aBalloon.setUpForRender();
		glRotated(elapsed_time * 30 * 2, 0, 0.8, 0.2);
		this->aBalloon.render();
		glPopMatrix();
		break;

	default:
		break;
	}//end switch

}


void Scene::runGameMode(bool runForever, double timeStep, Window & w) {
	randomEngine.seed((unsigned long)time(nullptr)); // set random seed based on current time

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
		gluLookAt(theDuck.getPosition().x, 
			theDuck.getPosition().y + .5, 
			theDuck.getPosition().z, 
			theDuck.getPosition().x, 
			theDuck.getPosition().y, 
			theDuck.getPosition().z + 10, 
			0, 1, 0);
		break;
	}

	
	//gluLookAt(0, 5, -100, 0, 0, 50, 0, 1, 0);
	glPushMatrix();
	this->skyBox.setUpForRender();
	this->skyBox.render(); // draw the background world
	glPopMatrix();

	//place the balloons, and put them in the vector
	//glPushMatrix();
	if (!balloonsPlaced)  //might want to change this eventually to be if balloons.size < 5 or something
		this->placeBalloons();

	//check if any balloons are hit
	this->checkForCollisions(w);

	// from the vector, display each balloon that is not hit
	for (auto iter = balloons.begin(); iter != balloons.end(); ++iter) {
		glPushMatrix();
		glTranslated(iter->getPosition().x,iter->getPosition().y, iter->getPosition().z);
		if(!iter->getShouldBeRemoved()) {
			iter->render();
			displayBalloonPointValue(*iter);  //display the balloon and its point value
		}
		glPopMatrix();
	}


	//draw the rail gun and the duck on top
	//push for gun
	glPushMatrix();
	glTranslated(initialGunPosition.x, initialGunPosition.y, initialGunPosition.z);
	//glRotated(180, 0, 1, 0);
	
	if (runForever)
		automateGun();
	glRotated(-theGun.getRotationAngle(), 0, 1, 0);
	glRotated(-theGun.getInclinationAngle(), 1, 0, 0);

	this->theGun.render();
	
	glPopMatrix();
	
	//push for duck
	//set its initial position
	if (!this->theDuck.isMoving()) {
		glPushMatrix();
		
		glTranslated(initialDuckPosition.x, initialDuckPosition.y, initialDuckPosition.z);

		//rotate the duck on the gun
		glRotated(-theGun.getRotationAngle(), 0, 1, 0);
		glRotated(-theGun.getInclinationAngle(), 1, 0, 0);

		//store the final launch angles for later
		theDuck.setLaunchInclination(theGun.getRotationAngle());
		theDuck.setLaunchRotation(theGun.getInclinationAngle());

		if (runForever)
			fire();

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

		//rotate the duck based on its launch angles
		glRotated(-theDuck.getLaunchRotation(), 1, 0, 0);
		glRotated(-theDuck.getLaunchInclination(), 0, 1, 0);

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

}


//If the duck isn't moving, fire it off.
// if it is moving, decrement duck count and reset the duck
void Scene::fire() {

	if(!this->theDuck.isMoving()) {
		vec3 velocity = vec3(
			-sin(theGun.getRotationAngle() * degToRad) * this->theGun.getGunPower(),
			sin(theGun.getInclinationAngle() * degToRad) * this->theGun.getGunPower(),
			cos(theGun.getInclinationAngle() * degToRad) * this->theGun.getGunPower()
			);

	//	cout << "Inclincation: " << theGun.getInclinationAngle() << "Rotation: " << theGun.getRotationAngle() << endl;
		this->theDuck.setVelocity(velocity);
		this->theDuck.setLaunched(true);
	}
	else {
		ducksRemaining--;
		if (ducksRemaining == 0) {
			gameOver = true;
			resetGame();
		}
		else 
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




//plsce the duck back on the gun and give it a new color
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


// functions for changing the power of the gun from 0 to 100
void Scene::increaseGunPower(double higher) {
	if (this->theGun.getGunPower() < MAX_GUN_POWER)
		this->theGun.increaseGunPower(higher);
}

void Scene::decreaseGunPower(double lower) {
	if (this->theGun.getGunPower() > MIN_GUN_POWER)
		this->theGun.decreaseGunPower(lower);
}

void Scene::cycleDifficulty() {
	switch (this->getDifficulty()) {
	case EASY:
		this->difficulty = NORMAL;
		this->difficulty_string = "Normal";
		MAX_BALLOONS = 10;
		resetGame();
		break;

	case NORMAL:
		this->difficulty = HARD;
		this->difficulty_string = "Hard";
		MAX_BALLOONS = 20;
		resetGame();
		break;

	case HARD:
		this->difficulty = EASY;
		this->difficulty_string = "Easy";
		MAX_BALLOONS = 3;
		resetGame();
		break;
	}
}


//function for placing balloons at semi random
// yet hittable places
void Scene::placeBalloons() {
	int xLeft, xRight, yBottom, yTop, zNear, zFar;

	//set number of balloons and range of positions based on difficulty
	switch (this->getDifficulty()) {

	case EASY:
		
		xLeft = -10;
		xRight = 10;
		yBottom = 3;
		yTop = 15;
		zNear = -80;
		zFar = -70;
		break;

	case NORMAL:
		
		xLeft = -10;
		xRight = 10;
		yBottom = 3;
		yTop = 18;
		zNear = -80;
		zFar = -60;
		break;

	case HARD:
		
		xLeft = -15;
		xRight = 15;
		yBottom = 3;
		yTop = 25;
		zNear = -80;
		zFar = -20;
		break;
	}

	int xPosition, yPosition, zPosition;
	Balloon b = Balloon::Balloon(false, vec3(0, 2, 4), vec3(0, 0, 0), vec3(1, 1, 1), vec3(0, 0, 0), vec4(1.0f, 0.0f, 0.0f, 1.0f));
	/* for each balloon wanted, generate a random position
		and assign that position to the balloon after it is constructed.
		Then add it to the balloon vector. */

	for (int i = 0; i < MAX_BALLOONS; ++i) {

		//generate balloon positions based on difficulty level		
		xPosition = genRandomInt(xLeft, xRight);
		
		yPosition = genRandomInt(yBottom, yTop);

		zPosition = genRandomInt(zNear, zFar);

		// set the position of the balloon and its point value based on the position
		b.setPosition(vec3(xPosition, yPosition, zPosition));
		
		//set point value based on distance from the gun
		//since all z positions are negative, the farther away + higher = more points
		b.setPointValue(100 + zPosition + yPosition);
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
	//Quite possible and likely that this function will break if you scale differently in different axi
			//glTranslated(0, .25, .26); quarter due to scale 0, .0625, .065
			//glutSolidSphere(1.5f, 20, 20); .375
	double duckRadius = .375;// * theDuck.getScale().x; re-add this code when the duck scale is implemented
			//glTranslated(0, -.25, 0);
			//glutSolidSphere(1.3f, 20, 20);
	double balloonRadius = 1.3;

		for (auto iter = balloons.begin(); iter != balloons.end(); ++iter) {
			balloonRadius = 1.3 * iter->getScale().y; 
			double distance = glm::sqrt((theDuck.getPosition().x - iter->getPosition().x) * (theDuck.getPosition().x - iter->getPosition().x) 
				+ ((theDuck.getPosition().y - 0.0625 /* theDuck.getScale().y */) - (iter->getPosition().y - 0.25 * iter->getScale().y)) * ((theDuck.getPosition().y - 0.0625 /* theDuck.getScale().y*/) - (iter->getPosition().y - 0.25  * iter->getScale().y))
				+ ((theDuck.getPosition().z - 0.065 /* theDuck.getScale().z */) - iter->getPosition().z) * ((theDuck.getPosition().z - 0.065 /* theDuck.getScale().z*/) - iter->getPosition().z));
			
			if(distance <= duckRadius+balloonRadius) { //something was hit!
				iter->setShouldBeRemoved(true);
				iter->setPosition(vec3(300, -300, 0)); //set to an unhittable position, will be cleared later
				theDuck.setHitBalloon(true);
				score += iter->getPointValue();
				balloonsRemaining--;
				resetDuck();

				//you won the game!
				if (balloonsRemaining == 0) {
					gameWon = true;
					gameOver = true;
					resetGame();
					return; //return so we don't check collisions on an empty balloon vector
				}
				
			}
			
		}

		//nothing was hit and the duck hit the ground
		if (theDuck.hitTheGround()) {
			ducksRemaining--;
			resetDuck();
			if (ducksRemaining == 0) {
				gameOver = true;
				resetGame();
			}
		}
	
}


void Scene::resetGame() {

	if (!gameWon) {	
		//only reset score on loss
		this->score = 0;
	}
		
	this->balloonsPlaced = false;
	this->gameOver = false;
	this->gameWon = false;
	this->balloonsRemaining = MAX_BALLOONS;
	this->ducksRemaining = MAX_DUCKS;
	
	this->theDuck.setColor(vec3(1, 1, 0));
	resetDuck();

	//chear the balloon vector to keep memory low
	balloons.clear();
}

void Scene::displayBalloonPointValue(Balloon & b) {
	
	//get its point value and convert to a string
	string pointValue = static_cast<ostringstream*>( &(ostringstream() << b.getPointValue()) )->str();
	
	glPushMatrix();
	glTranslated(1, 1, 0); //translate a little so it appears centered over the balloon
	glRotated(180, 0, 1, 0); // rotate so text isn't mirrored
	glScaled(.01, .01, 1);  //scale properly
	glColor3f(0, 0, 0);		// set color to black
	//actually draw the score string (as a c string)
	glutStrokeString(GLUT_STROKE_MONO_ROMAN,(unsigned char *)pointValue.c_str());
	glPopMatrix();

}


//Finds the closest balloon and moves the railgun to try and hit it
void Scene::automateGun() {

	//closestTargetPosition will become a balloon position
	vec3 closestTargetPosition = vec3(1000);

	//find the distance from the gun to the target (without using pow()!)
	double distanceToClosestTarget = sqrt(
		(closestTargetPosition.x - initialGunPosition.x) * (closestTargetPosition.x - initialGunPosition.x) + 
		(closestTargetPosition.y - initialGunPosition.y) * (closestTargetPosition.y - initialGunPosition.y) +
		(closestTargetPosition.z - initialGunPosition.z) * (closestTargetPosition.z - initialGunPosition.z)
	);

	//find the closest balloon to the gun
	for (auto iter = balloons.begin(); iter != balloons.end(); ++iter) {

		//only check if it's in play
		if (iter->getShouldBeRemoved() == false) {
			
			//calculate the distance from gun to balloon
			double balloonDistance = sqrt(
				(iter->getPosition().x - initialGunPosition.x) * (iter->getPosition().x - initialGunPosition.x) + 
				(iter->getPosition().y - initialGunPosition.y) * (iter->getPosition().y - initialGunPosition.y) +
				(iter->getPosition().z - initialGunPosition.z) * (iter->getPosition().z - initialGunPosition.z)
			);

			//if the distance is less than the closest, then make it the closest
			if (balloonDistance < distanceToClosestTarget) {
				distanceToClosestTarget = balloonDistance;
				closestTargetPosition = iter->getPosition();
			}
		}
	}

	


	//calculate the angles needed to hit. using atan2 because I overheard Perry talking about it at the last BBQ
	double targetRotation = -atan2((closestTargetPosition.x - initialGunPosition.x), (closestTargetPosition.z - initialGunPosition.z) ) * radToDeg;

	//compensate for rotation a little bit to provide added accuracy
	if (targetRotation < 0)
		targetRotation += 2;
	else
		targetRotation -= 2;

	// the inclination includes a slight offset (based on the distance to the target) to compensate for the duck's drop over time
	// its not perfect, but it works on most targets
	double targetInclination = asin((closestTargetPosition.y - initialGunPosition.y)/ distanceToClosestTarget) * radToDeg + .3 * distanceToClosestTarget;

	//move the gun into position
	theGun.setInclinationAngle(targetInclination);
	theGun.setRotationAngle(targetRotation);

}

