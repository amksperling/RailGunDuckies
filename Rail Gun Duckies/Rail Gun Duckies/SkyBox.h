/*
	Skybox is used to draw the bounding skybox for the game.
	It's a 200x200 cube that uses gradient colors
	to simulate added depth.
*/

#pragma once
#include <stdio.h>
#include <vector>
#include <assert.h>
#include "Object.h"

#include <GL/freeglut.h>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;


class SkyBox : public Object {

public:
	SkyBox();
	SkyBox(bool isMoving, vec3 position, vec3 rotation, vec3 scale, vec3 velocity, vec4 color);

	void render();
	inline GLuint getDisplayListHandle() { return this->displayListHandle; }


private:
	//the box consists of 4 sky sides, the ground and the top
	// so we need functions for all of them
	void skySide();
	void ground();
	void skyBox();
	void skyTop();

	static GLuint displayListHandle;
};
