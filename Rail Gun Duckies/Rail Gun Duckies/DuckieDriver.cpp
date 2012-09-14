/* The DuckieDriver file is a testing file for the Duckie class
   and its functions. */ 

#include <GL/freeglut.h>
#include "Duckie.h"

int window_width = 1280;
int window_height = 720;

double aspect = 1;
bool isWireFrame = false;
bool paused = false;

double period = 1000/60;


void DrawDuckie() {
	
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(0, 0, -5);
	GLUquadric *q = gluNewQuadric();
	
	
	// draw the body
	glPushMatrix();
	glScaled(1.3, .7, 1);
	
//	glRotated(theta, 0, 1, 0);
	glColor3d(1, 1, 0);
	gluSphere(q,1,100,100);
	glPopMatrix();

	// draw the head
	glPushMatrix();
	glScaled(.4, .4, .4);
//	glRotated(theta, 0, 1, 0);
	glTranslated(0, 1.8, 2.3);
	gluSphere(q,1,100,100);
	glPopMatrix();

	// draw the wings
	glPushMatrix();
	glScaled(.7, .3, .01);
//	glRotated(theta, 0, 1, 0);
	glColor3d(1, 0, 0);
	glTranslated(1.5, 0, 0);
	gluSphere(q, 1, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glScaled(.7, .3, .01);
//	glRotated(theta, 0, 1, 0);
	glColor3d(1, 0, 0);
	glTranslated(-1.5, 0, 0);
	gluSphere(q, 1, 100, 100);
	glPopMatrix();

	gluDeleteQuadric(q);
}
void Sphere() {
	
}

void DuckieDisplayFunc() {
	// use a switch to toggle between modes
	// each mode has a separate function

	double elapsed_time = double(glutGet(GLUT_ELAPSED_TIME)) / 1000.0;
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	//set up the world so we can see stuff!
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-3 * aspect, 3 * aspect, -3, 3, 1, 10);
//	gluPerspective(50, aspect, 1, 10);
	glViewport(0, 0, window_width, window_height);
	
	
	Duckie * d = new Duckie();
	Duckie * p = new Duckie();

	glPushMatrix();
	glTranslated(0, 0, -5);
	glTranslated(-3, 0, 0);
	glRotated(elapsed_time * 60, 0, 1, 0);

	d->render();
	delete d; 
	glPopMatrix();

	
glTranslated(0, 0, -5);
	glPushMatrix();
	
	glTranslated(3, 0, 0);
	glRotated(elapsed_time * 60, 0, 1, 0);

	p->render();
	delete p;
	glPopMatrix();

	glutSwapBuffers();
	glutPostRedisplay();
}

void ReshapeFunc(int w, int h) {
	window_width = w;
	window_height = h;
	if (h == 0) {
		return;
	}

	aspect = double(w) / double(h); // remember to guard against div/0
	glutPostRedisplay();

}

void KeyboardFunc(unsigned char c, int x, int y) {
	switch (c) {
	case 'n':
		glutCreateWindow("new window");
		break;
	case 'w':
		if (!isWireFrame) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			isWireFrame = true;
			break;
		}
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		isWireFrame = false;
		break;

	case 'p': 
		paused = !paused;
		break;
		// need to keep track of elapsed time while pasued and subtract from total time
	case 'x':
	case 27: glutLeaveMainLoop();
		return;
	}
	glutPostRedisplay();
}

void TimerFunc(int value) {
	glutTimerFunc(period, TimerFunc, value);
	glutPostRedisplay();
}
int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(window_width, window_height);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Duckie Driver");
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(DuckieDisplayFunc);
	glutReshapeFunc(ReshapeFunc); // what function called if resized window?
	glutKeyboardFunc(KeyboardFunc); // what function called if keypressed?
	glutTimerFunc(period, TimerFunc, 0);
	glutMainLoop();
	return 0;
}
