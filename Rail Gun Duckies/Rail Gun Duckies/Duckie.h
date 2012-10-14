#pragma once
#include <GL/freeglut.h>
#include <glm/glm.hpp>


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
	
//	void Initialize();
	void renderDL();
	void render();
//	static void initialize();

	double getMass() const;
	double getVelocity() const;
	double getAcceleration() const;

private:
	double mass;
	double velocity;
	double acceleration;
	vec3 color;
	GLuint displayListHandle;
	// vector for position;
};

