#pragma once
#include <gl/freeglut.h>



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
	
	void Initialize();
	void render();

	double getMass() const;
	double getVelocity() const;
	double getAcceleration() const;

private:
	double mass;
	double velocity;
	double acceleration;
	static bool isInitialized;
	Color color;
	// vector for position;
};

