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

	//getters for critical values
	inline vec3 getPosition() const {return this->position; }
	inline vec3 getVelocity() const { return this->velocity; }
	//inline vec3 getAcceleration() const { return this->acceleration; }

	//launch angles are used to rotate the duck upon launch
	inline double getLaunchRotation() const { return this->launchRotation; }
	inline double getLaunchInclination() const { return this->launchInclination; }

	//we have the ability to set any value
	inline void setPosition(vec3 position) { this->position = position; }
	inline void setVelocity(vec3 velocity) { this->velocity = velocity; }
	//inline void setAcceleration(vec3 acceleration) { this->acceleration = acceleration; }
	inline void setLaunched(bool launched) { this->launched = launched; }
	inline void setHitBalloon(bool hitBalloon) { this->hitBalloon = hitBalloon; }

	//only set launch angles if the duck is not launched!
	inline void setLaunchRotation(double launchRotation) {  if(launched) return; this->launchRotation = launchRotation; }
	inline void setLaunchInclination(double launchInclination) { if(launched) return; this->launchInclination = launchInclination; }
	
	//uses ballistic motion to calculate a new position for the duck every frame
	void updatePosition(double elapsed_time, double gravity);
	
	inline bool isMoving() { return this->launched; }
	inline bool hitABalloon() { return this->hitBalloon; }
	
	inline bool hitTheGround() { return this->getPosition().y == .5; }
	
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

