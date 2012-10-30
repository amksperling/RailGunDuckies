#pragma once
#include <stdio.h>
//#include <iostream>
//#include <sstream>
#include <vector>
//#include <assert.h>

#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include "Object.h"

using namespace std;
using namespace glm;

class Balloon : public Object {

public:
	Balloon(bool isMoving, vec3 position, vec4 color) : Object(isMoving, position, color) { };
	~Balloon();

	void render();
	//void drawDiamond();
	//void Triangle();

	inline void setPointValue(int value) { this->pointValue = value; }
	inline int getPointValue() { return this->pointValue; }
	
private:
	static vector<vec3> va_vertices;
	static vector<vec4> va_colors;
	static vector<ivec3> va_indices;
	static vector<vec3> va_normals;

	int pointValue;
};
