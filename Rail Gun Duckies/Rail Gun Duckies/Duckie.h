#include <gl/freeglut.h>



/*
The Duckie class represents one Duckie object used in the Rail Gun Duckies
game. Each Duckie has its own intrinsic properties that will be used



*/
class Duckie {

public:
	Duckie();

	~Duckie();
	
	void render();

	double getMass() const;
	double getVelocity() const;
	double getAcceleration() const;

private:
	double mass;
	double velocity;
	double acceleration;
	// vector for position;
};

static void Render();