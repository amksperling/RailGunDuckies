#pragma once
#include <GL/freeglut.h>



/*
The Duckie class represents one Duckie object used in the Rail Gun Duckies
game. Each Duckie has its own intrinsic properties that will be used



*/

struct Color {
	GLdouble red;
	GLdouble green;
	GLdouble blue;
};

class Duckie {

public:
	Duckie();
	Duckie(Color c);
	~Duckie();
	
//	void Initialize();
	void renderDL();
	void render();
	static void initialize();

	double getMass() const;
	double getVelocity() const;
	double getAcceleration() const;

private:
	double mass;
	double velocity;
	double acceleration;
	Color color;
	GLuint displayListHandle;
	// vector for position;
};

