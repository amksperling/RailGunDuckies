#include <gl/freeglut.h>
#include "Prism.h"

/* Prism Class

   This class is used to create a prism
*/

/* Prism Constructor

   Initializes a prism with the desired width (w), height (h), depth (d) and color (red, green, and blue specified by r, g, and b).

*/
Prism::Prism(float w, float h, float d, float r, float g, float b) {
	
	this->w = w;
	this->h = h;
	this->d = d;
	this->r = r;
	this->g = g;
	this->b = b;

}

/* Prism Deconstructor

   Deletes prism.

*/
Prism::~Prism() {

}

/* drawPrism

   Draws a prism with the desired width (w), height (h), depth (d) and color (red, green, and blue specified by r, g, and b).

*/
void Prism::drawPrism() {
	glPushMatrix();
	glScalef(this->w, this->h, this->d);
	glColor3f(this->r, this->g, this->b);
	glutSolidCube(1);
	glPopMatrix();
}