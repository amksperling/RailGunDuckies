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
	glBegin(GL_QUADS);
	glTranslated(0, 0, -100);
	glRotated(90, 1, 0, 0);
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
	glTranslated(0, 100, 0);
	glRotated(-90, 1, 0, 0);
	glRotated(180, 0, 0, 1);
	skySide();
	glPopMatrix();

	glPopMatrix();

}

void World::renderSky() {
	//Not set to sky material yet
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

		GLfloat omegaPoints = 91.0f;
		GLfloat omegaIncrement = 180/(omegaPoints-1);

		GLfloat phiPoints = 120.0f;
		GLfloat phiIncrement = 360/phiPoints;

		for(o = (GLfloat)0; o <=(GLfloat)180; o +=omegaIncrement) {
			for(p = (GLfloat)0; p <(GLfloat) 360; p +=phiIncrement) {
			
				if(o < .5 * 180) r = (GLfloat) 1;
				else r = (GLfloat) (1+ (1-cos((o-90)*(PI/180)))/2);
			
				this->va_vertices.push_back(glm::vec3((r * sin(o*(PI/180))* cos(p*(PI/180))), 
					(r * cos(o*(PI/180))), (r * sin(o*(PI/180))* sin(p*(PI/180)))));
				this->va_colors.push_back(glm::vec4(1.0f,0.0f,0.0f,1.0f));
			}
		}
	
		GLfloat height;
		GLfloat angle;
		r = 0;
		GLfloat heightPoints = 6;
		GLfloat heightIncrement  = 0.1f/(heightPoints-1);
		GLfloat anglePoints = 18;
		GLfloat angleIncrement = 360/anglePoints;

		for(height = (GLfloat)-1.45f; height >=(GLfloat)-1.55f; height -=heightIncrement) {
			for(angle = 0; angle < 360; angle+=angleIncrement){
				this->va_vertices.push_back(glm::vec3((r * cos(angle*(PI/180))), height, (r * sin(angle*(PI/180)))));
				this->va_colors.push_back(glm::vec4(1.0f,0.0f,0.0f,1.0f));
			}
			r+=(GLfloat)0.02;
		}
	
		r-=0.02f;

		GLfloat a;
		GLfloat aMax = (omegaPoints - 1) * phiPoints;
		for(a = 0; a < aMax; a++) {
			if(((int)a % (int)phiPoints) != ((int)phiPoints-1)) {
				this->va_indices.push_back(glm::ivec3(a,a+phiPoints+1,a+phiPoints));
				this->va_indices.push_back(glm::ivec3(a,a + 1,a+phiPoints+1));
			}
			else {
				this->va_indices.push_back(glm::ivec3(a,a+1,a+phiPoints));
				this->va_indices.push_back(glm::ivec3(a,a-phiPoints+1,a+1));
			}
			if(a < phiPoints) {
				this->va_normals.push_back(glm::vec3(0,1,0));
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
					three = va_vertices[GLuint(a + phiPoints + 1)];
				}
				else {
					two = va_vertices[GLuint(a - phiPoints + 1)];
					three = va_vertices[GLuint(a + 1)];
				}
				four = va_vertices[GLuint(a + phiPoints)];
				if(((int)a % (int)phiPoints) != 0) {
					five = va_vertices[GLuint(a - 1)];
					six = va_vertices[GLuint(a - phiPoints - 1)];
				}
				else {
					five = va_vertices[GLuint(a + phiPoints - 1)];
					six = va_vertices[GLuint(a - 1)];
				}
				
				vec3 sum = glm::cross(one - va_vertices[GLuint(a)], two - va_vertices[GLuint(a)]);
				sum += glm::cross(two - va_vertices[GLuint(a)], three - va_vertices[GLuint(a)]);
				sum += glm::cross(three - va_vertices[GLuint(a)], four - va_vertices[GLuint(a)]);
				sum += glm::cross(four - va_vertices[GLuint(a)], five - va_vertices[GLuint(a)]);
				sum += glm::cross(five - va_vertices[GLuint(a)], six - va_vertices[GLuint(a)]);
				sum += glm::cross(six - va_vertices[GLuint(a)], one - va_vertices[GLuint(a)]);
				this->va_normals.push_back(glm::normalize(sum));
			}
		} 

		for(a = 0; a < phiPoints; ++a) {
			this->va_normals.push_back(glm::vec3(0,-1,0));
		}

		for(a = 0; a < anglePoints; ++a) {
			this->va_normals.push_back(glm::vec3(0,1,0));
		}

		GLfloat initial = omegaPoints * phiPoints;
		GLfloat b = initial;
		GLfloat bMax = b + (heightPoints - 1) * anglePoints;

		for(b = omegaPoints * phiPoints; b < bMax; b++) {
			if(((int)(b-initial) % (int)anglePoints) != ((int)anglePoints-1)) {
				this->va_indices.push_back(glm::ivec3(b,b+anglePoints+1,b+anglePoints));
				this->va_indices.push_back(glm::ivec3(b,b + 1,b+anglePoints+1));
			}
			else {
				this->va_indices.push_back(glm::ivec3(b,b+1,b+anglePoints));
				this->va_indices.push_back(glm::ivec3(b,b-anglePoints+1,b+1));
			}

			if(b < initial + anglePoints) {
				this->va_normals.push_back(glm::vec3(0,1,0));
			}
			else {
				glm::vec3 one;
				glm::vec3 two;
				glm::vec3 three;
				glm::vec3 four;
				glm::vec3 five;
				glm::vec3 six;

				//get all points starting at point directly above and going clockwise
				one = va_vertices[GLuint(b - anglePoints)];
				if(((int)(b-initial) % (int)anglePoints) != ((int)anglePoints-1)) {
					two = va_vertices[GLuint(b + 1)];
					three = va_vertices[GLuint(b + anglePoints + 1)];
				}
				else {
					two = va_vertices[GLuint(b - anglePoints + 1)];
					three = va_vertices[GLuint(b + 1)];
				}
				four = va_vertices[GLuint(b + anglePoints)];
				if(((int)(b-initial) % (int)anglePoints) != 0) {
					five = va_vertices[GLuint(b - 1)];
					six = va_vertices[GLuint(b - anglePoints - 1)];
				}
				else {
					five = va_vertices[GLuint(b + anglePoints - 1)];
					six = va_vertices[GLuint(b - 1)];
				}

				glm::vec3 sum = glm::cross(one - va_vertices[GLuint(b)], two - va_vertices[GLuint(b)]);
				sum += glm::cross(two - va_vertices[GLuint(b)], three - va_vertices[GLuint(b)]);
				sum += glm::cross(three - va_vertices[GLuint(b)], four - va_vertices[GLuint(b)]);
				sum += glm::cross(four - va_vertices[GLuint(b)], five - va_vertices[GLuint(b)]);
				sum += glm::cross(five - va_vertices[GLuint(b)], six - va_vertices[GLuint(b)]);
				sum += glm::cross(six - va_vertices[GLuint(b)], one - va_vertices[GLuint(b)]);
				this->va_normals.push_back(glm::normalize(sum));
			}
		}

		for(a = 0; a < anglePoints; ++a) {
			for(angle = 0; angle < 360; angle+=angleIncrement) {
				this->va_normals.push_back(glm::normalize(glm::vec3(r*cos(angle *(PI/180)),0,r*sin(angle *(PI/180)))));
			}
		}

	}

	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glVertexPointer(3 , GL_FLOAT , 0 , &this->va_vertices[0]);
	glColorPointer(4, GL_FLOAT, 0, &this->va_colors[0]);
	glNormalPointer(GL_FLOAT, 0, &this->va_normals[0]);

	glDrawElements(GL_TRIANGLES, 3 * this->va_indices.size(), GL_UNSIGNED_INT, &this->va_indices[0]);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

	glPushMatrix();
	glTranslated(0, -1.55, 0);
	glRotated(90, 1, 0, 0);
	glColor3d(1, 0, 0);
	glutSolidTorus((GLdouble) 0.018, (GLdouble) 0.12, (GLint) 20, (GLint) 20);
	glPopMatrix();
}