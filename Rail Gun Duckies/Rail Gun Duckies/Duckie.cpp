
#include "Duckie.h"

//gravitational constant
const double g = -9.8;

static GLUquadric *q = gluNewQuadric();

//Default constructor
Duckie::Duckie() : Object() {
	this->displayListHandle = (GLuint(-1));
	this->position = glm::vec3(0, 1.5, -95);
	this->velocity = glm::vec3(0, 0, 0);
	this->acceleration = glm::vec3(0, 0, 0);
	this->color = glm::vec3(1, 1, 0);
}

//constructor to initialze color
Duckie::Duckie(vec3 color) : color(color)
{ }

Duckie::~Duckie() {

}

void Duckie::render() {
		
	//set up material parameters
	//numbers from http://devernay.free.fr/cours/opengl/materials.html
	//
	//yellow plastic
	GLfloat material_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat material_diffuse[] = { .5f, .5f, 0.0f, 1.0f };
    GLfloat material_specular[] = { .6f, .6f, .5f, 1.0f };
    GLfloat material_shininess[] = { .25f * 128.0f };

	//yellow rubber
	//GLfloat material_ambient[] = {.05, .05, 0, 1};
	//GLfloat material_diffuse[] = { .5, .5, .4, 1 };
	//GLfloat material_specular[] = { .7, .7, .04, 1 };
	//GLfloat material_shininess[] = { .078125 * 128 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);


	glColor3d(this->color.r, this->color.g, this->color.b);
	if (this->displayListHandle == GLuint(-1)) {
		this->displayListHandle = glGenLists(1);
		glNewList(this->displayListHandle, GL_COMPILE);

		glPushMatrix();
		if (q) {
			// draw the body

			glPushMatrix();
			glScaled(1, .7, 1.2);
			
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
			glColor3d(1, .5, 0);
			glTranslated(0, 7.5, 2.35);
			gluCylinder(q, 1, 0, 1, 100, 100);
			glPopMatrix();

			glPopMatrix();
		} //end if q
		
		else {
			fprintf(stderr, "Couldn't initialize quadric"); //impossible else
			exit(1);
		}
		
		glEndList();
	} // end if displayList == -1


	glCallList(this->displayListHandle);

}

//
//void Duckie::setColor(vec3 color) {
//	this->color.r = color.r;
//	this->color.g = color.g;
//	this->color.b = color.b;
//}

//update the current position of the duck
//based on its current velocity and acceleration
//void Duckie::updatePosition(vec3 currentPosition, float timeStep) {
//	this->position.z = this->velocity.x * timeStep + this->position.z;
//	this->position.y = .5 * g * timeStep * timeStep + this->velocity.y * timeStep + this->position.y;
//	if( this->position.y <= 0) {
//		this->position.y = 0; // don't go under the world!
//	}
//	if (this->position.z == -200)
//		this->position.z = -199;
//}

void Duckie::setInitVelocity(double velocity, double inclinationAngle) {
	this->velocity.x = velocity * cos(inclinationAngle);
	this->velocity.y = velocity * sin(inclinationAngle);
	this->launched = true;
}

void Duckie::updatePosition(double timeStep, double gravity) {

	
	position.x += velocity.x * timeStep;
	position.y += velocity.y * timeStep;
	position.z += velocity.z * timeStep;

	// add gravity to the y component of velocity
	// v = v + gt
	velocity.y += gravity * timeStep;


	if( this->position.y <= .5) {
		this->position.y = .5; // don't go under the world!
		//this->launched = false;
	}

	//dont leave the world
	if (this->position.x >= 100)
		this->position.x = 100;
	if (this->position.x <= -100)
		this->position.x = -100;
	
	if (this->position.z >= 100)
		this->position.z = 100;
	
}