/* Header file for a window manager class. 
   Kinda like a wrapper for glut for our own purposes.
   Not sure if it's totally necessary, but it can make
   our code look nicer in the end. */

#pragma once
#include <GL/freeglut.h>
#include <string>

using namespace std;


const int DEFAULT_WIDTH = 1280;
const int DEFAULT_HEIGHT = 720;
const int DEFAULT_POS_X = 10;
const int DEFAULT_POS_Y = 10;
const string DEFAULT_TITLE = "Rail Gun Duckies";

//we store our modes in enums for easy access
//with minimal memory hassles

enum APP_MODES {
	DUCK_BEAUTY,
	RAILGUN_BEAUTY,
	BALLOON_BEAUTY,
	GAME,
	GAME_FOREVER
};

enum LIGHT_MODES {
	OFF,
	BASIC,
	SPOTLIGHT,
	DAY_NIGHT,
	OTHER
};

enum CAMERA_MODES {
	MAIN,
	FLIGHT_FOLLOWER,
	FIRST_PERSON,
	SPECTATE_LEFT,
	SPECTATE_RIGHT,
	SPECTATE_FRONT
};

class Window {

public:



	Window();
	Window(int w, int h, int posX, int posY, bool fullScreen, string title);


	/* These functions will toggle between the various modes
	   of the program. If we implement more than one lighting
	   mode, then it can be used in every mode depending on
	   the switch. */

	void cycleSceneMode();

	void cycleLightingMode();

	void cycleCameraMode();
	void cycleSpectatorMode();

	void toggleFullScreen();
	void toggleWireFrame();
	void toggleLights();
	void toggleGhostMode();

	
	inline void setPause(bool newPausedValue) { this->isPaused = newPausedValue; }
	inline bool getPaused() { return this->isPaused; }

	void reshape(int w, int h);

	inline int getSceneMode() const { return sceneMode; }
	inline int getCameraMode() const { return cameraMode; }
	inline int getLightMode() const { return lightMode; }

	inline double getAspect() const { return this->aspect; }
	inline int getWidth() const { return this->w; }
	inline int getHeight() const { return this->h; }

private:

	/* pretty much every variable used by glut can go here.
	   We can use the glut functions to call our own window
	   functions with the correct paramaters. */

	int w;
	int h;
	bool isFullScreen;
	bool isWireFrame;
	bool isPaused;
	bool ghostMode;

	double aspect;
	int sceneMode;
	int cameraMode;
	int lightMode;

	void setBasicLights();

	//these are for planned features and are not implemented
	void setSpotLights();
	void setDayNight();
	void setOtherLights();
};
