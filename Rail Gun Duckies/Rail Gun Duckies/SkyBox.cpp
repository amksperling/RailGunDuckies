#include <GL/freeglut.h>
#include "SkyBox.h"

GLuint SkyBox::displayListHandle;

SkyBox::SkyBox() {
	this->displayListHandle = (GLuint) -1;
}

SkyBox::SkyBox(bool isMoving, vec3 position, vec3 rotation, vec3 scale, vec3 velocity, vec4 color) :
	Object(isMoving, position, rotation, scale, velocity, color) {
	this->displayListHandle = (GLuint) -1;
}


void SkyBox::render() {
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


// draw one side of the sky box
//its a gradeint color from dark blue to light blue
// RGB Color values from http://www.tayloredmktg.com/rgb/
void SkyBox::skySide() {
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glBegin(GL_QUADS);

	glNormal3f(0, 1, 0);
	glColor3ub(0, 191, 255);
	glVertex2d(-100, 100);
	glVertex2d(100, 100);
	glColor3ub(0, 0, 100);
	glVertex2d(100, 0);
	glVertex2d(-100, 0);

	glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

//the top is one color, as opposed to a gradient
void SkyBox::skyTop() {
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glBegin(GL_QUADS);

	glNormal3f(0, 1, 0);
	glColor3ub(0, 191, 255);
	glVertex2d(-100, 100);
	glVertex2d(100, 100);
	//glColor3ub(250, 250, 250);
	glVertex2d(100, 0);
	glVertex2d(-100, 0);

	glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

// draw the ground from -100 to 100
// gradient from green to dark green
void SkyBox::ground() {
	glDisable(GL_LIGHTING);

	glPushMatrix();
	glTranslated(0, 0, -100);
	glRotated(90, 1, 0, 0);
	glBegin(GL_QUADS);


	glColor3ub(0, 100, 0);
	glNormal3f(0, 1, 0);
	glVertex2d(-100, 0);
	glColor3ub(0, 30, 0);
	glVertex2d(-100, 200);
	glVertex2d(100, 200);
	glColor3ub(0, 100, 0);
	glVertex2d(100, 0);

	glEnd();

	glPopMatrix();
	glEnable(GL_LIGHTING);

}

//draw a skybox from the sky sides
void SkyBox::skyBox() {
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


	// need something different for the top
	glPushMatrix();
	glTranslated(0, 100, -100);
	glScaled(1, 1, 2);
	glRotated(-90, 1, 0, 0);
	glRotated(180, 0, 0, 1);
	skyTop();
	glPopMatrix();

	glPopMatrix();

}

