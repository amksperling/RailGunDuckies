#pragma once
#include <stdio.h>
#include <vector>
#include <assert.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

/*
   The Object class is a superclass. It contains properties and methods that are useful to most, if not all, objects
   rendered in the scene.
*/

class Object {

public:
	Object();
	Object(bool isMoving, vec3 position, vec3 rotation, vec3 scale, vec3 velocity, vec4 color);
	~Object();

	virtual void render() = 0;

	void updateAndRender(float timeStep, bool shouldFall, bool shouldRender);

	void drawRect(float w, float h, float d, float r, float g, float b);
	void drawVecArrayBox(float w, float h, float d, float r, float g, float b, Object &objectToModify);
	void drawVecArrayFace(float w, float h, float r, float g, float b, Object &objectToModify);
	void drawVecArrayCircle(int radialPoints, float radius, float r, float g, float b, Object &objectToModify);

	void setShouldBeRemoved(bool shouldBeRemoved) { this->shouldBeRemoved = shouldBeRemoved; }
	void setIsMoving(bool isMoving) { this->isMoving = isMoving; }
	void setIsBeautyModeModel(bool isBeautyModeModel) { this->isBeautyModeModel = isBeautyModeModel; }
	void setPosition(vec3 position) { this->position = position; }
	void setRotation(vec3 rotation) { this->rotation = rotation; }
	void setBeautyModeRotationVector(vec3 beautyModeRotationVector) { this->beautyModeRotationVector = beautyModeRotationVector; }
	void setBeautyModeRotationSpeed(int beautyModeRotationSpeed) { this->beautyModeRotationSpeed = beautyModeRotationSpeed; }
	void setScale(vec3 scale) { this->scale = scale; }
	void setVelocity(vec3 velocity) { this->velocity = velocity; }
	void setColor(vec4 color) { this->color = color; }

	bool getShouldBeRemoved() { return this->shouldBeRemoved; }
	bool getIsMoving() { return this->isMoving; }
	bool getIsBeautyModeModel() { return this->isBeautyModeModel; }
	vec3 getPosition() { return this->position; }
	vec3 getRotation() { return this->rotation; }
	vec3 getBeautyModeRotationVector() { return this->beautyModeRotationVector; }
	int  getBeautyModeRotationSpeed() { return this->beautyModeRotationSpeed; }
	vec3 getScale() { return this->scale; }
	vec3 getVelocity() { return this->velocity; }
	vec4 getColor() { return this->color; }

private:
	bool shouldBeRemoved; //sets object for removal
	bool isMoving;        //indicates object is moving
	bool isBeautyModeModel; //indicates if the object is used for beauty mode
	vec3 position;        //current position of object relative to the origin
	vec3 rotation;        //indicates degrees to rotate about x, y, and z-axis
	vec3 beautyModeRotationVector; //indicates the axis to rotate the model around
	int  beautyModeRotationSpeed;  //number indicating the speed of rotation
	vec3 scale;           //scales object to this size
	vec3 velocity;        //velocity of object in units/time
	vec4 color;           //color object should be rendered
};
