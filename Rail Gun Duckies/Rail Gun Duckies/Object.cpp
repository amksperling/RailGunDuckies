#include "Object.h"

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
}

/* Object Deconstructor

   Deletes object.

*/
Object::~Object() {

}

void Object::drawRect(float w, float h, float d, float r, float g, float b){
	glPushMatrix();
	glScalef(w, h, d);
	glColor3f(r, g, b);
	//if (cubeDisplayListHandle == GLuint(-1)) {
	//cubeDisplayListHandle = glGenLists(1);

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
	//End of my rectangle making test
	//glEndList();
	//} // end if displayList == -1
	//glCallList(cubeDisplayListHandle);
	glPopMatrix();
}
/*
void Object::drawVecArrayFace(float w, float h, float r, float g, float b){
		this->va_vertices.push_back(glm::vec3(-1, 0, 1));
		this->va_colors.push_back(glm::vec4(0.004f,0.306f,0.0f,1.0f));
		this->va_normals.push_back(glm::vec3(0,1,0));

		this->va_vertices.push_back(glm::vec3(1, 0, 1));
		this->va_colors.push_back(glm::vec4(0.004f,0.306f,0.0f,1.0f));
		this->va_normals.push_back(glm::vec3(0,1,0));

		this->va_vertices.push_back(glm::vec3(-1, 0, -1));
		this->va_colors.push_back(glm::vec4(0.004f,0.306f,0.0f,1.0f));
		this->va_normals.push_back(glm::vec3(0,1,0));

		this->va_vertices.push_back(glm::vec3(1, 0, -1));
		this->va_colors.push_back(glm::vec4(0.004f,0.306f,0.0f,1.0f));
		this->va_normals.push_back(glm::vec3(0,1,0));
		
		int startIndex = (int)omegaPoints * (int)phiPoints;

		this->va_indices.push_back(glm::ivec3(startIndex,startIndex+1,startIndex+3));
		this->va_indices.push_back(glm::ivec3(startIndex,startIndex + 3,startIndex+2));
}

void Object::setUpForRender() {
	glTranslated(this->position.x, this->position.y, this->position.z);
	glRotated(this->rotation.x, 1, 0, 0);
	glRotated(this->rotation.y, 0, 1, 0);
	glRotated(this->rotation.z, 0, 0, 1);
	glScalef(this->scale.x, this->scale.y, this->scale.z);
} */