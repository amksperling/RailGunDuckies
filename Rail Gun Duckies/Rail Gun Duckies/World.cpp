#include "World.h"

World::World() {}

World::World(bool isMoving, vec3 position, vec3 rotation, vec3 scale, vec3 velocity, vec4 color) : 
	Object(isMoving, position, rotation, scale, velocity, color)
{ } 

const float PI = 3.14159265f;

void World::render() {
	glDisable(GL_CULL_FACE);
	if (this->va_vertices.size() == 0) {	

		GLfloat r;
		GLfloat o;
		GLfloat p;
		r = 1;

		//The world is drawn by specifying individual vertexes. In this case, the top half of the
		//world is drawn by loops that draw verticle stacks of circles of non-linear radius which are connected to form
		//a hemisphere shape. In this case, the circles are made by taking polar coordinates and converting
		//them back into cartesian.

		GLfloat omegaPoints = 31.0f;
		GLfloat omegaIncrement = 90/(omegaPoints-1);

		//The value to increment between the points is determined by the desired space to fill over the number
		//of points. In this case, a 1 is subtracted from the points, because 0 is counted as the first point
		//and the loop runs until the value equals the desired size.

		GLfloat phiPoints = 20.0f;
		GLfloat phiIncrement = 360/phiPoints;

		for(o = (GLfloat)0; o <=(GLfloat)90; o +=omegaIncrement) {
			for(p = (GLfloat)0; p <(GLfloat) 360; p +=phiIncrement) {
			
				this->va_vertices.push_back(glm::vec3((r * sin(o*(PI/180))* cos(p*(PI/180))), 
					(r * cos(o*(PI/180))), (r * sin(o*(PI/180))* sin(p*(PI/180)))));
				this->va_colors.push_back(glm::vec4(0.0f,0.0f,1.0f,1.0f));
			}
		}

		//The vertices are then grouped into triangles and have their normals calculated by normalizing 
		//the result of taking the cross-product between the two sides of every triangle that the vertex is involved in
		//and summing them. 

		//Iterates through the loop and connects the vertices into triangular shapes that blur together into the final shape
		//the max index of the loop does not include the last row of points as each row constructs triangles with the row
		//beneath it and thus the last row does not need to construct triangles

		for(int a = 0; a < (int)(omegaPoints * phiPoints); ++a) {
		if(a < (omegaPoints - 1) * phiPoints) { //last row does not need to construct triangles as there is no row beneath it
			if(((int)a % (int)phiPoints) != ((int)phiPoints-1)) {
				this->va_indices.push_back(glm::ivec3(a+phiPoints,a+phiPoints+1,a));
				this->va_indices.push_back(glm::ivec3(a+phiPoints+1,a + 1,a));
			}
			else {
				this->va_indices.push_back(glm::ivec3(a+phiPoints,a+1,a));
				this->va_indices.push_back(glm::ivec3(a+1,a-phiPoints+1,a));
			}
		}
		//the top row of normals are easily predicted due to the shape of the balloon, the rest are calculated
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
				//points at the end of the row must wrap around the array to find their neighbor points
				if(((int)a % (int)phiPoints) != ((int)phiPoints-1)) {
					two = va_vertices[GLuint(a + 1)];
					if(a < (omegaPoints - 1) * phiPoints) three = va_vertices[GLuint(a + phiPoints + 1)];
				}
				else {
					two = va_vertices[GLuint(a - phiPoints + 1)];
					if(a < (omegaPoints - 1) * phiPoints) three = va_vertices[GLuint(a + 1)];
				}
				if(a < (omegaPoints - 1) * phiPoints) four = va_vertices[GLuint(a + phiPoints)];
				//points at the end of the row must wrap around the array to find their neighbor points
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
				this->va_normals.push_back((glm::normalize(sum)));
			}
		}

		//draw a square for the floor
			
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
		
		//starting index of square points is after all hemisphere points
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

	glEnable(GL_CULL_FACE);
} 