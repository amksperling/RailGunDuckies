/* We've officially started on the balloon. */

#include "Balloon.h"

#define PI 3.14159265

Balloon::Balloon() {

}

Balloon::~Balloon() {

}

void Balloon::render() {

}

void Balloon::drawBalloon()
{
	if (this->va_vertices.size() == 0)
	{	
		GLfloat height;
		GLfloat r;
		GLfloat angle;
		r = 0;
		for(height = 1; height >=.8; height -=.1){
			for(angle = 0; angle < 360; angle+=40){
				this->va_vertices.push_back(glm::vec3((r * cos(angle*PI/180)),height,(r * sin(angle*PI/180))));
			}
			r+=0.1;
		}
		for(height = .7; height >= 0; height -=.05){
		    r  = cos((height/.7) * (PI/2));
			for(angle = 0; angle < 360; angle+=40){
				this->va_vertices.push_back(glm::vec3((r * cos(angle*PI/180)),height,(r * sin(angle*PI/180))));
			}
		}

		this->va_colors.push_back(glm::vec4(1.0f,0.0f,0.0f,1.0f));
		this->va_colors.push_back(glm::vec4(0.0f,1.0f,0.0f,1.0f));
		this->va_colors.push_back(glm::vec4(0.0f,0.0f,1.0f,1.0f));
		this->va_colors.push_back(glm::vec4(1.0f,1.0f,1.0f,1.0f));
		this->va_colors.push_back(glm::vec4(1.0f,0.0f,0.0f,1.0f));
		this->va_colors.push_back(glm::vec4(1.0f,0.0f,0.0f,1.0f));

		GLfloat a;
		GLfloat b;
		for(a = 0; a < 18; a++){
			for(b = 0; b < 9; b++){
				this->va_indices.push_back(glm::ivec3(a+b,a+b+91,a+b+90));
				this->va_indices.push_back(glm::ivec3(a+b,a+b+1,a+b+91));
			}
		}
	}

	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(3 , GL_FLOAT , 0 , &this->va_vertices[0]);
	glColorPointer(4, GL_FLOAT, 0, &this->va_colors[0]);

	glDrawElements(GL_TRIANGLES , 3 * this->va_indices.size() , GL_UNSIGNED_INT , &this->va_indices[0]);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}



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