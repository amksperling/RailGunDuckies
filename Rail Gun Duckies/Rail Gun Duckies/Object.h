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

	inline void setShouldBeRemoved(bool shouldBeRemoved) { this->shouldBeRemoved = shouldBeRemoved; }
	inline void setIsMoving(bool isMoving) { this->isMoving = isMoving; }
	inline void setIsBeautyModeModel(bool isBeautyModeModel) { this->isBeautyModeModel = isBeautyModeModel; }
	inline void setPosition(vec3 position) { this->position = position; }
	inline void setRotation(vec3 rotation) { this->rotation = rotation; }
	inline void setBeautyModeRotationVector(vec3 beautyModeRotationVector) { this->beautyModeRotationVector = beautyModeRotationVector; }
	inline void setBeautyModeRotationSpeed(int beautyModeRotationSpeed) { this->beautyModeRotationSpeed = beautyModeRotationSpeed; }
	inline void setScale(vec3 scale) { this->scale = scale; }
	inline void setVelocity(vec3 velocity) { this->velocity = velocity; }
	inline void setColor(vec4 color) { this->color = color; }

	inline bool getShouldBeRemoved() { return this->shouldBeRemoved; }
	inline bool getIsMoving() { return this->isMoving; }
	inline bool getIsBeautyModeModel() { return this->isBeautyModeModel; }
	inline vec3 getPosition() { return this->position; }
	inline vec3 getRotation() { return this->rotation; }
	inline vec3 getBeautyModeRotationVector() { return this->beautyModeRotationVector; }
	inline int  getBeautyModeRotationSpeed() { return this->beautyModeRotationSpeed; }
	inline vec3 getScale() { return this->scale; }
	inline vec3 getVelocity() { return this->velocity; }
	inline vec4 getColor() { return this->color; }

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
