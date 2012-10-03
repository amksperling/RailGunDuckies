#include <gl/freeglut.h>
#include "RailGun.h"
#include "Prism.h"

RailGun::RailGun() {
	this->railgun_display_list = (GLuint) -1;
}

RailGun::~RailGun() {

}

void RailGun::drawRailGun() {
	if (this->railgun_display_list == (GLuint) -1)
	{
		this->railgun_display_list = glGenLists(1);
		glNewList(this->railgun_display_list, GL_COMPILE);
	//reflective table
	GLfloat material_ambient[] = {.19225, .19225, 0.19225, 1};
	GLfloat material_diffuse[] = { .50754, .50754, 0.50754, 1 };
    GLfloat material_specular[] = { .502873, .502873, .508273, 1 };
    GLfloat material_shininess[] = { .4 * 128 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);

	Prism *endRailGun = new Prism(1.0f,1.0f,0.5f,0.511f,0.535f,0.586f);
	endRailGun->drawPrism();
	glTranslated(0, 0, -5.5); 
	endRailGun->drawPrism();
	Prism *connectorStrutRailGun = new Prism(0.25f,0.25f,5.0f,0.511f,0.535f,0.586f);
	glTranslated(-0.375f, 0.375f, 2.75f);
	connectorStrutRailGun->drawPrism();
	glTranslated(0.75f, 0.0f, 0.0f);
	connectorStrutRailGun->drawPrism();
	glTranslated(0.0f, -0.75f, 0.0f);
	connectorStrutRailGun->drawPrism();
	glTranslated(-0.75f, 0.0f, 0.0f);
	connectorStrutRailGun->drawPrism();
	delete endRailGun;
	delete connectorStrutRailGun;
	glEndList();
	}

	glCallList(this->railgun_display_list);
}

double RailGun::getRotationAngle() const {
	return this->rotationAngle;
}

double RailGun::getInclinationAngle() const {
	return this->inclinationAngle;
}