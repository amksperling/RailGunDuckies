#include "Scene.h"



Scene::Scene() : displayListHandle(-1) { }

void Scene::render() {
	if (this->displayListHandle == GLuint(-1)) {
		this->displayListHandle = glGenLists(1);
		glNewList(this->displayListHandle, GL_COMPILE);

		// draw the skybox
		skyBox();
		// draw the ground
		ground();
		placeGun();
		placeDuck();
		glEndList();
	}
	glCallList(this->displayListHandle);
}


void Scene::background() {
	glPushMatrix();
	glBegin(GL_QUADS);

	glNormal3f(0, 1, 0);
	glColor3d(1, 1, 1);
	glVertex2d(-100, 100);
	glVertex2d(100, 100);
	glColor3d(0, 0, 1);
	glVertex2d(100, 0);
	glVertex2d(-100, 0);
	
	glEnd();
	glPopMatrix();
}

void Scene::ground() {
	glPushMatrix();
	glBegin(GL_QUADS);

	glRotated(90, 1, 0, 0);
	glColor3d(0, 1, 0);
	glNormal3f(0, 1, 0);
	glVertex2d(-200, 200);
	glVertex2d(200, 200);
	glVertex2d(200, -200);
	glVertex2d(-200, -200);

	glEnd();
	glPopMatrix();
}

void Scene::skyBox() {
	glPushMatrix();
	glTranslated(0, 0, 100);
	background();
	glPopMatrix();
	glRotated(90, 0 , 1, 0);

	glPushMatrix();
	glTranslated(0, 0, 100);
	background();
	glPopMatrix();
	glRotated(90, 0 , 1, 0);

	glPushMatrix();
	glTranslated(0, 0, 100);
	background();
	glPopMatrix();
	glRotated(90, 0 , 1, 0);

	glPushMatrix();
	glTranslated(0, 0, 100);
	background();
	glPopMatrix();
	glRotated(90, 0 , 1, 0);

	// need something for the top


}

// pla
void Scene::placeGun() {
	Balloon a;

	glPushMatrix();
	glTranslated(0, .5, 0);
//	this->theGun.drawRailGun();
	glTranslated(0, 10, 20);
	this->balloons.push_back(a);
	this->balloons.at(0).render();
	glTranslated(-5, 0 ,0);
	this->balloons.at(0).render();
	glTranslated(10, 0 ,0);
	this->balloons.at(0).render();

	glPopMatrix();

}


void Scene::placeDuck() {
	glPushMatrix();

	glTranslated(0, 1, 0);
	this->theDuck.render();
	glPopMatrix();

}