#include "Scene.h"



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
	

	


	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	
	glLoadIdentity();

	//set up camera at (0, 2, 0)
	gluLookAt(0, 2, 0, 0, 0, 10, 0, 1, 0);
	glPushMatrix();
	this->theWorld.render();
	//renderWorld(); // draw the background world
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

	glPopMatrix();

	//glPushMatrix();
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//glOrtho(0, 1280, 0, 720, 1, 10);
	//glLoadIdentity();
	//glutStrokeString(GLUT_STROKE_MONO_ROMAN, string);
	glPopMatrix();
}


void Scene::runGameMode(bool runForever, double & elapsed_time) {
	double startTime = elapsed_time;


	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	
	glLoadIdentity();

	//set up camera at (0, 2, 0)
	gluLookAt(0, 5, -100, 0, 0, 50, 0, 1, 0);
	glPushMatrix();
	renderWorld(); // draw the background world
	glPopMatrix();

	//draw the rail gun and the duck on top
	//push for gun
	glPushMatrix();
	glTranslated(0, .5, -94);
	glRotated(180, 0, 1, 0);
	this->theGun.drawRailGun();
	glPopMatrix();

	//push for duck
	//set its initial position
	if (!this->theDuck.isMoving()) {
		glPushMatrix();
		glTranslated(0, 2.5, -95);
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
	

	glPopMatrix();
}

void Scene::fire() {
	this->theDuck.setInitVelocity(.01, theGun.getInclinationAngle());
}

void Scene::moveRailGun(int x, int y) {
	this->theGun.setInclinationAngle(y);
	this->theGun.setRotationAngle(x);
}