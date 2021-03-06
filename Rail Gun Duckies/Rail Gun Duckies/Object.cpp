#include "Object.h"

#include <stdio.h>  
#include <iostream>
#include <sstream> //Checka
#include <vector>
#include <assert.h> //Checkb
#include <ctime>
#include <iomanip>

using namespace std;

const float PI = 3.14159265f;
static const float gravity = -32.2f;

/* Object Class

   This class is a super class for all objects used
*/

/* Object Constructor

   Constructor for Object super class

*/
//GLuint Object::cubeDisplayListHandle = (GLuint) -1;

Object::Object() { }

Object::Object(bool isMoving, vec3 position, vec3 rotation, vec3 scale, vec3 velocity, vec4 color) {
	this->shouldBeRemoved = false;
	this->isMoving = isMoving;
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
	this->velocity = velocity;
	this->color = color;
	this->isBeautyModeModel = false;
	this->beautyModeRotationVector = vec3(0,1,0);
	this->beautyModeRotationSpeed = 30;
}

/* Object Deconstructor

   Deletes object.

*/
Object::~Object() {

}

void Object::drawRect(float w, float h, float d, float r, float g, float b){
	//draws a cube with the scale specified. Responsibility of caller to save in display list.
	//r,g,b unused
	glPushMatrix();
	glScalef(w, h, d);

    glBegin(GL_QUADS);		// Draw The Cube Using quads
	glNormal3f(0.0, 1.0f, 0.0f);
	glVertex3f(0.5f, 0.5f, -0.5f);	// Top Right Of The Quad (Top)
	glVertex3f(-0.5f, 0.5f, -0.5f);	// Top Left Of The Quad (Top)
	glVertex3f(-0.5f, 0.5f,0.5f);	// Bottom Left Of The Quad (Top)
	glVertex3f(0.5f, 0.5f,0.5f);	// Bottom Right Of The Quad (Top)

	glNormal3f(0.0, -1.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, -0.5f);	// Top Right Of The Quad (Bottom)
	glVertex3f(-0.5f, -0.5f, -0.5f);//Top Left Of The Quad (Bottom)
    glVertex3f(-0.5f, -0.5f,0.5f);	// Bottom Left Of The Quad (Bottom)
	glVertex3f(0.5f, -0.5f,0.5f);	// Bottom Right Of The Quad (Bottom)

	glNormal3f(0.0, 0.0f, 1.0f);
    glVertex3f(0.5f, 0.5f, 0.5f);	// Top Right Of The Quad (Front)
    glVertex3f(-0.5f, 0.5f, 0.5f);	// Top Left Of The Quad (Front)
	glVertex3f(-0.5f, -0.5f, 0.5f);	// Bottom Left Of The Quad (Front)
	glVertex3f(0.5f, -0.5f, 0.5f);	// Bottom Right Of The Quad (Front)

	glNormal3f(0.0, 0.0f, -1.0f);
    glVertex3f(-0.5f, 0.5f, -0.5f);	// Top Right Of The Quad (Back)
	glVertex3f(0.5f, 0.5f, -0.5f);	// Top Left Of The Quad (Back)
	glVertex3f(0.5f, -0.5f, -0.5f); // Bottom Left Of The Quad (Back)
	glVertex3f(-0.5f, -0.5f, -0.5f);// Bottom Right Of The Quad (Back)


	glNormal3f(-1.0, 0.0f, 0.0f);
    glVertex3f(-0.5f, 0.5f, 0.5f);	// Top Right Of The Quad (Left)
    glVertex3f(-0.5f, 0.5f, -0.5f);	// Top Left Of The Quad (Left)
	glVertex3f(-0.5f, -0.5f, -0.5f);// Bottom Left Of The Quad (Left)
    glVertex3f(-0.5f, -0.5f, 0.5f); // Bottom Right Of The Quad (Left)

	glNormal3f(1.0, 0.0f, 0.0f);
    glVertex3f(0.5f, 0.5f, -0.5f);	// Top Right Of The Quad (Right)
    glVertex3f(0.5f, 0.5f, 0.5f);	// Top Left Of The Quad (Right)
	glVertex3f(0.5f, -0.5f, 0.5f);	// Bottom Left Of The Quad (Right)
    glVertex3f(0.5f, -0.5f, -0.5f);	// Bottom Right Of The Quad (Right)
    glEnd();
	glPopMatrix();
}

