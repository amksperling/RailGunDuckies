#include "RailGun.h"

GLuint RailGun::railgun_display_list;

RailGun::RailGun() : Object() {
	this->railgun_display_list = (GLuint) -1;
	this->gunPower = 50;
}

RailGun::RailGun(bool isMoving, vec3 position, vec3 rotation, vec3 scale, vec3 velocity, vec4 color) : Object(isMoving, position, rotation, scale, velocity, color) {
	this->railgun_display_list = (GLuint) -1;
	this->gunPower = 50;
} 

RailGun::~RailGun() {

}

void RailGun::render() {
	if (this->railgun_display_list == (GLuint) -1)
	{
		this->railgun_display_list = glGenLists(1);
		glNewList(this->railgun_display_list, GL_COMPILE);
	//reflective table
	GLfloat material_ambient[] = {(GLfloat).192, (GLfloat).192, (GLfloat)0.192, (GLfloat)1};
	GLfloat material_diffuse[] = { (GLfloat).508, (GLfloat).508, (GLfloat)0.508, (GLfloat)1 };
    GLfloat material_specular[] = { (GLfloat).503, (GLfloat).503, (GLfloat).503, (GLfloat)1 };
    GLfloat material_shininess[] = { (GLfloat).4 * (GLfloat)128 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);

	glTranslated(0, 0, 2.75);
	//Prism *endRailGun = new Prism(1.0f,1.0f,0.5f,0.511f,0.535f,0.586f);
	Object::drawRect(1.0f,1.0f,0.5f,0.511f,0.535f,0.586f);
	glTranslated(0, 0, -5.5); 
	Object::drawRect(1.0f,1.0f,0.5f,0.511f,0.535f,0.586f);
//	Prism *connectorStrutRailGun = new Prism(0.25f,0.25f,5.0f,0.511f,0.535f,0.586f);
	glTranslated(-0.375f, 0.375f, 2.75f);
	Object::drawRect(0.25f,0.25f,5.0f,0.511f,0.535f,0.586f);
	glTranslated(0.75f, 0.0f, 0.0f);
	Object::drawRect(0.25f,0.25f,5.0f,0.511f,0.535f,0.586f);
	glTranslated(0.0f, -0.75f, 0.0f);
	Object::drawRect(0.25f,0.25f,5.0f,0.511f,0.535f,0.586f);
	glTranslated(-0.75f, 0.0f, 0.0f);
	Object::drawRect(0.25f,0.25f,5.0f,0.511f,0.535f,0.586f);
	//delete endRailGun;
	//delete connectorStrutRailGun;
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

void RailGun::setRotationAngle(double a) {
	this->rotationAngle = a;
}

void RailGun::setInclinationAngle(double a) {
	this->inclinationAngle = a;
}