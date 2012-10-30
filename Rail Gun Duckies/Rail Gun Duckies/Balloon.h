#pragma once
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <assert.h>

//#include <gl/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include "Object.h"

using namespace std;
using namespace glm;

class Balloon : public Object {

public:
	Balloon();
	~Balloon();

	void render();
	void drawDiamond();
	void Triangle();

	inline void setPosition(vec3 position) { this->position = position; }
	inline vec3 getPosition() { return this->position; }
	inline bool isHit() { return this->hit; }

	inline void setPointValue(int value) { this->points = value; }
	inline void setHit(bool hit) { this->hit = hit; }
	inline int getPointValue() { return this->points; }
	
private:

	static vector<vec3> va_vertices;
	static vector<vec4> va_colors;
	static vector<ivec3> va_indices;
	static vector<vec3> va_normals;

	vec3 position;

	bool hit;
	int points;
};
