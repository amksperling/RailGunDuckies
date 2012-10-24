#pragma once
#include <gl/freeglut.h>
#include "Object.h"

/*
The RailGun class represents one RailGun object used in the Rail Gun Duckies
game.
*/

class RailGun : public Object {

public:
	RailGun();
	~RailGun();
	
	void drawRailGun();

	double getRotationAngle() const;
	double getInclinationAngle() const;

	void setRotationAngle(double a);
	void setInclinationAngle(double a);

	GLuint railgun_display_list;

private:
	double rotationAngle;
	double inclinationAngle;
};