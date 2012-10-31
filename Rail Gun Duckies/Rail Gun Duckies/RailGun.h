#pragma once
#include <gl/freeglut.h>
#include <stdio.h>
#include <vector>
#include <glm/glm.hpp>
#include "Object.h"

using namespace std;
using namespace glm;

/*
The RailGun class represents one RailGun object used in the Rail Gun Duckies
game.
*/

class RailGun : public Object {

public:
	RailGun();
	RailGun(bool isMoving, vec3 position, vec3 rotation, vec3 scale, vec3 velocity, vec4 color);
	~RailGun();
	
	void render();

	double getRotationAngle() const;
	double getInclinationAngle() const;
	inline double getGunPower() const { return this->gunPower; }

	void increaseGunPower(double higher) { this->gunPower += higher; }
	void decreaseGunPower(double lower) { this->gunPower -= lower; }

	void setRotationAngle(double a);
	void setInclinationAngle(double a);

	static GLuint railgun_display_list;

private:
	double rotationAngle;
	double inclinationAngle;
	double gunPower;
};
