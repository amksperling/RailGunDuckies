/* The DuckieDriver file is a testing file for the Duckie class
   and its functions. */ 

#include <GL/freeglut.h>
#include "Duckie.h"


const int init_width = 1280;
const int init_height = 720;

int window_width = init_width;
int window_height = init_height;

double aspect = 1;

bool isWireFrame = false;
bool paused = false;
bool isFullScreen = false;

double period = 1000/60;

double pScale = .01;

//void DrawDuckie() {
//GLUquadric *q = gluNewQuadric();
//	
//	
//	// draw the body
//	glPushMatrix();
//	glScaled(1, .7, 1.2);
//	glColor3d(1, 1, 0);
//	gluSphere(q,1,100,100);
//	glPopMatrix();
//
//	// draw the head
//	glPushMatrix();
//	glScaled(.4, .4, .4);
//	glTranslated(0, 1.8, 2.2);
//	gluSphere(q,1,100,100);
//	glPopMatrix();
//
//	// draw the wings
//	glPushMatrix();
//	glScaled(.3, .4, .75);
//	glColor3d(1, 0, 0);
//	glTranslated(3, 0, 0);
//	gluSphere(q, 1, 100, 100);
//	glPopMatrix();
//
//	glPushMatrix();
//	glScaled(.3, .4, .75);
//	glColor3d(1, 0, 0);
//	glTranslated(-3, 0, 0);
//	gluSphere(q, 1, 100, 100);
//	glPopMatrix();
//
//
//	// draw the eyes
//	glPushMatrix();
//	glScaled(.1, .1, .1);
//	glColor3d(1, 1, 1);
//	glTranslated(2, 10, 11.3);
//	gluSphere(q, 1, 100, 100);
//	glPopMatrix();
//
//	glPushMatrix();
//	glScaled(.1, .1, .1);
//	glColor3d(1, 1, 1);
//	glTranslated(-2, 10, 11.3);
//	gluSphere(q, 1, 100, 100);
//	glPopMatrix();
//
//
//	// draw the beak
//	glPushMatrix();
//	glScaled(.25, .1, .5);
//	glColor3d(1, .5, 0);
//	glTranslated(0, 7.5, 2.5);
//	gluCylinder(q, 1, 0, 1, 100, 100);
//
//	// draw lines separating beak
//	//glColor3d(0, 0, 0);
//	//glBegin(GL_LINE);
//	//glVertex3d(2, 7.5, .5);
//	//glVertex3d(3, 7.5, 1);
//	//glEnd();
//	//glPopMatrix();
//
//	gluDeleteQuadric(q);
//}
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
//	glOrtho(-3 * aspect, 3 * aspect, -3, 3, 1, 10);
	gluPerspective(60, aspect, 1, 10);
	glViewport(0, 0, window_width, window_height);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Duckie * d = new Duckie();
	Duckie * p = new Duckie();

	glPushMatrix();
	glTranslated(0, 0, -5);
	glTranslated(-3, 0, 0);
	glRotated(elapsed_time * 60, 0, 1, 0);

//	DrawDuckie();
	d->render();

	delete d; 
	glPopMatrix();

	

	glPushMatrix();
	glTranslated(0, 0, -5);
	glTranslated(3, 0, 0);
	glRotated(elapsed_time * 60, 1, 0, 0);

	if (pScale < 1) {
		glScaled(pScale, pScale, pScale);
	}
	p->render();

	pScale += .001;
	
	delete p;
	glPopMatrix();

	glutSwapBuffers();
	glutPostRedisplay();
}

void ReshapeFunc(int w, int h) {
	if (h <= 0) {
		return;
	}

	window_width = w;
	window_height = h;


	aspect = double(w) / double(h); // remember to guard against div/0
	glutPostRedisplay();

}

void KeyboardFunc(unsigned char c, int x, int y) {
	switch (c) {
	
	case 'f':
		if (!isFullScreen) {
			glutFullScreen();
			isFullScreen = true;
			break;
		}
		glutReshapeWindow(init_width, init_height);
		isFullScreen = false;
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
	glutInitWindowSize(init_width, init_height);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Duckie Driver");
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(DuckieDisplayFunc);
	glutReshapeFunc(ReshapeFunc); // what function called if resized window?
	glutKeyboardFunc(KeyboardFunc); // what function called if keypressed?
	glutTimerFunc(period, TimerFunc, 0);
	glutMainLoop();
	return 0;
}
