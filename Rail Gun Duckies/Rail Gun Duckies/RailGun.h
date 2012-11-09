#pragma once
#include <GL/freeglut.h>
#include <stdio.h>
#include <vector>
#include <glm/glm.hpp>
#include "Object.h"

using namespace std;
using namespace glm;

/*
   The RailGun class is a subclass of Object. It contains properties and methods unique to the railgun class
   as well as the method to construct and render a railgun.
*/

class RailGun : public Object {

public:
	RailGun();
	RailGun(bool isMoving, vec3 position, vec3 rotation, vec3 scale, vec3 velocity, vec4 color);
	~RailGun();

	void render();

	//rotation = yaw, x axis
	double getRotationAngle() const;

	//inclination = pitch, y axis
	double getInclinationAngle() const;

	double getGunPower() const { return this->gunPower; }

	//the power of the gun is variable from 0 to 100
	void increaseGunPower(double higher) { this->gunPower += higher; }
	void decreaseGunPower(double lower) { this->gunPower -= lower; }
	void setGunPower(double input) { this->gunPower = input; }

	void setRotationAngle(double a);
	void setInclinationAngle(double a);

	static GLuint railgun_display_list;

private:
	double rotationAngle;
	double inclinationAngle;
	double gunPower;
};
