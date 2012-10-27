#include "Scene.h"

static float launchSpeed = 30;
static double old_time;
static double new_time;

Scene::Scene() : displayListHandle(-1) { }

void Scene::runBeautyMode(int beautyMode) {
	double elapsed_time = double(glutGet(GLUT_ELAPSED_TIME)) / 1000.0;
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//set up camera at (0, 2, 0)
	gluLookAt(0, 2, 0, 0, 0, 10, 0, 1, 0);
	glPushMatrix();
	glTranslated(0, 2, 4);
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


void Scene::runGameMode(bool runForever, double & elapsed_time, Window & w) {
	double startTime = elapsed_time;



	//glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	
	glLoadIdentity();

	//set up camera at (0, 2, 0)

	switch (w.getCameraMode()) {
	case MAIN:
		gluLookAt(0, 5, -100, 0, 0, 50, 0, 1, 0);
		break;

	case FLIGHT_FOLLOWER:
		gluLookAt(0, 5, -100, theDuck.getPosition().x, theDuck.getPosition().y, theDuck.getPosition().z, 0, 1, 0);
		break;

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
	glTranslated(0, .5, -94);
	glRotated(180, 0, 1, 0);
	glRotated(theGun.getInclinationAngle(), 1, 0, 0);
	glRotated(-theGun.getRotationAngle(), 0, 1, 0);
	this->theGun.drawRailGun();
	glPopMatrix();

	//push for duck
	//set its initial position
	if (!this->theDuck.isMoving()) {
		glPushMatrix();
		glTranslated(0, 2, -96);
		glRotated(-theGun.getInclinationAngle(), 1, 0, 0);
		glRotated(-theGun.getRotationAngle(), 0, 1, 0);
		glScaled(.5, .5, .5);
		this->theDuck.render();
		glPopMatrix();
	}
	else {
		glPushMatrix();
		theDuck.updatePosition(theDuck.getPosition(), elapsed_time);
		glTranslated(theDuck.getPosition().x, theDuck.getPosition().y, theDuck.getPosition().z);
		glScaled(.5, .5, .5);
		theDuck.render();
		glPopMatrix();
	}
	

	//glPopMatrix();
}

void Scene::fire() {

	vec3 velocity = vec3(
		-sin(theGun.getRotationAngle()) * launchSpeed,
		sin(theGun.getInclinationAngle()) * launchSpeed,
		cos(theGun.getInclinationAngle()) * launchSpeed
		);

	//this->theDuck.setVelocity(velocity);
	if (!theDuck.isMoving())
		this->theDuck.setInitVelocity(.01, theGun.getInclinationAngle());
	//else
		//reset duck
}

void Scene::moveRailGun(int x, int y, Window & w) {

	double futureXAngle;
	double futureYAngle;

	if((double)x < ((double)w.getWidth())/2) futureXAngle = ((double)w.getWidth()/2 - (double)x)/((double)w.getWidth()/2) * -90;
	else futureXAngle = (((double)x - ((double)w.getWidth()/2))/((double)w.getWidth()/2)) * 90;

	futureYAngle = ((double)w.getHeight() - (double)y)/((double)w.getHeight()) * 90;
	
	this->theGun.setRotationAngle(futureXAngle);
	this->theGun.setInclinationAngle(futureYAngle);
}