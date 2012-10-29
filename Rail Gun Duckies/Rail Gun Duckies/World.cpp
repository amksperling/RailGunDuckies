#include "World.h"

World::World() : displayListHandle(-1) {}

const float PI = 3.14159265f;

void World::render() {
	if (this->displayListHandle == GLuint(-1)) {
		this->displayListHandle = glGenLists(1);
		glNewList(this->displayListHandle, GL_COMPILE);

		// draw the skybox
		skyBox();
		// draw the ground
		ground();
		glEndList();
	}
	glCallList(this->displayListHandle);

}


// draw one side of the sky box
void World::skySide() {
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glBegin(GL_QUADS);

	glNormal3f(0, 1, 0);
	glColor3ub(255, 255, 255);
	glVertex2d(-100, 100);
	glVertex2d(100, 100);
	glColor3ub(0, 0, 150);
	glVertex2d(100, 0);
	glVertex2d(-100, 0);
	
	glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

// draw the ground from -100 to 100
void World::ground() {
	glDisable(GL_LIGHTING);

	glPushMatrix();
	glTranslated(0, 0, -100);
	glRotated(90, 1, 0, 0);
	glBegin(GL_QUADS);
	

	glColor3ub(0, 100, 0);
	glNormal3f(0, 1, 0);
	glVertex2d(-100, 0);
	glColor3ub(0, 40, 0);
	glVertex2d(-100, 200);
	glVertex2d(100, 200);
	glColor3ub(0, 100, 0);
	glVertex2d(100, 0);
	
	glEnd();

	glPopMatrix();
	glEnable(GL_LIGHTING);

}

//draw a skybox from the sky sides
void World::skyBox() {
	glPushMatrix();

	glPushMatrix();
	glTranslated(0, 0, 100);
	skySide();
	glPopMatrix();
	glRotated(90, 0 , 1, 0);

	glPushMatrix();
	glTranslated(0, 0, 100);
	skySide();
	glPopMatrix();
	glRotated(90, 0 , 1, 0);

	glPushMatrix();
	glTranslated(0, 0, 100);
	skySide();
	glPopMatrix();
	glRotated(90, 0 , 1, 0);

	glPushMatrix();
	glTranslated(0, 0, 100);
	skySide();
	glPopMatrix();
	glRotated(90, 0 , 1, 0);


	// need something for the top
	glPushMatrix();
	glTranslated(0, 100, -100);
	glScaled(1, 1, 2);
	glRotated(-90, 1, 0, 0);
	glRotated(180, 0, 0, 1);
	skySide();
	glPopMatrix();

	glPopMatrix();

}

void World::renderSky() {
	glDisable(GL_CULL_FACE);

	//Not set to balloon material yet
	GLfloat material_ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat material_diffuse[] = { 0.5f, 0.5f, 0.0f, 1.0f};
    GLfloat material_specular[] = { 0.6f, 0.6f, 0.5f, 1.0f };
    GLfloat material_shininess[] = { .25f * 128.0f };

	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess); 

	if (this->va_vertices.size() == 0) {	

		GLfloat r;
		GLfloat o;
		GLfloat p;
		r = 1;

		GLfloat omegaPoints = 31.0f;
		GLfloat omegaIncrement = 90/(omegaPoints-1);

		GLfloat phiPoints = 10.0f;
		GLfloat phiIncrement = 360/phiPoints;

		for(o = (GLfloat)0; o <=(GLfloat)90; o +=omegaIncrement) {
			for(p = (GLfloat)0; p <(GLfloat) 360; p +=phiIncrement) {
			
				this->va_vertices.push_back(glm::vec3((r * sin(o*(PI/180))* cos(p*(PI/180))), 
					(r * cos(o*(PI/180))), (r * sin(o*(PI/180))* sin(p*(PI/180)))));
				this->va_colors.push_back(glm::vec4(0.0f,0.0f,1.0f,1.0f));
			}
		}
		/*
		GLfloat rPoints = 3.0f;
		GLfloat rIncrement = 1/(rPoints - 1);

		for(r = (GLfloat)1; 1 >=(GLfloat)0; r -= rIncrement) {
			for(p = (GLfloat)0; p <(GLfloat) 360; p +=phiIncrement) {
				this->va_vertices.push_back(glm::vec3((r * cos(o*(PI/180))), 
					0, (r * sin(o*(PI/180)))));
				this->va_colors.push_back(glm::vec4(0.0f,1.0f,0.0f,1.0f));
				this->va_normals.push_back(glm::vec3(0,1,0));
			}
		}*/

		for(int a = 0; a < (int)(omegaPoints * phiPoints); a++) {
		if(a < (omegaPoints - 1) * phiPoints) { //last row does not need to construct triangles as there is no row beneath it
			if(((int)a % (int)phiPoints) != ((int)phiPoints-1)) {
				this->va_indices.push_back(glm::ivec3(a,a+phiPoints+1,a+phiPoints));
				this->va_indices.push_back(glm::ivec3(a,a + 1,a+phiPoints+1));
			}
			else {
				this->va_indices.push_back(glm::ivec3(a,a+1,a+phiPoints));
				this->va_indices.push_back(glm::ivec3(a,a-phiPoints+1,a+1));
			}
		}
			if(a < phiPoints) {
				this->va_normals.push_back(glm::vec3(0,-1,0));
			}
			else {
				glm::vec3 one;
				glm::vec3 two;
				glm::vec3 three;
				glm::vec3 four;
				glm::vec3 five;
				glm::vec3 six;

				//get all points starting at point directly above and going clockwise
				one = va_vertices[GLuint(a - phiPoints)];
				if(((int)a % (int)phiPoints) != ((int)phiPoints-1)) {
					two = va_vertices[GLuint(a + 1)];
					if(a < (omegaPoints - 1) * phiPoints) three = va_vertices[GLuint(a + phiPoints + 1)];
				}
				else {
					two = va_vertices[GLuint(a - phiPoints + 1)];
					if(a < (omegaPoints - 1) * phiPoints) three = va_vertices[GLuint(a + 1)];
				}
				if(a < (omegaPoints - 1) * phiPoints) four = va_vertices[GLuint(a + phiPoints)];
				if(((int)a % (int)phiPoints) != 0) {
					five = va_vertices[GLuint(a - 1)];
					six = va_vertices[GLuint(a - phiPoints - 1)];
				}
				else {
					five = va_vertices[GLuint(a + phiPoints - 1)];
					six = va_vertices[GLuint(a - 1)];
				}
				
				vec3 sum = glm::cross(two - va_vertices[GLuint(a)], one - va_vertices[GLuint(a)]);
				if(a < (omegaPoints - 1) * phiPoints){
				sum += glm::cross(three - va_vertices[GLuint(a)], two - va_vertices[GLuint(a)]);
				sum += glm::cross(four - va_vertices[GLuint(a)], three - va_vertices[GLuint(a)]);
				sum += glm::cross(five - va_vertices[GLuint(a)], four - va_vertices[GLuint(a)]);
				}
				sum += glm::cross(six - va_vertices[GLuint(a)], five - va_vertices[GLuint(a)]);
				sum += glm::cross(one - va_vertices[GLuint(a)], six - va_vertices[GLuint(a)]);
				this->va_normals.push_back(glm::normalize(sum));
			}
		}
		/*
		for(int a = (omegaPoints * phiPoints); a < (int)((omegaPoints + rPoints -1) * phiPoints); ++a) {
			if(((int)a % (int)phiPoints) != ((int)phiPoints-1)) {
				this->va_indices.push_back(glm::ivec3(a,a+phiPoints+1,a+phiPoints));
				this->va_indices.push_back(glm::ivec3(a,a + 1,a+phiPoints+1));
			}
			else {
				this->va_indices.push_back(glm::ivec3(a,a+1,a+phiPoints));
				this->va_indices.push_back(glm::ivec3(a,a-phiPoints+1,a+1));
			}
		}
		*/
		
		this->va_vertices.push_back(glm::vec3(-1, 0, 1));
		this->va_colors.push_back(glm::vec4(0.0f,1.0f,0.0f,1.0f));
		this->va_normals.push_back(glm::vec3(0,1,0));

		this->va_vertices.push_back(glm::vec3(1, 0, 1));
		this->va_colors.push_back(glm::vec4(0.0f,1.0f,0.0f,1.0f));
		this->va_normals.push_back(glm::vec3(0,1,0));

		this->va_vertices.push_back(glm::vec3(-1, 0, -1));
		this->va_colors.push_back(glm::vec4(0.0f,1.0f,0.0f,1.0f));
		this->va_normals.push_back(glm::vec3(0,1,0));

		this->va_vertices.push_back(glm::vec3(1, 0, -1));
		this->va_colors.push_back(glm::vec4(0.0f,1.0f,0.0f,1.0f));
		this->va_normals.push_back(glm::vec3(0,1,0));
		
		int startIndex = (int)omegaPoints * (int)phiPoints;

		this->va_indices.push_back(glm::ivec3(startIndex,startIndex+1,startIndex+3));
		this->va_indices.push_back(glm::ivec3(startIndex,startIndex + 3,startIndex+2));
		
	}

	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glVertexPointer(3 , GL_FLOAT , 0 , &this->va_vertices[0]);
	glColorPointer(4, GL_FLOAT, 0, &this->va_colors[0]);
	glNormalPointer(GL_FLOAT, 0, &this->va_normals[0]);

	glDrawElements(GL_TRIANGLES, 3*this->va_indices.size(), GL_UNSIGNED_INT, &this->va_indices[0]);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
} 