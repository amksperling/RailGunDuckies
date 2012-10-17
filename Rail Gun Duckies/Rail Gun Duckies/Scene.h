#pragma once
#include "Duckie.h"
#include "RailGun.h"
#include "Balloon.h"
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <vector>

using namespace std;
using namespace glm;

class Scene {

public:

	Scene();

	void render(); // could be private as well if needed
	void playGame();
	void playGameForever();

	inline int getScore() { return this->score; }

private:

	vector<Balloon> balloons; // list of all balloons
	RailGun theGun;
	Duckie theDuck;


	bool gameWon;
	bool gameOver;
	bool balloonHit;

	void placeBalloons();
	void background();
	void ground();
	void skyBox();
	void placeGun();
	void placeDuck();

	int score;
	int ducksRemaining;
	GLuint displayListHandle;
	
};


