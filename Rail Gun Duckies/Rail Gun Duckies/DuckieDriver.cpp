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
bool duckFullSize = false;

double period = 1000/60;

double pScale = .01;



//InitGL function to handle all GL initializations
// for the main function. Handles lighting and depth so far...
void initGL() {

	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_SMOOTH);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE , 0.0);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER , 1.0);

	//set up light position
	GLfloat light_position[] = { 2 , 2, 1, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);


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

	// grow the duck
	if (pScale <= 1) {
		glScaled(pScale, pScale, pScale);
		pScale += .001;
	}

	p->render();


	
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
	
	initGL();

	glutDisplayFunc(DuckieDisplayFunc);
	glutReshapeFunc(ReshapeFunc); // what function called if resized window?
	glutKeyboardFunc(KeyboardFunc); // what function called if keypressed?
	glutTimerFunc(period, TimerFunc, 0);
	glutMainLoop();
	return 0;
}
