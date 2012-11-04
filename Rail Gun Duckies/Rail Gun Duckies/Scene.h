#pragma once
#include "Duckie.h"
#include "RailGun.h"
#include "Balloon.h"
#include "World.h"
#include "Window.h"
#include "SkyBox.h"
#include "Object.h"
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <sstream>
#include <random>
#include <ctime>


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


	inline int getScore() const { return this->score; }
	inline int getDucksRemaining() const { return this->ducksRemaining; }
	inline int getBalloonsRemaining() const{ return this->balloonsRemaining; }
	inline int getGunPower() const { return int(this->theGun.getGunPower()); }
	inline double getGunInclination() const { return this->theGun.getInclinationAngle(); }
	inline double getGunRotation() const { return this->theGun.getRotationAngle(); }

	inline vector<Balloon> & getBalloons() { return this->balloons; }
	
	void resetGame();

private:

	vector<Balloon> balloons; // list of all balloons
	Balloon aBalloon;
	RailGun theGun;
	Duckie theDuck;
	World theWorld;
	SkyBox skyBox;

	static bool gameWon;
	static bool gameOver;
	bool balloonHit;

	//used to draw the world in which our objects are placed
	void renderWorld();
	void displayBalloonPointValue(Balloon & b);
//	void placeGun();
//	void placeDuck();
	void placeBalloons();
	void resetDuck();
	void automate();

	static int score;
	static int ducksRemaining;
	static int balloonsRemaining;
	static bool balloonsPlaced;

	GLuint displayListHandle;
	
};

double genRandomDouble(double low, double high);
int genRandomInt(int low, int high);
