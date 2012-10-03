#include "Window.h"

// Create a default window, the same as what we have now.
Window::Window() {
	glutInitWindowPosition(DEFAULT_POS_X, DEFAULT_POS_Y);
	glutInitWindowSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Rail Gun Duckies");
	this->isFullScreen = false;
	this->isWireFrame = false;
	this->w = DEFAULT_WIDTH;
	this->h = DEFAULT_HEIGHT;
}


// Create a fully custimzable window all in one constructor!
Window::Window(int w, int h, int posX, int posY, bool fullScreen, char * title) {
	glutInitWindowPosition(posX, posY);
	glutInitWindowSize(w, h);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow(title);
	if (fullScreen) glutFullScreen();
	this->isFullScreen = fullScreen;
	this->isWireFrame = false;
	this->w = w;
	this->h = h;
}

//Toggles full screen mode.
void Window::toggleFullScreen() {
	if (!this->isFullScreen) glutFullScreen();
	else glutReshapeWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT);
	this->isFullScreen = !this->isFullScreen;
}

// Toggle Wireframe mode
void Window::toggleWireFrame() {
	if (!this->isWireFrame) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	this->isWireFrame = !this->isWireFrame;
}