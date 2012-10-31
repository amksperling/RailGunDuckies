#pragma once
#include <stdio.h>
#include <vector>
#include <assert.h>
#include "Object.h"

//#include <gl/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;


class World : public Object {

public:

	World();
	World(bool isMoving, vec3 position, vec3 rotation, vec3 scale, vec3 velocity, vec4 color);

	void render();

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

};