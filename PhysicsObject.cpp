#include "PhysicsObject.h"

PhysicsObject::PhysicsObject():pos(0.0f),vel(0.0f),accel(0.0f),mass(0.0f),boundingSphere(0.0f){
	rotationalInertia = 1.0f;
	angle = angularAcc = angularVel = 0.0f;
}


PhysicsObject::~PhysicsObject(){

}

