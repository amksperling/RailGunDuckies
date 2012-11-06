#pragma once
#include <stdio.h>
#include <vector>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include "Object.h"

using namespace std;
using namespace glm;

/*
   The Diamond class is a subclass of Object. It contains properties and methods unique to the diamond class 
   as well as the method to construct and render a diamond.
*/

class Diamond : public Object {

public:
	Diamond();

	Diamond(bool isMoving, vec3 position, vec3 rotation, vec3 scale, vec3 velocity, vec4 color, int pointValue, int lifetime);// : Object(isMoving, position, rotation, scale, velocity, color) {};
	//overloaded constructor used to instantiate object superclass

	~Diamond();

	void render();  //display the diamond
	
	inline void setLifetime(int lifetime) { this->lifetime = lifetime; }
	inline int getLifetime() { return this->lifetime; }

	inline void setPointValue(int value) { this->pointValue = value; }
	inline int getPointValue() { return this->pointValue; }

private:
	int lifetime;  //how long the diamonds will last before they are removed from the screen
	int pointValue; //the point value of the balloon destroyed to create these diamonds. Used to determine color

	static vector<vec3> va_vertices; //array used to hold the points in space used to define the shape of a diamond
	static vector<ivec3> va_indices; //array used to hold groups of points that form a single triangular piece of the overall diamond
	static vector<vec3> va_normals;  //array used to hold the normal to each point in space, used for light and shadow calculations

};
