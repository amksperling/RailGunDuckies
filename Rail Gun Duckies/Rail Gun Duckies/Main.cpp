/* The main file  for Rail Gun Duckies:
	It uses a Window and Scene object to handle
	all freeglut callbacks and run the program properly.

*/ 
#include <GL/freeglut.h>
#include "Window.h"
#include "Scene.h"
#include <stdio.h>  
#include <iostream>
#include <sstream> //Checka
#include <vector>
#include <assert.h> //Checkb
#include <ctime>
#include <iomanip>

using namespace std;

//the period determines the ideal fps for the application:
//in this case, its 60.
const double period = 1000/60;

//the time variables are used to determine the timesteps
//required for drawing the duck in flight
static double timeSinceStart = 0.0;
static double timeStep = 0.0;
static double oldTimeSinceStart = 0.0;

//the test subjets:
Window * w;
Scene s;


//angle of rotation for camera
static float xpos = 0, ypos = 0, zpos = 0, xrot = 0, yrot = 0, zrot = 0.0, angle=0.0;

//camera function for controlling a global camera:
// controlled with the arrow keys
void camera (void) {
    glRotatef(xrot,1.0,0.0,0.0);  //rotate our camera on teh 
									//x-axis (left and right)
    glRotatef(yrot,0.0,1.0,0.0);  //rotate our camera on the 
									//	y-axis (up and down)
	glRotatef(zrot, 0, 0, 1);
    glTranslated(-xpos,-ypos,-zpos); //translate the screen
									// to the position of our camera
}


//function for displaying beauty mode text in an
// orthographic projection. 
void displayBeautyText(string text) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w->getWidth(), 0, w->getHeight(), 1, 10); // set ortho projection based on window size
	glViewport(0, 0, w->getWidth(),  w->getHeight());
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//starting from the bottom left corner, translate text 10 units
	// up and step back to see it. Scale to desired size
	glPushMatrix();
	glTranslated(0, 10, -1);
	glScaled(0.25, 0.25, 1);
	glDisable(GL_LIGHTING); //make sure to disable lighting!
	glColor3d(1, 1, 1);

	//freeglut uses c style strings, so we need to get that.
	//and actually print the string:
	glutStrokeString(GLUT_STROKE_MONO_ROMAN, (unsigned char *)text.c_str());

	glEnable(GL_LIGHTING); //enable lighting since we're done
	glPopMatrix();
}



