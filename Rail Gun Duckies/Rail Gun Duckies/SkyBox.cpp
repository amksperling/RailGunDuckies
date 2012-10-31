#include <gl/freeglut.h>
#include "SkyBox.h"

GLuint SkyBox::displayListHandle;

SkyBox::SkyBox() {
	this->displayListHandle = (GLuint) -1;
}

SkyBox::SkyBox(bool isMoving, vec3 position, vec3 rotation, vec3 scale, vec3 velocity, vec4 color) : Object(isMoving, position, rotation, scale, velocity, color){
	this->displayListHandle = (GLuint) -1;
} 

const float PI = 3.14159265f;

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
void SkyBox::skySide() {
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

// draw the ground from -100 to 100
void SkyBox::ground() {
	glDisable(GL_LIGHTING);

	glPushMatrix();
	glTranslated(0, 0, -100);
	glRotated(90, 1, 0, 0);
	glBegin(GL_QUADS);
	

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


	// need something for the top
	glPushMatrix();
	glTranslated(0, 100, -100);
	glScaled(1, 1, 2);
	glRotated(-90, 1, 0, 0);
	glRotated(180, 0, 0, 1);
	skySide();
	glPopMatrix();

	glPopMatrix();

}