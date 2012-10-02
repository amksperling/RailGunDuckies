#include "Window.h"


// Create a default window, the same as what we have now.
Window::Window() {
	glutInitWindowPosition(DEFAULT_POS_X, DEFAULT_POS_Y);
	glutInitWindowSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow(DEFAULT_TITLE);
	this->isFullScreen = false;
	this->w = DEFAULT_WIDTH;
	this->h = DEFAULT_HEIGHT;
}


// Create a fully custimzable window all in one constructor!
Window::Window(int w, int h, int posX, int posY, bool fullScreen, char * title) {
	glutInitWindowPosition(posX, posY);
	glutInitWindowSize(w, h);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow(title);
	if (fullScreen) {
		glutFullScreen();
		this->isFullScreen = true;
	}
	else
		this->isFullScreen = false;
	this->w = w;
	this->h = h;
}

//Toggles full screen mode.
void Window::toggleFullScreen() {
	if (!this->isFullScreen) {
		glutFullScreen();
		this->isFullScreen = true;
		return;
	}
	else {
		glutReshapeWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT);
		this->isFullScreen = false;
		return;
	}
}
