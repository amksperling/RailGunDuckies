#pragma once
//#include "Duckie.h"
//#include "RailGun.h"
//#include "Balloon.h"
//#include "Window.h"
//#include "GreyDuck.h"
//#include "Scene.h"

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <assert.h>

#include <GL/freeglut.h>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

class Object {

public:
	Object();
	~Object();

//	virtual void render();
	void drawRect(float w, float h, float d, float r, float g, float b);

   // static GLuint cubeDisplayListHandle;

private:

};