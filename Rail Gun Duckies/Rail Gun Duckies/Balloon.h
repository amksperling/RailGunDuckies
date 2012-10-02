/* We've officially started on the balloon. */

#include <GL/freeglut.h>
#include <glm.hpp>

using namespace glm;

class Balloon {

public:

	Balloon();

	void render();
	
private:
	//vertex vector?
};

static void computeVertices(Balloon b);