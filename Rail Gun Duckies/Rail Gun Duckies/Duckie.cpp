#include <gl/freeglut.h>
#include "Duckie.h"


Duckie::Duckie() {

}

Duckie::~Duckie() {

}

void Duckie::render() {

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(0, 0, -5);

	GLUquadric *q = gluNewQuadric();
	
	
	// draw the body
	glPushMatrix();
	glScaled(1.3, .7, 1);
	
//	glRotated(theta, 0, 1, 0);
	glColor3d(1, 1, 0);
	gluSphere(q,1,100,100);
	glPopMatrix();

	// draw the head
	glPushMatrix();
	glScaled(.4, .4, .4);
//	glRotated(theta, 0, 1, 0);
	glTranslated(0, 1.8, 2.3);
	gluSphere(q,1,100,100);
	glPopMatrix();

	// draw the wings
	glPushMatrix();
	glScaled(.7, .3, .01);
//	glRotated(theta, 0, 1, 0);
	glColor3d(1, 0, 0);
	glTranslated(1.5, 0, 0);
	gluSphere(q, 1, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glScaled(.7, .3, .01);
//	glRotated(theta, 0, 1, 0);
	glColor3d(1, 0, 0);
	glTranslated(-1.5, 0, 0);
	gluSphere(q, 1, 100, 100);
	glPopMatrix();

	gluDeleteQuadric(q);
}

double Duckie::getMass() const {
	return this->mass;
}

double Duckie::getVelocity() const {
	return this->velocity;
}

double Duckie::getAcceleration() const {
	return this->acceleration;
}

static void Render() {
	GLUquadric *q = gluNewQuadric();

	// set up the inital matricies
	glMatrixMode(GL_MODELVIEW);
	
	glLoadIdentity();
	// create the body...
//	glPushMatrix();
	gluSphere(q, 1, 100, 100);
	glScaled(1, .75, .75);
//	glPopMatrix();
}