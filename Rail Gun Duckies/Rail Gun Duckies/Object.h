#pragma once
#include <stdio.h>
#include <vector>
#include <assert.h>

#include <GL/freeglut.h>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

//Possible additions: isBeautyModel, arbitrary int for resolution (can change object resolution 1-5), setUpForRender will be setUpAndRender
//and do the position update, translation, and render in one method. Also, add draw circle for polished railgun

class Object {

public:
	Object();
	Object(bool isMoving, vec3 position, vec3 rotation, vec3 scale, vec3 velocity, vec4 color);
	~Object();

//	virtual void render();
//  virtual void updatePosition(double timeStep, double gravity);

	void setUpForRender();

	void drawRect(float w, float h, float d, float r, float g, float b);
	void Object::drawVecArrayBox(float w, float h, float d, float r, float g, float b, Object &objectToModify);
	void Object::drawVecArrayFace(float w, float h, float r, float g, float b, Object &objectToModify);
	void Object::drawVecArrayCircle(int radialPoints, float radius, float r, float g, float b, Object &objectToModify);

	inline void setShouldBeRemoved(bool shouldBeRemoved) { this->shouldBeRemoved = shouldBeRemoved; }
	inline void setIsMoving(bool isMoving) { this->isMoving = isMoving; }
	inline void setPosition(vec3 position) { this->position = position; }
	inline void setRotation(vec3 rotation) { this->rotation = rotation; }
	inline void setScale(vec3 rotation) { this->scale = scale; }
	inline void setVelocity(vec3 velocity) { this->velocity = velocity; }
	inline void setColor(vec4 color) { this->color = color; }

	inline bool getShouldBeRemoved() { return this->shouldBeRemoved; }
	inline bool getIsMoving() { return this->isMoving; }
	inline vec3 getPosition() { return this->position; }
	inline vec3 getRotation() { return this->rotation; }
	inline vec3 getScale() { return this->scale; }
	inline vec3 getVelocity() { return this->velocity; }
	inline vec4 getColor() { return this->color; }

private:

	bool shouldBeRemoved;
	bool isMoving;
	vec3 position;
	vec3 rotation;
	vec3 scale;
	vec3 velocity;
	vec4 color;

};