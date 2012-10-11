/* Header file for a window manager class. 
   Kinda like a wrapper for glut for our own purposes.
   Not sure if it's totally necessary, but it can make
   our code look nicer in the end. */

#pragma once
#include <GL/freeglut.h>
#include <string>

const int DEFAULT_WIDTH = 1280;
const int DEFAULT_HEIGHT = 720;
const int DEFAULT_POS_X = 0;
const int DEFAULT_POS_Y = 0;
//const char * DEFAULT_TITLE = "Rail Gun Duckies";

const enum APP_MODES {
	DUCK_BEAUTY,
	RAILGUN_BEAUTY,
	BALLOON_BEAUTY,
	GAME,
	GAME_FOREVER
};

class Window {

public:

	Window();
	Window(int w, int h, int posX, int posY, bool fullScreen, char * title);


	/* These functions will toggle between the various modes
	   of the program. If we implement more than one lighting
	   mode, then it can be used in every mode depending on
	   the switch. */

	void cycleSceneMode(int defaultMode);

	void cycleLightingMode(int defaultLight);

	void cycleCameraMode(int defaultCamera);

	void toggleFullScreen();
	void toggleWireFrame();

private:

	/* pretty much every variable used by glut can go here.
	   We can use the glut functions to call our own window
	   functions with the correct paramaters. */

	int w;
	int h;
	bool isFullScreen;
	bool isWireFrame;
	double aspect;
};