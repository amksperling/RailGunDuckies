#pragma once
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <cstdio>
#include "Object.h"

/*
The Duckie class represents one Duckie object used in the Rail Gun Duckies
game. Each Duckie has its own intrinsic properties that will be used



*/

using namespace glm;

class Duckie : public Object {

public:

	Duckie();
	Duckie(vec3 color);
	~Duckie();
	


	void render();

	inline vec3 getPosition() const {return this->position; }
	inline vec3 getVelocity() const { return this->velocity; }
	inline vec3 getAcceleration() const { return this->acceleration; }

	inline double getLaunchRotation() const { return this->launchRotation; }
	inline double getLaunchInclination() const { return this->launchInclination; }

	inline void setPosition(vec3 position) { this->position = position; }
	inline void setVelocity(vec3 velocity) { this->velocity = velocity; }
	inline void setAcceleration(vec3 acceleration) { this->acceleration = acceleration; }
	inline void setLaunched(bool launched) { this->launched = launched; }
	inline void setLaunchRotation(double launchRotation) {  if(launched) return; this->launchRotation = launchRotation; }
	inline void setLaunchInclination(double launchInclination) { if(launched) return; this->launchInclination = launchInclination; }
	
	void updatePosition(double elapsed_time, double gravity);
	
	inline bool isMoving() { return this->launched; }
	inline bool hitABalloon() { return this->hitBalloon; }
	
	inline bool hitTheGround() { return this->getPosition().y == .5; }
	
	inline void setColor(vec3 color) { this->color = color; }
	inline void setHitBalloon(bool hitBalloon) { this->hitBalloon = hitBalloon; }

private:

	bool launched;
	bool hitBalloon;

	double launchRotation;
	double launchInclination;

	vec3 velocity;
	vec3 acceleration;
	vec3 color;

	vec3 position;
	

	GLuint displayListHandle;
	
};

