#pragma once
#include "Duckie.h"
#include "RailGun.h"
#include "Balloon.h"
#include "World.h"
#include "Window.h"
#include "Object.h"
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>

using namespace std;
using namespace glm;

class Scene {

public:

	Scene();



	//use these functions to switch between app modes
	void runBeautyMode(int beautyMode);
	void runGameMode(bool runForever, double timeStep, Window & w);

	void fire();
	void moveRailGun(int x, int y, const Window & w);
	void increaseGunPower(double higher);
	void decreaseGunPower(double lower);
	void checkForCollisions (Window & w); //(Object movingItem, Object otherObjects[], Window & w);

//	void duckBeauty();
//	void railGunBeauty();
//	void balloonBeauty();
//	void playGame();
//	void playGameForever();


	inline int getScore() { return this->score; }
	inline int getDucksRemaining() { return this->ducksRemaining; }
	inline int getBalloonsRemaining() { return this->balloonsRemaining; }
	inline int getGunPower() { return int(this->theGun.getGunPower()); }
	inline double getGunInclination() { return this->theGun.getInclinationAngle(); }
	inline double getGunRotation() { return this->theGun.getRotationAngle(); }


	void placeBalloons();
	//inline RailGun getGun() { return this->theGun; }

private:

	vector<Balloon> balloons; // list of all balloons
	Balloon aBalloon;
	RailGun theGun;
	Duckie theDuck;
	World theWorld;

	bool gameWon;
	bool gameOver;
	bool balloonHit;

	//used to draw the world in which our objects are placed
	void renderWorld();

	void skySide();
	void ground();
	void skyBox();
//	void placeGun();
//	void placeDuck();
	
	void resetDuck();

	static int score;
	static int ducksRemaining;
	static int balloonsRemaining;
	static bool balloonsPlaced;

	GLuint displayListHandle;
	
};

double genRandomDouble(double low, double high);
int genRandomInt(int low, int high);
