#pragma once
#include <stdio.h>
#include <vector>
#include <assert.h>

#include <GL/freeglut.h>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

class Object {

public:
	Object();
	Object(bool isMoving, vec3 position, vec3 velocity, vec3 rotation, vec4 color);
	~Object();

//	virtual void render();
//  virtual void updatePosition();

	void drawRect(float w, float h, float d, float r, float g, float b);

	inline void setShouldBeRemoved(bool shouldBeRemoved) { this->shouldBeRemoved = shouldBeRemoved; }
	inline void setIsMoving(bool isMoving) { this->isMoving = isMoving; }
	inline void setPosition(vec3 position) { this->position = position; }
	inline void setVelocity(vec3 velocity) { this->velocity = velocity; }
	inline void setRotation(vec3 rotation) { this->rotation = rotation; }
	inline void setColor(vec4 color) { this->color = color; }

	inline bool getShouldBeRemoved() { return this->shouldBeRemoved; }
	inline bool getIsMoving() { return this->isMoving; }
	inline vec3 getPosition() { return this->position; }
	inline vec3 getVelocity() { return this->velocity; }
	inline vec3 getRotation() { return this->rotation; }
	inline vec4 getColor() { return this->color; }

private:

	bool shouldBeRemoved;
	bool isMoving;
	vec3 position;
	vec3 velocity;
	vec3 rotation;
	vec4 color;

};