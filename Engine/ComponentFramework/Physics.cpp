#include "Physics.h"
#include <iostream>


void Physics::SimpleNewtonMotion(PhysicsObject &object, const float deltaTime) {
	object.angularVel += object.angularAcc * deltaTime;
	object.angle += object.angularVel * deltaTime + 0.5f * object.angularAcc * deltaTime * deltaTime;
	object.pos += object.vel * deltaTime + 0.5f * object.accel * deltaTime * deltaTime;
	object.vel += object.accel * deltaTime;
}

bool Physics::PlaneSphereCollision(const PhysicsObject &object, const Plane &p) {

	Vec3 a = object.getPos();
	float b = a * Vec3(p.x, p.y, p.z);
	b += p.d;
	b /=  VMath::mag(Vec3(p.x, p.y, p.z));
	b = abs(b);

	if (b <= object.boundingSphere.r) {
		return true;
	}
	else {

		return false;
	}
}

void Physics::PlaneSphereCollisionResponse(PhysicsObject &object, const Plane &p) {
	//body1->vel = (body1->vel) * -1 + Vec3(2 * plane.plane.x, 2 * plane.plane.y, 2 * plane.plane.z) * (body1->vel * Vec3(plane.plane.x, plane.plane.y, plane.plane.z));
	Vec3 normal = Vec3(p.x, p.y, p.z);
	VMath::normalize(normal);
	Vec3 p1 = object.vel * -1;
	p1 = normal * (normal * p1);
	object.vel += p1 * 2;
	if (abs(object.vel.x) < VERY_SMALL) { object.vel.x = 0; }
	if (abs(object.vel.y) < VERY_SMALL) { object.vel.y = 0; }
	if (abs(object.vel.z) < VERY_SMALL) { object.vel.z = 0; }

}

bool Physics::SphereSphereCollision(const PhysicsObject &object1, const PhysicsObject &object2) {
	float distance = sqrt(pow(object2.pos.x - object1.pos.x, 2) + pow(object2.pos.y - object1.pos.y, 2) + pow(object2.pos.z - object1.pos.z, 2));
	if (distance < object1.boundingSphere.r + object2.boundingSphere.r) {
		return true;
	}
	else {
		return false;
	}
}

void Physics::SphereSphereCollisionResponse(PhysicsObject &object1, PhysicsObject &object2) {
	float e = 0.884f;//0.99f;
	Vec3 lineOfAction = object1.pos - object2.pos;
	Vec3 normalizedLineOfAction = lineOfAction / (sqrt(lineOfAction.x * lineOfAction.x + lineOfAction.y * lineOfAction.y + lineOfAction.z * lineOfAction.z));
	float v1p = normalizedLineOfAction * object1.vel;
	float v2p = normalizedLineOfAction * object2.vel;

	if (v1p - v2p > 0.0f) return;

	float v1pnew = (((object1.mass - e * object2.mass) * v1p) + ((1.0f + e) * object2.mass * v2p) / (object2.mass + object1.mass));
	float v2pnew = (((object2.mass - e * object1.mass) * v2p) + ((1.0f + e) * object1.mass * v1p) / (object1.mass + object2.mass));

	object1.vel += normalizedLineOfAction * (v1pnew - v1p);
	object2.vel += normalizedLineOfAction * (v2pnew - v2p);
}

bool Physics::SphereRayCollision(PhysicsObject& sphere, Raycast& ray)
{
	Vec3 position = Vec3(sphere.boundingSphere.x, sphere.boundingSphere.y, sphere.boundingSphere.z);
	float a = ray.dir * ray.dir;
	float b = 2 * ((ray.start - position) * ray.dir);
	float c = (ray.start - position) * (ray.start - position) - sphere.boundingSphere.r * sphere.boundingSphere.r;
	float d = b * b - 4 * a * c;

	if (d < 0) {
		return false;
	}
	else {
		float t1 = (-b + sqrt(d)) / (2 * a);
		float t2 = (-b - sqrt(d)) / (2 * a);
		if (t1 >= 0 || t2 >= 0) {
			return true;
		}
		else {
			return false;
		}
	}
}
