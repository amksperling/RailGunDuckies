#pragma once
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <cstdio>

/*
The Duckie class represents one Duckie object used in the Rail Gun Duckies
game. Each Duckie has its own intrinsic properties that will be used



*/

using namespace glm;

class Duckie {

public:

	Duckie();
	Duckie(vec3 color);
	~Duckie();
	


	void render();

	inline vec3 getPosition() const {return this->position; }
	inline double getMass() const { return this->mass; }
	inline vec2 getVelocity() const { return this->velocity; }
	inline vec2 getAcceleration() const { return this->acceleration; }

	inline void setPosition(vec3 position) { this->position = position; }
	inline void setVelocity(vec2 velocity) { this->velocity = velocity; }
	inline void setAcceleration(vec2 acceleration) { this->acceleration = acceleration; }
	
	//set initial velocity based on railgun angles
	void setInitVelocity(double velocity, double inclinationAngle);
	void updatePosition(vec3 currentPosition, float timeStep);

	inline bool isMoving() { return this->launched; }

	void setColor(vec3 color);

private:

	bool launched;

	double mass;

	vec2 velocity;
	vec2 acceleration;
	vec3 color;

	vec3 position;
	

	GLuint displayListHandle;
	
};

