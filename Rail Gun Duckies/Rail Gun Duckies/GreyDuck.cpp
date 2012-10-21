
#include "GreyDuck.h"

static GLuint duckList;

static GLUquadric *q = gluNewQuadric();

GreyDuck::GreyDuck() {
	this->displayListHandle = -1;
}

void GreyDuck::render() {
			
	//set up material parameters
	//numbers from http://devernay.free.fr/cours/opengl/materials.html
	//
	//yellow plastic
	GLfloat material_ambient[] = {.00, .00, 0, 1};
	GLfloat material_diffuse[] = { .01, .01, .01, 1 };
    GLfloat material_specular[] = { .5, .5, .5, 1 };
    GLfloat material_shininess[] = { .15 * 128 };

	//yellow rubber
	//GLfloat material_ambient[] = {.05, .05, 0, 1};
	//GLfloat material_diffuse[] = { .5, .5, .4, 1 };
	//GLfloat material_specular[] = { .7, .7, .04, 1 };
	//GLfloat material_shininess[] = { .078125 * 128 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);

	if (this->displayListHandle == GLuint(-1)) {
		this->displayListHandle = glGenLists(1);
		glNewList(this->displayListHandle, GL_COMPILE);

		if (q) {
			// draw the body

			glPushMatrix();
			glScaled(1, .7, 1.2);
			glColor3d(.5, .5, .5);
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
			glTranslated(2.9, 0, 0);
			gluSphere(q, 1, 100, 100);
			glPopMatrix();

			glPushMatrix();
			glScaled(.3, .4, .75);
			glTranslated(-2.9, 0, 0);
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

			//pupils
			glPushMatrix();
			glScaled(.05, .05, .05);
			glColor3d(0, 0, 1);
			glTranslated(4, 20, 24);
			gluSphere(q, 1, 100, 100);
			glPopMatrix();

			glPushMatrix();
			glScaled(.05, .05, .05);
			glColor3d(0, 0, 1);
			glTranslated(-4, 20, 24);
			gluSphere(q, 1, 100, 100);
			glPopMatrix();

			// draw the beak
			glPushMatrix();
			glScaled(.25, .1, .5);
			glColor3d(1, .75, 0);
			glTranslated(0, 7.5, 2.35);
			gluCylinder(q, 1, 0, 1, 100, 100);
			glPopMatrix();
		} //end if q
		
		else {
			fprintf(stderr, "Couldn't initialize quadric");
			exit(1);
		}
		
		glEndList();
	} // end if displayList == -1
	glCallList(this->displayListHandle);
}