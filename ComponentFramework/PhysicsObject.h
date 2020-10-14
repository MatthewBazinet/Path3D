#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H
#include "Vector.h"
#include "Sphere.h"

using namespace MATH;

class PhysicsObject {
	friend class Physics;
public:
	PhysicsObject();
	virtual ~PhysicsObject();
	

public:
	/// Untility functions so small they cane be inlined
	inline void setPos(const Vec3 &pos_) { pos = pos_; }
	inline Vec3 getPos() const { return pos; }
	inline void setVel(const Vec3 &vel_) { vel = vel_; }
	inline Vec3 getVel() { return vel; }
	inline void setAccel(const Vec3 &accel_) { accel = accel_; }
	inline Vec3 getAccel() { return accel; }
	inline void applyForce(const Vec3 force) { accel = force / mass;  }
	inline void ApplyTorque(const float torque) {angularAcc = torque / rotationalInertia; }
	inline void setAngularVelocity(const float angularVel_) { angularVel = angularVel_; }
	inline void setRotationalInertia(const float rotationalInertia_) { rotationalInertia = rotationalInertia_; }
	inline float getAngle() { return angle; }
	inline void setMass(float mass_) { mass = mass_; }

protected:
	Vec3 pos, vel, accel;
	float mass;
	Sphere boundingSphere;
	float rotationalInertia;
	float angle, angularVel, angularAcc;
};
#endif

