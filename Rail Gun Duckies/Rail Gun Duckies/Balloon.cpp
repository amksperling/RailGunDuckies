/* We've officially started on the balloon. */

#include "Balloon.h"

Balloon::Balloon() {

}

Balloon::~Balloon() {

}

void Balloon::render() {

}

// still need to specify vertecies!!!
void Balloon::drawDiamond()
{
	if (this->va_vertices.size() == 0)
	{
		this->va_vertices.push_back(glm::vec3(0.0f,2.0f,0.0f)); //0 //glmVec3 //single digits
		this->va_vertices.push_back(glm::vec3(1.0f,1.0f,0.0f)); //1
		this->va_vertices.push_back(glm::vec3(-1.0f,1.0f,0.0f)); //2
		this->va_vertices.push_back(glm::vec3(0.0f,1.0f,1.0f)); //3
		this->va_vertices.push_back(glm::vec3(0.0f,1.0f,-1.0f)); //4
		this->va_vertices.push_back(glm::vec3(0.0f,0.0f,0.0f)); //5

		this->va_colors.push_back(glm::vec4(1.0f,0.0f,0.0f,1.0f));
		this->va_colors.push_back(glm::vec4(0.0f,1.0f,0.0f,1.0f));
		this->va_colors.push_back(glm::vec4(0.0f,0.0f,1.0f,1.0f));
		this->va_colors.push_back(glm::vec4(1.0f,1.0f,1.0f,1.0f));
		this->va_colors.push_back(glm::vec4(1.0f,0.0f,0.0f,1.0f));
		this->va_colors.push_back(glm::vec4(1.0f,0.0f,0.0f,1.0f));

		this->va_indices.push_back(glm::ivec3(0,1,3));
		this->va_indices.push_back(glm::ivec3(2,0,3));
		this->va_indices.push_back(glm::ivec3(2,4,0));
		this->va_indices.push_back(glm::ivec3(4,1,0)); 
		this->va_indices.push_back(glm::ivec3(5,1,3));
		this->va_indices.push_back(glm::ivec3(2,5,3));
		this->va_indices.push_back(glm::ivec3(2,4,5));
		this->va_indices.push_back(glm::ivec3(4,1,5));

	}

	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(3 , GL_FLOAT , 0 , &this->va_vertices[0]);
	glColorPointer(4, GL_FLOAT, 0, &this->va_colors[0]);

	glDrawElements(GL_TRIANGLES , 3 * this->va_indices.size() , GL_UNSIGNED_INT , &this->va_indices[0]);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}


void Balloon::Triangle()
{
	/*glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50, ((double) this->width) / ((double) this->height), 1, 10);
	glViewport(0, 0, this->width, this->height);

	glClearColor(0, 0, 0.5, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, -5.5, 0, 0, 0, 0, 1, 0);*/

	if (this->va_v.size() == 0)
	{
		this->va_v.push_back(0);
		this->va_v.push_back(1);
		this->va_v.push_back(-1);
		this->va_v.push_back(-1);
		this->va_v.push_back(1);
		this->va_v.push_back(-1);

		this->va_c.push_back(1);
		this->va_c.push_back(0);
		this->va_c.push_back(0);
		this->va_c.push_back(0);
		this->va_c.push_back(1);
		this->va_c.push_back(0);
		this->va_c.push_back(0);
		this->va_c.push_back(1);

		this->va_i.push_back(0);
		this->va_i.push_back(1);
		this->va_i.push_back(2);
	}

	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(2 , GL_DOUBLE , 0 , &this->va_v[0]);
	glColorPointer(3, GL_DOUBLE, 0, &this->va_c[0]);

	glDrawElements(GL_TRIANGLES , 3 , GL_UNSIGNED_INT , &this->va_i[0]);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
} 