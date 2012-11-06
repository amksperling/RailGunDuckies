#include "Balloon.h"

const float PI = 3.14159265f;

vector<vec3> Balloon::va_vertices;
vector<ivec3> Balloon::va_indices;
vector<vec3> Balloon::va_normals;

Balloon::Balloon() {
	this->pointValue = 0;
}

Balloon::Balloon(bool isMoving, vec3 position, vec3 rotation, vec3 scale, vec3 velocity, vec4 color) : 
	Object(isMoving, position, rotation, scale, velocity, color){
	this->pointValue = 0;
} 

Balloon::~Balloon() {

}

void Balloon:: render() {
	//Source: https://uwmad.courses.wisconsin.edu/d2l/lms/content/viewer/main_frame.d2l?tId=11011796&ou=1821693
	//Example vertex array code used to figure out vertex arrays

	//GL_CULL_FACE is left enabled as disabling it leads to bizarre ripple effects
	glDisable(GL_COLOR_MATERIAL); //disabled, so that the color will be determined by the material specified below
	GLboolean blendAlreadyEnabled; 
	glGetBooleanv(GL_BLEND, &blendAlreadyEnabled); //checks if blending is already enable, to later restore the previous state
	if(blendAlreadyEnabled) glBlendFunc(GL_ONE, GL_ONE);
	else glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	//Unique color and alpha values for each component of light result in giving a unique look to the
	//model. These values were chosen to simulate the appearance of a shiny, semi-transparent balloon
	GLfloat material_ambient_gold[] = {0.25f, 0.20f, 0.08f, 0.8f};//{ 0.7f, 0.6f, 0.6f, 0.7f};
    GLfloat material_diffuse_gold[] = {0.75f, 0.61f, 0.22f, 0.8f};//{ 0.7f, 0.6f, 0.6f, 0.7f};
    GLfloat material_specular_gold[] = { 0.63f, 0.56f, 0.37f, 0.7f};
    GLfloat material_shininess_gold[] = { .4f * 128.0f };

	GLfloat material_ambient_silver[] = { 0.7f, 0.6f, 0.6f, 0.7f};
    GLfloat material_diffuse_silver[] = { 0.7f, 0.6f, 0.6f, 0.7f};
    GLfloat material_specular_silver[] = { 0.7f, 0.6f, 0.6f, 0.7f};
    GLfloat material_shininess_silver[] = { .25f * 128.0f };

	GLfloat material_ambient_red[] = {1.0f, 0.1f, 0.1f, 0.8f};//{ 0.7f, 0.6f, 0.6f, 0.7f};
    GLfloat material_diffuse_red[] = {1.0f, 0.1f, 0.1f, 0.8f};//{ 0.7f, 0.6f, 0.6f, 0.7f};
    GLfloat material_specular_red[] = { 0.7f, 0.6f, 0.6f, 0.7f};
    GLfloat material_shininess_red[] = { .25f * 128.0f };

	GLfloat material_ambient_green[] = {0.1f, 1.0f, 0.1f, 0.8f};//{ 0.7f, 0.6f, 0.6f, 0.7f};
    GLfloat material_diffuse_green[] = {0.1f, 1.0f, 0.1f, 0.8f};//{ 0.7f, 0.6f, 0.6f, 0.7f};
    GLfloat material_specular_green[] = { 0.6f, 0.7f, 0.6f, 0.7f};
    GLfloat material_shininess_green[] = { .25f * 128.0f };

	GLfloat material_ambient_blue[] = {0.1f, 0.1f, 1.0f, 0.8f};//{ 0.7f, 0.6f, 0.6f, 0.7f};
    GLfloat material_diffuse_blue[] = {0.1f, 0.1f, 1.0f, 0.8f};//{ 0.7f, 0.6f, 0.6f, 0.7f};
    GLfloat material_specular_blue[] = { 0.6f, 0.6f, 0.7f, 0.7f};
    GLfloat material_shininess_blue[] = { .25f * 128.0f };

	if(this->pointValue >= 55){
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_ambient_gold);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse_gold);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_specular_gold);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, material_shininess_gold);
	}
	else if(this->pointValue >= 50){
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_ambient_silver);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse_silver);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_specular_silver);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, material_shininess_silver);
	}
	else if(this->pointValue % 3 == 0){
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_ambient_blue);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse_blue);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_specular_blue);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, material_shininess_blue);
	}
	else if(this->pointValue % 2 == 0){
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_ambient_green);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse_green);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_specular_green);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, material_shininess_green);
	}
	else{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_ambient_red);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse_red);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_specular_red);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, material_shininess_red);
	}

	if (va_vertices.size() == 0) {

		GLfloat r;
		GLfloat o;
		GLfloat p;
		r = 1.0;

		//The balloon is drawn by specifying individual vertexes. In this case, the top half of the
		//balloon is drawn by loops that draw verticle stacks of circles of non-linear radius which are connected to form
		//a balloon shape. In this case, the circles are made by taking polar coordinates and converting
		//them back into cartesian.

		//The balloon's unique bottom shape is due to an equation which varies the distance of the stack of circles
		//from the center of the shape in a non-linear form.

		GLfloat omegaPoints = 91.0f;
		GLfloat omegaIncrement = 180/(omegaPoints-1);

		//The value to increment between the points is determined by the desired space to fill over the number
		//of points. In this case, a 1 is subtracted from the points, because 0 is counted as the first point
		//and the loop runs until the value equals the desired size.

		GLfloat phiPoints = 120.0f;
		GLfloat phiIncrement = 360/phiPoints;

		//Source: http://electron9.phys.utk.edu/vectors/3dcoordinates.htm used to translate polar to 
		for(o = (GLfloat)0; o <=(GLfloat)180; o +=omegaIncrement) {
			for(p = (GLfloat)0; p <(GLfloat) 360; p +=phiIncrement) {
			
				if(o < .5 * 180) r = (GLfloat) 1;
				else r = (GLfloat) (1+ (1-cos((o-90)*(PI/180)))/2);
			
				this->va_vertices.push_back(glm::vec3((r * sin(o*(PI/180))* cos(p*(PI/180))), 
					(r * cos(o*(PI/180))), (r * sin(o*(PI/180))* sin(p*(PI/180)))));
			}
		}
	
		GLfloat height;
		GLfloat angle;
		r = 0.0;
		GLfloat heightPoints = 6.0;
		GLfloat heightIncrement  = 0.1f/(heightPoints-1);
		
		//The value to increment between the points is determined by the desired space to fill over the number
		//of points. In this case, a 1 is subtracted from the points, because 0 is counted as the first point
		//and the loop runs until the value equals the desired size.

		GLfloat anglePoints = 18.0;
		GLfloat angleIncrement = 360/anglePoints;

		GLfloat radialIncreasePerHeightIncrement = 0.02f;

		//A small cone is created on the bottom of the balloon by drawing a stack of circles of a linear radius.
		//Source: http://electron9.phys.utk.edu/vectors/2dcoordinates.htm used to translate polar to cartesian 2D
		for(height = (GLfloat)-1.45f; height >=(GLfloat)-1.55f; height -=heightIncrement) {
			for(angle = 0; angle < 360; angle+=angleIncrement){
				this->va_vertices.push_back(glm::vec3((r * cos(angle*(PI/180))), height, (r * sin(angle*(PI/180)))));
			}
			r+=radialIncreasePerHeightIncrement;
		}
	
		r = 1; //the radius is reset to 1 as it is used later

		//The vertices are then grouped into triangles and have their normals calculated by normalizing 
		//the result of taking the cross-product between the two sides of every triangle that the vertex is involved in
		//and summing them. 

		GLfloat a;
		GLfloat aMax = (omegaPoints - 1) * phiPoints;
		//Iterates through the loop and connects the vertices into triangular shapes that blur together into the final shape
		//the max index of the loop does not include the last row of points as each row constructs triangles with the row
		//beneath it and thus the last row does not need to construct triangles
		for(a = 0; a < aMax; a++) {
			//the last vertex in a row is unique as the point considered next to it is actually the first point in the row
			if(((int)a % (int)phiPoints) != ((int)phiPoints-1)) {
				this->va_indices.push_back(glm::ivec3(a,a+phiPoints+1,a+phiPoints));
				this->va_indices.push_back(glm::ivec3(a,a + 1,a+phiPoints+1));
			}
			else {
				this->va_indices.push_back(glm::ivec3(a,a+1,a+phiPoints));
				this->va_indices.push_back(glm::ivec3(a,a-phiPoints+1,a+1));
			}
			//the top row of normals are easily predicted due to the shape of the balloon, the rest are calculated
			if(a < phiPoints) {
				this->va_normals.push_back(glm::vec3(0,1,0));
			}
			else {

				//Source: http://glm.g-truc.net/code.html used to figure our normal calculations

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
					three = va_vertices[GLuint(a + phiPoints + 1)];
				}
				else {
					two = va_vertices[GLuint(a - phiPoints + 1)];
					three = va_vertices[GLuint(a + 1)];
				}
				four = va_vertices[GLuint(a + phiPoints)];
				//points at the end of the row must wrap around the array to find their neighbor points
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

		//The preceding loop did not address the final row of normals as it did not need to loop through the final
	    //row to specify vertices. This loop fills in the rest of the normals as they are easily predicted due to the
		//shape of the balloon.
		for(a = 0; a < phiPoints; ++a) {
			this->va_normals.push_back(glm::vec3(0,-1,0));
		}

		//The normals and indices of the cone beneath the balloon are calculated the same way.
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

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glVertexPointer(3 , GL_FLOAT , 0 , &va_vertices[0]);
	glNormalPointer(GL_FLOAT, 0, &va_normals[0]);

	glDrawElements(GL_TRIANGLES, 3 * va_indices.size(), GL_UNSIGNED_INT, &va_indices[0]);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

	glPushMatrix();
	glTranslated(0, -1.55, 0);
	glRotated(90, 1, 0, 0);
	glutSolidTorus((GLdouble) 0.018, (GLdouble) 0.11, (GLint) 20, (GLint) 20);
	//Source: http://www.nigels.com/glt/doc/class_glut_torus.html
	glPopMatrix();

	glEnable(GL_COLOR_MATERIAL);
	if(!blendAlreadyEnabled){
		glDisable(GL_BLEND);
	}
	else glBlendFunc(GL_ONE, GL_ONE);
}

/* //would overwrite balloon if called
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
} */
