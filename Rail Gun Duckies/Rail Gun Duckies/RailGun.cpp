#include <gl/freeglut.h>
#include "RailGun.h"
#include "Prism.h"

RailGun::RailGun() {

}

RailGun::~RailGun() {

}

void RailGun::drawRailGun() {
	Prism *endRailGun = new Prism(1.0f,1.0f,0.5f,0.0f,0.0f,1.0f);
	endRailGun->drawPrism();
	glTranslated(0, 0, -5.5); 
	endRailGun->drawPrism();
	Prism *connectorStrutRailGun = new Prism(0.25f,0.25f,5.0f,0.0f,1.0f,0.0f);
	glTranslated(-0.375f, 0.375f, 2.75f);
	connectorStrutRailGun->drawPrism();
	glTranslated(0.75f, 0.0f, 0.0f);
	connectorStrutRailGun->drawPrism();
	glTranslated(0.0f, -0.75f, 0.0f);
	connectorStrutRailGun->drawPrism();
	glTranslated(-0.75f, 0.0f, 0.0f);
	connectorStrutRailGun->drawPrism();
	delete endRailGun;
	delete connectorStrutRailGun;;
}

double RailGun::getRotationAngle() const {
	return this->rotationAngle;
}

double RailGun::getInclinationAngle() const {
	return this->inclinationAngle;
}