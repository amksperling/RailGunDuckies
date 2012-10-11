#pragma once
#include <gl/freeglut.h>

/*
The Prism class represents one Prism object used in the Rail Gun Duckies
game.
*/

class Prism {

public:
	Prism(float w, float h, float d, float r, float g, float b);
	~Prism();

	void drawPrism();

private:
	float w;
	float h;
	float d;
	float r;
	float g;
	float b;
};