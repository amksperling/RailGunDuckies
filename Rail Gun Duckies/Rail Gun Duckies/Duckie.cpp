#include <gl/freeglut.h>
#include "Duckie.h"


Duckie::Duckie() {

}

Duckie::~Duckie() {

}

void Duckie::render() {

	GLUquadric *q = gluNewQuadric();
	
	
	// draw the body
	glPushMatrix();
	glScaled(1, .7, 1.2);
	glColor3d(1, 1, 0);
	gluSphere(q,1,100,100);
	glPopMatrix();

	// draw the head
	glPushMatrix();
	glScaled(.4, .4, .4);
	glTranslated(0, 1.8, 2.2);
	gluSphere(q,1,100,100);
	glPopMatrix();

	// draw the wings
	glPushMatrix();
	glScaled(.3, .4, .75);
	glColor3d(1, 0, 0);
	glTranslated(3, 0, 0);
	gluSphere(q, 1, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glScaled(.3, .4, .75);
	glColor3d(1, 0, 0);
	glTranslated(-3, 0, 0);
	gluSphere(q, 1, 100, 100);
	glPopMatrix();


	// draw the eyes
	glPushMatrix();
	glScaled(.1, .1, .1);
	glColor3d(1, 1, 1);
	glTranslated(2, 10, 11.3);
	gluSphere(q, 1, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glScaled(.1, .1, .1);
	glColor3d(1, 1, 1);
	glTranslated(-2, 10, 11.3);
	gluSphere(q, 1, 100, 100);
	glPopMatrix();


	// draw the beak
	glPushMatrix();
	glScaled(.25, .1, .5);
	glColor3d(1, .5, 0);
	glTranslated(0, 7.5, 2.5);
	gluCylinder(q, 1, 0, 1, 100, 100);

	// draw lines separating beak
	//glColor3d(0, 0, 0);
	//glBegin(GL_LINE);
	//glVertex3d(2, 7.5, .5);
	//glVertex3d(3, 7.5, 1);
	//glEnd();
	//glPopMatrix();


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
