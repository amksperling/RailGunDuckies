#pragma once
#include <vector>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

class ModelManager {

public:
	ModelManager();
	~ModelManager();

	GLuint duckie_display_list;
	GLuint railgun_display_list;

	vector<vec3> va_vertices_balloon;
	vector<vec4> va_colors_balloon;
	vector<ivec3> va_indices_balloon;
	vector<vec3> va_normals_balloon;

	vector<vec3> va_vertices_world;
	vector<vec4> va_colors_world;
	vector<ivec3> va_indices_world;
	vector<vec3> va_normals_world;

	inline void setDuckieDisplayList(GLuint passedInDisplayList) { this->duckie_display_list = passedInDisplayList; }
	inline void setRailgunDisplayList(GLuint passedInDisplayList) { this->railgun_display_list = passedInDisplayList; }
	inline void setVerticesArrayBallon(vector<vec3> passedInVectorArray) { this->va_vertices_balloon = passedInVectorArray; }
	inline void setColorsArrayBallon(vector<vec4> passedInVectorArray) { this->va_colors_balloon = passedInVectorArray; }
	inline void setIndicesArrayBallon(vector<ivec3> passedInVectorArray) { this->va_indices_balloon = passedInVectorArray; }
	inline void setNormalsArrayBallon(vector<vec3> passedInVectorArray) { this->va_normals_balloon = passedInVectorArray; }
	inline void setVerticesArrayWorld(vector<vec3> passedInVectorArray) { this->va_vertices_world = passedInVectorArray; }
	inline void setColorsArrayWorld(vector<vec4> passedInVectorArray) { this->va_colors_world = passedInVectorArray; }
	inline void setIndicesArrayWorld(vector<ivec3> passedInVectorArray) { this->va_indices_world = passedInVectorArray; }
	inline void setNormalsArrayWorld(vector<vec3> passedInVectorArray) { this->va_normals_world = passedInVectorArray; }

	inline GLuint getDuckieDisplayList() { return this->duckie_display_list; }
	inline GLuint getRailgunDisplayList() { return this->railgun_display_list; }
	inline vector<vec3> getVerticesArrayBallon() { return this->va_vertices_balloon; }
	inline vector<vec4> getColorsArrayBallon() { return this->va_colors_balloon; }
	inline vector<ivec3> getIndicesArrayBallon() { return this->va_indices_balloon; }
	inline vector<vec3> getNormalsArrayBallon() { return this->va_normals_balloon; }
	inline vector<vec3> getVerticesArrayWorld() { return this->va_vertices_world; }
	inline vector<vec4> getColorsArrayWorld() { return this->va_colors_world; }
	inline vector<ivec3> getIndicesArrayWorld() { return this->va_indices_world; }
	inline vector<vec3> getNormalsArrayWorld() { return this->va_normals_world; }

private:
	
};