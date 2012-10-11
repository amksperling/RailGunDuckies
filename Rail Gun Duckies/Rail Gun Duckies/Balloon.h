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
	void drawDiamond();
	
private:
	// Used with vertex arrays.
	vector<glm::vec3> va_vertices;
	vector<glm::vec4> va_colors;
	vector<glm::vec3> va_indices;
};

static void computeVertices(Balloon b);