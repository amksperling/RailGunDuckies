/* We've officially started on the balloon. */
#pragma once
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <assert.h>

//#include <gl/glew.h>
#include <GL/freeglut.h>
#include <glm.hpp>

using namespace std;
using namespace glm;

class Balloon {

public:
	Balloon();
	~Balloon();

	void render();
	void drawBalloon();
	void drawDiamond();
	void Triangle();
	
private:
	// Used with vertex arrays.
	vector<GLdouble> va_v;
	vector<GLdouble> va_c;
	vector<GLuint> va_i;

	vector<vec3> va_vertices;
	vector<vec4> va_colors;
	vector<ivec3> va_indices;
};

static void computeVertices(Balloon b);