void Object::drawVecArrayBox(float w, float h, float d, float r, float g, float b, Object &objectToModify){
	glPushMatrix();
	glScalef(w,h,d);

	glPushMatrix();
	glTranslated(0, 0, (d/2));
	drawVecArrayFace(w,h,r,g,b,objectToModify);
	glPopMatrix();


	glPushMatrix();
	glRotated(180, 0 , 1, 0);
	glTranslated(0, 0, (d/2));
	drawVecArrayFace(w,h,r,g,b,objectToModify);
	glPopMatrix();

	glPushMatrix();
	glRotated(90, 0, 1, 0);
	glTranslated(0, 0, (w/2));
	drawVecArrayFace(d,h,r,g,b,objectToModify);
	glPopMatrix();

	glPushMatrix();
	glRotated(270, 0, 1, 0);
	glTranslated(0, 0, (w/2));
	drawVecArrayFace(d,h,r,g,b,objectToModify);
	glPopMatrix();

	glPushMatrix();
	glRotated(90, 1, 0, 0);
	glTranslated(0, 0, (h/2));
	drawVecArrayFace(w,d,r,g,b,objectToModify);
	glPopMatrix();

	glPushMatrix();
	glRotated(270, 1, 0, 0);
	glTranslated(0, 0, (h/2));
	drawVecArrayFace(w,d,r,g,b,objectToModify);
	glPopMatrix();

	glPopMatrix();
}

void Object::drawVecArrayFace(float w, float h, float r, float g, float b, Object &objectToModify){
		/*
		int startIndex = objectToModify.va_vertices.size();

		objectToModify.va_vertices.push_back(glm::vec3(-0.5, 0, 0.5));
		this->va_colors.push_back(glm::vec4(r, g, b,1.0f));
		this->va_normals.push_back(glm::vec3(0,0,1));

		this->va_vertices.push_back(glm::vec3(0.5, 0, 0.5));
		this->va_colors.push_back(glm::vec4(r, g, b,1.0f));
		this->va_normals.push_back(glm::vec3(0,0,1));

		this->va_vertices.push_back(glm::vec3(-0.5, 0, -0.5));
		this->va_colors.push_back(glm::vec4(r, g, g,1.0f));
		this->va_normals.push_back(glm::vec3(0,0,1));

		this->va_vertices.push_back(glm::vec3(0.5, 0, -0.5));
		this->va_colors.push_back(glm::vec4(r, g, b, 1.0f));
		this->va_normals.push_back(glm::vec3(0,0,1));
		

		this->va_indices.push_back(glm::ivec3(startIndex,startIndex+1,startIndex+3));
		this->va_indices.push_back(glm::ivec3(startIndex,startIndex + 3,startIndex+2)); */
}

void Object::drawVecArrayCircle(int radialPoints, float radius, float r, float g, float b, Object &objectToModify){
		/*
	float angleIncrement = 360/(float)radialPoints;

	for(float angle = 0; angle < 360; angle+=angleIncrement) {
		this->va_normals.push_back(glm::normalize(glm::vec3(r*cos(angle *(PI/180)),0,r*sin(angle *(PI/180)))));
	}
	*/
	/*objectToModify.va_vertices.push_back(glm::vec3(-1, 0, 1));
		this->va_colors.push_back(glm::vec4(r, g, b,1.0f));
		this->va_normals.push_back(glm::vec3(0,1,0));

		this->va_vertices.push_back(glm::vec3(1, 0, 1));
		this->va_colors.push_back(glm::vec4(r, g, b,1.0f));
		this->va_normals.push_back(glm::vec3(0,1,0));

		this->va_vertices.push_back(glm::vec3(-1, 0, -1));
		this->va_colors.push_back(glm::vec4(r, g, g,1.0f));
		this->va_normals.push_back(glm::vec3(0,1,0));

		this->va_vertices.push_back(glm::vec3(1, 0, -1));
		this->va_colors.push_back(glm::vec4(r, g, b, 1.0f));
		this->va_normals.push_back(glm::vec3(0,1,0));
		
		int startIndex = (int)omegaPoints * (int)phiPoints;

		this->va_indices.push_back(glm::ivec3(startIndex,startIndex+1,startIndex+3));
		this->va_indices.push_back(glm::ivec3(startIndex,startIndex + 3,startIndex+2)); */
}


void Object::updateAndRender(float timeStep, bool shouldFall, bool shouldRender) {
	//updates position of object, rotates it, scales it, and renders it

	glPushMatrix();

	//if its a beauty mode object then move it to position and rotate according to beauty mode style
	if(this->isBeautyModeModel) {
		glTranslated(this->position.x, this->position.y, this->position.z);
		glRotated(timeStep * this->beautyModeRotationSpeed, this->beautyModeRotationVector.x, 
			this->beautyModeRotationVector.y, this->beautyModeRotationVector.z);
	}
	else {

	//x = x + vt
	position.x += velocity.x * timeStep;
	position.y += velocity.y * timeStep;
	position.z += velocity.z * timeStep;

	if(position.y >= 30){
		position.y = -5;
	}

	// add gravity to the y component of velocity
	// v = v + gt
	if(shouldFall && velocity.y != 0) velocity.y += gravity * timeStep;

	glTranslated(this->position.x, this->position.y, this->position.z);
	glRotated(this->rotation.z, 0, 0, 1);
	glRotated(this->rotation.y, 0, 1, 0);
	glRotated(this->rotation.x, 1, 0, 0);
	}
	glScalef(this->scale.x, this->scale.y, this->scale.z);
	if(shouldRender) this->render();
	glPopMatrix();
} 