//function for displaying all informational text in game mode in an ortho projection
void displayGameText() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w->getWidth(), 0, w->getHeight(), 1, 10);
	glViewport(0, 0, w->getWidth(), w->getHeight());
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	//int/double to string conversion from http://www.cplusplus.com/articles/D9j2Nwbp/
	//game status text
	string score = "Score: " + static_cast<ostringstream*>( &(ostringstream() << s.getScore()) )->str();
	string ducksRemaining = "Ducks Left: " + static_cast<ostringstream*>( &(ostringstream() << s.getDucksRemaining()) )->str();
	string balloonsRemaining = "Balloons Left: " + static_cast<ostringstream*>( &(ostringstream() << s.getBalloonsRemaining()) )->str();

	string gunPower = "Gun Power: " + static_cast<ostringstream*>( &(ostringstream() << s.getGunPower()) )->str();

	//notice use of setprecision() to limit decimal values
	string gunRotation = "Gun Rotation: " + static_cast<ostringstream*>( &(ostringstream() << setprecision(3) << s.getGunRotation()) )->str();
	string gunInclination = "Gun Inclination: " + static_cast<ostringstream*>( &(ostringstream() << setprecision(2) << s.getGunInclination()) )->str();
	
	//more info text
	string difficulty = "Difficulty: " + s.getDifficultyString();
	string automated = "AUTOMATED";
	string paused = "PAUSED";


	glPushMatrix();
	glTranslated(0, 5, -1);
	glScaled(.1, .1, 1);
	glDisable(GL_LIGHTING); //text doesn't need lighting!
	glColor3d(1, 1, 1);     //make it white

	//left side
	//display score
	glPushMatrix();
	glutStrokeString(GLUT_STROKE_MONO_ROMAN,(unsigned char *)score.c_str());
	glPopMatrix();

	glTranslated(0, 120, 0);

	//display ducks remaining
	glPushMatrix();
	glutStrokeString(GLUT_STROKE_MONO_ROMAN,(unsigned char *)ducksRemaining.c_str());
	glPopMatrix();

	glTranslated(0, 120, 0);

	//display balloons remaining
	glPushMatrix();
	glutStrokeString(GLUT_STROKE_MONO_ROMAN,(unsigned char *)balloonsRemaining.c_str());
	glPopMatrix();

	glTranslated(0, 120, 0);

	//display difficulty level
	glPushMatrix();
	glutStrokeString(GLUT_STROKE_MONO_ROMAN,(unsigned char *)difficulty.c_str());
	glPopMatrix();

	glTranslated(0, 120, 0);

	//display "automated" if game is automated
	if (w->getSceneMode() == GAME_FOREVER) {
		glPushMatrix();
		glutStrokeString(GLUT_STROKE_MONO_ROMAN,(unsigned char *)automated.c_str());
		glPopMatrix();
	}

	glTranslated(0, 120, 0);

	//display "paused" if game is paused
	if (w->getPaused()) {
		glPushMatrix();
		glutStrokeString(GLUT_STROKE_MONO_ROMAN,(unsigned char *)paused.c_str());
		glPopMatrix();
	}

	//move over to the right side
	glScaled(10, 10, 1);
	glTranslated(w->getWidth() - 140, -60, 0);
	glScaled(.1, .1, 1);


	//display gun power
	glPushMatrix();
	glutStrokeString(GLUT_STROKE_MONO_ROMAN,(unsigned char *)gunPower.c_str());
	glPopMatrix();

	glTranslated(-600, 120, 0);

	//display gun rotation
	glPushMatrix();
	glutStrokeString(GLUT_STROKE_MONO_ROMAN,(unsigned char *)gunRotation.c_str());
	glPopMatrix();

	glTranslated(0, 120, 0);

	//display gun inclination
	glPushMatrix();
	glutStrokeString(GLUT_STROKE_MONO_ROMAN,(unsigned char *)gunInclination.c_str());
	glPopMatrix();


	glEnable(GL_LIGHTING); //enable lighting since we're done
	glPopMatrix();

}


//fnuction used in debugging to check for GL errors
// prints any error to the console if one is found
bool CheckGLErrors(string location) {
	bool error_found = false;
	GLenum  error;
	const GLubyte *errorString;
	while ((error = glGetError()) != GL_NO_ERROR) {
		cout <<"\n";
		cout <<location; 
		error_found = true;
		errorString = gluErrorString(error);
		cout << errorString;
	}

	return error_found;
}

//InitGL function to handle all GL initializations
// for the main function. Handles lighting, depth, and face culling
void initGL() {

	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_SMOOTH);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_FRONT_AND_BACK);
	//glEnable(GL_LIGHT1);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE , 1.0);
	//glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER , 1.0);

	//////set up light position
	GLfloat light_position[] = { 2 , 2, 1, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	//GLfloat global_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	//glLightfv(GL_LIGHT0, GL_AMBIENT, global_ambient);

}

/*
The switching display function is the meat of the entire application.
It determines which application mode to run and what to display on the screen.

*/
void SwitchingDisplayFunc() {
	CheckGLErrors("Beginning of Display Function:");

	timeSinceStart = double(glutGet(GLUT_ELAPSED_TIME)) / 1000.0;
	
	timeStep = timeSinceStart - oldTimeSinceStart;
	if(w->getPaused()) timeStep = 0;
	oldTimeSinceStart = timeSinceStart;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(1, 0, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	//set up the world so we can see stuff!
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75, w->getAspect(), 1, 250);
	glViewport(0, 0, w->getWidth(), w->getHeight());
	camera();

	CheckGLErrors("push projection ");

	//swtich application modes
	// for each mode, the 3d scene is drawn, and then the 2d text is displayed over it
	switch (w->getSceneMode()) {

	case DUCK_BEAUTY:
		CheckGLErrors("begin duck beauty:");
		s.runBeautyMode(DUCK_BEAUTY);
		displayBeautyText("Duck Beauty Mode");
		CheckGLErrors("end duck beauty: ");
		break;

	case RAILGUN_BEAUTY:
		CheckGLErrors("begin railgun beauty:");
		s.runBeautyMode(RAILGUN_BEAUTY);
		displayBeautyText("RailGun Beauty Mode");

		CheckGLErrors("end gun beauty:");
		break;

	case BALLOON_BEAUTY:
		CheckGLErrors("begin balloon beauty:");
		s.runBeautyMode(BALLOON_BEAUTY);
		displayBeautyText("Balloon Beauty Mode");
		CheckGLErrors("end balloon beauty:");
		break;

	//the game modes require 3 paramaters:
	// runForever, timeStep, and a window.
	// the timestep was just calculated above and used here
	case GAME:
		CheckGLErrors("begin game:");
		s.runGameMode(false, timeStep, *w);
		displayGameText();
		CheckGLErrors("end game:");
		break;

	case GAME_FOREVER:
		s.runGameMode(true, timeStep, *w);
		displayGameText();
		break;

	default: break;

	}

	glutSwapBuffers();
	glutPostRedisplay();

	CheckGLErrors("End of Display Function:");
}

