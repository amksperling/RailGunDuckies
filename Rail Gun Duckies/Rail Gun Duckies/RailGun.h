#include <gl/freeglut.h>

/*
The RailGun class represents one RailGun object used in the Rail Gun Duckies
game.
*/

class RailGun {

public:
	RailGun();
	~RailGun();
	
	void drawRailGun();

	double getRotationAngle() const;
	double getInclinationAngle() const;

private:
	double rotationAngle;
	double inclinationAngle;
};