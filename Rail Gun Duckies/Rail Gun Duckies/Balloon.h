#pragma once
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <assert.h>

//#include <gl/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

class Balloon {

public:
	Balloon();
	~Balloon();

	void render();
	void drawDiamond();
	void Triangle();

	inline void setPosition(vec3 position) { this->position = position; }
	inline vec3 getPosition() { return this->position; }
	
private:
	// Used with vertex arrays.
	vector<GLdouble> va_v;
	vector<GLdouble> va_c;
	vector<GLuint> va_i;
	vector<GLdouble> va_n;

	vector<vec3> va_vertices;
	vector<vec4> va_colors;
	vector<ivec3> va_indices;
	vector<vec3> va_normals;

	vec3 position;
};