//Called when the window is resized in the OS
void ReshapeFunc(int width, int height) {
	//our window manager class handles this
	w->reshape(width, height);
	
}


//The KeyboardFunc handles all standard keyboard controls
//our window and scene classes handle all functions themselves,
// so this function becomes really simple
//see the README for information on implemented functions
void KeyboardFunc(unsigned char key, int x, int y) {
	switch (key) {
	
	case 'f':
		w->toggleFullScreen();
		break;
		
	case 'w':
		w->toggleWireFrame();
		break;

	case 'l':
		w->toggleLights();
		break;

	case 'c':
		w->cycleCameraMode();
		break;

	case 'p': 
		//paused = !paused;
		if (w->getPaused())
			w->setPause(false);
		else
			w->setPause(true);
		break;

	case 'r':
		s.resetGame();
		break;

	case 'g':
		w->toggleGhostMode();
		break;

	case 'd':
		s.cycleDifficulty();
		break;

	case 32: //spacebar
		if (w->getSceneMode() == GAME || w->getSceneMode() == GAME_FOREVER)
			s.fire();
	break;

	case ']':
		s.increaseGunPower(1);
		break;
	case '[':
		s.decreaseGunPower(1);
		break;

	case 'x':
	case 27:  //both x and Esc exit the program
		glutLeaveMainLoop();
		delete w;
		return;
	}
}

// The specialFunc handles special keys,
// in this case, only F1 and the arrow keys
void SpecialFunc(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_F1:
		w->cycleSceneMode();
		break;

	// planed feature for multiple lighting modes
	// not used now
	//case GLUT_KEY_F2:
	//	w->cycleLightingMode();
	//	break;

	//useing arrow keys to control global camera 
	case GLUT_KEY_LEFT:
		if (yrot > -35)
			yrot -= 1;
		break;

	case GLUT_KEY_RIGHT: 
		if (yrot < 35)
			yrot += 1;
		break;

	case GLUT_KEY_UP:
		if (xrot < 35)
			xrot += 1;
		break;

	case GLUT_KEY_DOWN:
		if (xrot > -35)
			xrot -= 1;
		break;
	
	default: break;
	}
}

//we dont even use the timer function,
// because we call glutPostRedisplay() at the end of 
// our display function
void TimerFunc(int value) {
	glutTimerFunc(GLuint(period), TimerFunc, value);
	glutPostRedisplay();
}


void MouseMovement(int x, int y) {

	// pass in the reference to the window in order to access current
	// height and width
	if (w && !w->getPaused()) // only move if not paused
		s.moveRailGun(x, y, *w);
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);

	//create a new default window to handle all glut calls
	w = new Window();

	//enable initial GL paramaters
	initGL();

	//list our callbacks
	glutDisplayFunc(SwitchingDisplayFunc);
	glutReshapeFunc(ReshapeFunc); // what function called if resized window?
	glutKeyboardFunc(KeyboardFunc); // what function called if keypressed?
	//glutTimerFunc(GLuint(period), TimerFunc, 0);
	glutPassiveMotionFunc(MouseMovement);
	glutSpecialFunc(SpecialFunc);
	glutMainLoop();
	return 0;
}
