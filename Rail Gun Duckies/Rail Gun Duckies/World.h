#pragma once

#include <GL/freeglut.h>


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
	//void skyDome() // for future use with a sky dome

};