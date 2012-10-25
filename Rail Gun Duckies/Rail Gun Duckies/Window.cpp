#include "Window.h"

// Create a default window, the same as what we have now.
Window::Window() {
	glutInitWindowPosition(DEFAULT_POS_X, DEFAULT_POS_Y);
	glutInitWindowSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow(&DEFAULT_TITLE[0]);
	this->isFullScreen = false;
	this->isWireFrame = false;
	this->w = DEFAULT_WIDTH;
	this->h = DEFAULT_HEIGHT;
	this->sceneMode = DUCK_BEAUTY;
	this->lightMode = BASIC;
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE , 0.0);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER , 1.0);
	setBasicLights();
}


// Create a fully custimzable window all in one constructor!
Window::Window(int w, int h, int posX, int posY, bool fullScreen, string title) {
	glutInitWindowPosition(posX, posY);
	glutInitWindowSize(w, h);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow(&title[0]);
	if (fullScreen) glutFullScreen();
	this->isFullScreen = fullScreen;
	this->isWireFrame = false;
	this->w = w;
	this->h = h;
	this->lightMode = BASIC;
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE , 0.0);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER , 1.0);
	setBasicLights();
}

//Toggles full screen mode.
void Window::toggleFullScreen() {
	if (!this->isFullScreen) 
		glutFullScreen();
	else 
		glutReshapeWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT);
	this->isFullScreen = !this->isFullScreen;
}

// Toggle Wireframe mode
void Window::toggleWireFrame() {
	if (!this->isWireFrame) 
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else 
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	this->isWireFrame = !this->isWireFrame;
}

void Window::cycleSceneMode() {
	switch (this->sceneMode) {
	case DUCK_BEAUTY:
		this->sceneMode = RAILGUN_BEAUTY;
		break;
	case RAILGUN_BEAUTY:
		this->sceneMode = BALLOON_BEAUTY;
		break;
	case BALLOON_BEAUTY:
		this->sceneMode = GAME;
		break;
	case GAME:
		this->sceneMode = GAME_FOREVER;
		break;
	case GAME_FOREVER:
		this->sceneMode = DUCK_BEAUTY;
		break;
	}
}

void Window::cycleLightingMode() {
	switch (this->lightMode) {
	case OFF:
		toggleLights();
		setBasicLights();
		this->lightMode = BASIC;
		break;

	case BASIC:
		this->lightMode = SPOTLIGHT;
		break;

	case SPOTLIGHT:
		this->lightMode = DAY_NIGHT;
		break;

	case DAY_NIGHT:
		this->lightMode = OTHER;
		break;

	case OTHER:
		toggleLights();
		this->lightMode = OFF;
	}
}

void Window::toggleLights() {
	if (this->lightMode == OFF) {
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		this->lightMode = BASIC;
	}
	else {
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		this->lightMode = OFF;
	}
}

void Window::setBasicLights() {
	////set up basic light position
	GLfloat light_position[] = { 2 , 2, 1, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

void Window::reshape(int w, int h) {
	if (h <= 0) {
		return;
	}

	this->w = w;
	this->h = h;


	this->aspect = double(w) / double(h); // remember to guard against div/0

}