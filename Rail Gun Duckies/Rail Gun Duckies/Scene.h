/*
	The Scene class handles all aspects of the application.
	It uses every other object to draw the necessary scene and play the game.
	It also handles all game mechanics and automation.

*/

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

//Enum used for the 3 difficulty modes
//default is normal
enum DIFFICULTY {
	EASY,
	NORMAL,
	HARD
};

class Scene {

public:

	Scene();

	void setToBeautyMode(); //transition objects and positions to beauty mode
	void setToGameMode();   //transition objects and positions to game mode

	//use these functions to switch between app modes
	void runBeautyMode(int beautyMode);
	void runGameMode(bool runForever, float timeStep, Window & w);


	//fire the duck
	void fire();

	//reset the game
	void resetGame();

	//cycle through the 3 difficulties
	void cycleDifficulty();


	//move the rail gun based on mouse movement and position in the window
	//this function converts pixels to degrees
	void moveRailGun(int x, int y, const Window & w);

	//increase/decrease gun power (0-100)
	void increaseGunPower(double higher);
	void decreaseGunPower(double lower);

	//collision detection
	void checkForCollisions (Window & w); //(Object movingItem, Object otherObjects[], Window & w);

	//move hit balloon
	void moveHitBalloon(Balloon &b);

	//setup base of railgun
	void drawPedestal();

	//inline getters for all instance variables
	inline int getScore() const { return this->score; }
	inline int getDifficulty() const { return this->difficulty; }
	inline int getDucksRemaining() const { return this->ducksRemaining; }
	inline int getBalloonsRemaining() const{ return this->balloonsRemaining; }
	inline int getGunPower() const { return int(this->theGun.getGunPower()); }
	inline double getGunInclination() const { return this->theGun.getInclinationAngle(); }
	inline double getGunRotation() const { return this->theGun.getRotationAngle(); }
	inline string getDifficultyString() const { return this->difficulty_string; }
	inline vector<Balloon> & getBalloons() { return this->balloons; }
	
	
private:

	vector<Balloon> balloons; // list of all balloons
	Balloon aBalloon; //used for beauty mode

	//we only use one gun and one duck the whole time!
	//save memory!
	RailGun theGun; 
	Duckie theDuck;

	Duckie lifeIndicatingDuck1;
	Duckie lifeIndicatingDuck2;
	Duckie lifeIndicatingDuck3;

	//World is used for beauty modes, skybox is for the game
	World theWorld;
	SkyBox skyBox;

	static bool gameWon;
	static bool gameOver;
	static bool balloonHit;
	static bool transitionedFromGameMode;
	static bool transitionedFromBeautyMode;

	//used to draw the world in which our objects are placed
	void renderWorld();

	//displays point text above balloons
	void displayBalloonPointValue(Balloon & b);

	//generate random positions for balloons and place them in the world
	void placeBalloons();

	//put the duck back on the gun
	void resetDuck();

	//automates gun movement
	// see function for implemnetation details
	void automateGun();

	static int score;
	static int ducksRemaining;
	static int balloonsRemaining;
	static bool balloonsPlaced;
	int difficulty;
	string difficulty_string;

	GLuint displayListHandle;
	
};

//non class functions to generate random ints and doubles
//uses C++11 random engines and distributions
double genRandomDouble(double low, double high);
int genRandomInt(int low, int high);
