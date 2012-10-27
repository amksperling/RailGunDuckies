#pragma once
#include <stdio.h>
#include <vector>
#include <assert.h>

//#include <gl/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;


class World {

public:

	World();

	void render();
	inline GLuint getDisplayListHandle() { return this->displayListHandle; }


private:
	void skySide();
	void ground();
	void skyBox();

	GLuint displayListHandle;
	void renderSky(); // for future use with a sky dome

	// Used with vertex arrays.
	vector<GLdouble> va_v;
	vector<GLdouble> va_c;
	vector<GLuint> va_i;
	vector<GLdouble> va_n;

	vector<vec3> va_vertices;
	vector<vec4> va_colors;
	vector<ivec3> va_indices;
	vector<vec3> va_normals;

};