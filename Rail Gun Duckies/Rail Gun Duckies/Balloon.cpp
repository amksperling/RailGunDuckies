/* We've officially started on the balloon. */

#include "Balloon.h"

const float PI = 3.14159265f;


Balloon::Balloon() {

}

Balloon::~Balloon() {

}

void Balloon::render() {
	//Not set to balloon material yet
	GLfloat material_ambient[] = {.00, .00, 0, 1};
	GLfloat material_diffuse[] = { .5, .5, 0, 1 };
    GLfloat material_specular[] = { .6, .6, .5, 1 };
    GLfloat material_shininess[] = { .25 * 128 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess); 

	if (this->va_vertices.size() == 0) {	
/*		GLfloat height;
		GLfloat r;
		GLfloat angle;
		r = 0;

		for(height = (GLfloat)1; height >=(GLfloat).8; height -=(GLfloat).1) {
			for(angle = 0; angle < 360; angle+=40){
				this->va_vertices.push_back(glm::vec3((r * cos(angle*(PI/180))), height, (r * sin(angle*(PI/180)))));
			    this->va_colors.push_back(glm::vec4(1.0f,0.0f,0.0f,1.0f));
			}
			r+=(GLfloat)0.1;
		}
		for(height = (GLfloat).7; height >= (GLfloat)0; height -=(GLfloat).05) {
		    r  = (GLfloat)(cos((height/.7) * (PI/2)));
			for(angle = 0; angle < 360; angle+=40) {
				this->va_vertices.push_back(glm::vec3((r * cos(angle*(PI/180))), height, (r * sin(angle*(PI/180)))));
				this->va_colors.push_back(glm::vec4(1.0f,0.0f,0.0f,1.0f));
			}
		}

		GLfloat a;
		GLfloat b;
		for(a = 0; a < 18; a++) {
			for(b = 0; b < 9; b++) {
				this->va_indices.push_back(glm::ivec3(a+b,a+b+91,a+b+90));
				this->va_indices.push_back(glm::ivec3(a+b,a+b+1,a+b+91));
			}
		}
	} */

	GLfloat r;
	GLfloat o;
	GLfloat p;

	r = 1;

	GLfloat omegaPoints = 21;
	GLfloat omegaIncrement = 180/(omegaPoints-1);

	GLfloat phiPoints = 20;
	GLfloat phiIncrement = 360/phiPoints;

	for(o = (GLfloat)0; o <=(GLfloat)180; o +=omegaIncrement) {
		for(p = (GLfloat)0; p <(GLfloat) 360; p +=phiIncrement) {
			
			if(o < 117) r = 1;
			else if(o == 117) r = ((o+2)/117);
			else if(o == 126) r = ((o+5)/126);
			else if(o == 135) r = ((o)/126);
			else r = ((o-3)/126);
			
			this->va_vertices.push_back(glm::vec3((r * sin(o*(PI/180))* cos(p*(PI/180))), (r * cos(o*(PI/180))), (r * sin(o*(PI/180))* sin(p*(PI/180)))));
			this->va_colors.push_back(glm::vec4(1.0f,0.0f,0.0f,1.0f));
		}
	}
	
	GLfloat height;
	GLfloat angle;
	r = 0;
	GLfloat heightPoints = 6;
	GLfloat heightIncrement  = 0.1/(heightPoints-1);
	GLfloat anglePoints = 18;
	GLfloat angleIncrement = 360/anglePoints;

	for(height = (GLfloat)-1.4; height >=(GLfloat)-1.5; height -=heightIncrement) {
		for(angle = 0; angle < 360; angle+=angleIncrement){
			this->va_vertices.push_back(glm::vec3((r * cos(angle*(PI/180))), height, (r * sin(angle*(PI/180)))));
			this->va_colors.push_back(glm::vec4(1.0f,0.0f,0.0f,1.0f));
		}
		r+=(GLfloat)0.02;
	}
	
	GLfloat a;
	GLfloat aMax = (omegaPoints - 1) * phiPoints;
	for(a = 0; a < aMax; a++) {
		if(((int)a % (int)phiPoints) != ((int)phiPoints-1)){
		this->va_indices.push_back(glm::ivec3(a,a+phiPoints+1,a+phiPoints));
		this->va_indices.push_back(glm::ivec3(a,a + 1,a+phiPoints+1));
		}
		else{
		this->va_indices.push_back(glm::ivec3(a,a+1,a+phiPoints));
		this->va_indices.push_back(glm::ivec3(a,a-phiPoints+1,a+1));
		}
	} 

	GLfloat b = omegaPoints * phiPoints;
	GLfloat bMax = b + (heightPoints - 1) * anglePoints;
	for(b = omegaPoints * phiPoints; b < bMax; b++) {
		if(((int)(b-(omegaPoints*phiPoints)) % (int)anglePoints) != ((int)anglePoints-1)){
		this->va_indices.push_back(glm::ivec3(b,b+anglePoints+1,b+anglePoints));
		this->va_indices.push_back(glm::ivec3(b,b + 1,b+anglePoints+1));
		}
		else{
		this->va_indices.push_back(glm::ivec3(b,b+1,b+anglePoints));
		this->va_indices.push_back(glm::ivec3(b,b-anglePoints+1,b+1));
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



void Balloon::drawDiamond() {
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