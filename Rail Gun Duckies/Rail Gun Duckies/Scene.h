#pragma once
#include "Duckie.h"
#include "RailGun.h"
#include "Balloon.h"
#include "Window.h"
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
	void runGameMode(bool runForever, double & elapsed_time);

	void fire();
	void moveRailGun(int x, int y);

//	void duckBeauty();
//	void railGunBeauty();
//	void balloonBeauty();
//	void playGame();
//	void playGameForever();


	inline int getScore() { return this->score; }
	inline int getDucksRemainging() { return this->ducksRemaining; }
	inline int getBalloonsRemaining() { return this->balloonsRemaining; }

private:

	vector<Balloon> balloons; // list of all balloons
	Balloon aBalloon;
	RailGun theGun;
	Duckie theDuck;


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
	void placeBalloons();

	int score;
	int ducksRemaining;
	int balloonsRemaining;

	GLuint displayListHandle;
	
};


