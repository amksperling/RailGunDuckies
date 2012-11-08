#include "Diamond.h"

vector<vec3> Diamond::va_vertices;
vector<ivec3> Diamond::va_indices;
vector<vec3> Diamond::va_normals;

Diamond::Diamond() {
}

Diamond::Diamond(bool isMoving, vec3 position, vec3 rotation, vec3 scale, vec3 velocity, vec4 color, int pointValue, int lifetime) : 
	Object(isMoving, position, rotation, scale, velocity, color){
		this->pointValue = pointValue;
		this->lifetime = lifetime;
} 

Diamond::~Diamond() {

}


void Diamond::render() {
	glDisable(GL_COLOR_MATERIAL); //disabled, so that the color will be determined by the material specified below

	//Unique color and alpha values for each component of light result in giving a unique look to the
	//model. These values were chosen to simulate the appearance of a shiny, semi-transparent balloon
	GLfloat material_ambient_gold[] = {0.25f, 0.20f, 0.08f, 0.8f};
    GLfloat material_diffuse_gold[] = {0.75f, 0.61f, 0.22f, 0.8f};
    GLfloat material_specular_gold[] = { 0.63f, 0.56f, 0.37f, 0.7f};
    GLfloat material_shininess_gold[] = { .4f * 128.0f };

	GLfloat material_ambient_silver[] = { 0.7f, 0.6f, 0.6f, 0.7f};
    GLfloat material_diffuse_silver[] = { 0.7f, 0.6f, 0.6f, 0.7f};
    GLfloat material_specular_silver[] = { 0.7f, 0.6f, 0.6f, 0.7f};
    GLfloat material_shininess_silver[] = { .25f * 128.0f };

	GLfloat material_ambient_red[] = {1.0f, 0.1f, 0.1f, 0.8f};
    GLfloat material_diffuse_red[] = {1.0f, 0.1f, 0.1f, 0.8f};
    GLfloat material_specular_red[] = { 0.7f, 0.6f, 0.6f, 0.7f};
    GLfloat material_shininess_red[] = { .25f * 128.0f };

	GLfloat material_ambient_green[] = {0.1f, 1.0f, 0.1f, 0.8f};
    GLfloat material_diffuse_green[] = {0.1f, 1.0f, 0.1f, 0.8f};
    GLfloat material_specular_green[] = { 0.6f, 0.7f, 0.6f, 0.7f};
    GLfloat material_shininess_green[] = { .25f * 128.0f };

	GLfloat material_ambient_blue[] = {0.1f, 0.1f, 1.0f, 0.8f};
    GLfloat material_diffuse_blue[] = {0.1f, 0.1f, 1.0f, 0.8f};
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

	if (this->va_vertices.size() == 0)
	{
		this->va_vertices.push_back(glm::vec3(0.0f,2.0f,0.0f)); //0 //glmVec3 //single digits
		this->va_vertices.push_back(glm::vec3(1.0f,1.0f,0.0f)); //1
		this->va_vertices.push_back(glm::vec3(-1.0f,1.0f,0.0f)); //2
		this->va_vertices.push_back(glm::vec3(0.0f,1.0f,1.0f)); //3
		this->va_vertices.push_back(glm::vec3(0.0f,1.0f,-1.0f)); //4
		this->va_vertices.push_back(glm::vec3(0.0f,0.0f,0.0f)); //5

		this->va_indices.push_back(glm::ivec3(0,1,3));
		this->va_indices.push_back(glm::ivec3(2,0,3));
		this->va_indices.push_back(glm::ivec3(2,4,0));
		this->va_indices.push_back(glm::ivec3(4,1,0)); 
		this->va_indices.push_back(glm::ivec3(5,1,3));
		this->va_indices.push_back(glm::ivec3(2,5,3));
		this->va_indices.push_back(glm::ivec3(2,4,5));
		this->va_indices.push_back(glm::ivec3(4,1,5));

		this->va_normals.push_back(glm::vec3(0.0f,1.0f,0.0f)); //0 //glmVec3 //single digits
		this->va_normals.push_back(glm::vec3(0.5f,0.5f,0.0f)); //1
		this->va_normals.push_back(glm::vec3(-0.5f,0.5f,0.0f)); //2
		this->va_normals.push_back(glm::vec3(0.0f,0.5f,0.5f)); //3
		this->va_normals.push_back(glm::vec3(0.0f,0.5f,-0.5f)); //4
		this->va_normals.push_back(glm::vec3(0.0f,-1.0f,0.0f));

	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glVertexPointer(3 , GL_FLOAT , 0 , &this->va_vertices[0]);
	glNormalPointer(GL_FLOAT, 0, &va_normals[0]);

	glDrawElements(GL_TRIANGLES , 3 * this->va_indices.size() , GL_UNSIGNED_INT , &this->va_indices[0]);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

	glEnable(GL_COLOR_MATERIAL);
} 
