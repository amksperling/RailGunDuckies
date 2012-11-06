#pragma once
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <cstdio>
#include "Object.h"

/*
The Duckie class represents one Duckie object used in the Rail Gun Duckies
game. The duck keeps track of its position, velocity, color, and other 
attributes needed for the game to work.
*/

using namespace glm;

class Duckie : public Object {

public:

	Duckie();
	Duckie(bool isMoving, vec3 position, vec3 rotation, vec3 scale, vec3 velocity, vec4 color);
	~Duckie();
	


	void render();

	//launch angles are used to rotate the duck upon launch
	inline double getLaunchRotation() const { return this->launchRotation; }
	inline double getLaunchInclination() const { return this->launchInclination; }

	//inline void setAcceleration(vec3 acceleration) { this->acceleration = acceleration; }
	inline void setLaunched(bool launched) { this->launched = launched; }
	inline void setHitBalloon(bool hitBalloon) { this->hitBalloon = hitBalloon; }

	//only set launch angles if the duck is not launched!
	inline void setLaunchRotation(double launchRotation) {  if(launched) return; this->launchRotation = launchRotation; }
	inline void setLaunchInclination(double launchInclination) { if(launched) return; this->launchInclination = launchInclination; }
	
	
	inline bool isMoving() { return this->launched; }
	inline bool hitABalloon() { return this->hitBalloon; }
	
	inline bool hitTheGround() { return this->getPosition().y <= .7; }
	
	//we have the ability to change the color of the duck
	inline void setColor(vec3 color) { this->color = color; }
	

private:

	bool launched;
	bool hitBalloon;

	double launchRotation;
	double launchInclination;

	vec3 velocity;
	//vec3 acceleration;
	vec3 color;

	vec3 position;
	

	GLuint displayListHandle;
	
};

