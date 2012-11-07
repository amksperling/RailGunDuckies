#pragma once
#include <stdio.h>
#include <vector>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include "Object.h"

using namespace std;
using namespace glm;

/*
   The Balloon class is a subclass of Object. It contains properties and methods unique to the balloon class 
   as well as the method to construct and render a balloon.
*/

class Balloon : public Object {

public:
	Balloon();

	//overloaded constructor used to instantiate object superclass
	Balloon(bool isMoving, vec3 position, vec3 rotation, vec3 scale, vec3 velocity, vec4 color);

	~Balloon();

	void render();  //display the balloon

	void setPointValue(int value) { this->pointValue = value; }
	int getPointValue() { return this->pointValue; }
	

private:
	static vector<vec3> va_vertices; //array used to hold the points in space used to define the shape of a balloon
	static vector<ivec3> va_indices; //array used to hold groups of points that form a single triangular piece of the overall balloon
	static vector<vec3> va_normals;  //array used to hold the normal to each point in space, used for light and shadow calculations

	int pointValue;                  //value that will be added to the user's score if the balloon was successsfully hit
};
