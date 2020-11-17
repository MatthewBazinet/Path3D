#include "Raycast.h"
#include "VMath.h"
#include "Physics.h"

Raycast::Raycast(){
	start = Vec3();
	dir = start;
}

Raycast::Raycast(Vec3 start_, Vec3 dir_)
{
	start = start_;
	dir = dir_;
}

Raycast::~Raycast() {

}

Vec3 Raycast::currentPosition(float t) const
{
	return start + (dir * t);
}

float Raycast::distanceToPoint(Vec3 point) const
{
	Vec3 a = point - start;
	float a1 = pow(VMath::mag(a), 2);
	float b = VMath::dot(a, dir);
	b = (b * b) / pow(VMath::mag(dir), 2);
	float d = a1 - b;
	d = sqrt(d);
	return d;
}

std::string Raycast::getTag(PhysicsObject objects[], int length)
{
	for (int i = 0; i < length; i++) {
		if (Physics::SphereRayCollision(objects[i], *this)){
			return std::string(objects[i].tag);
		}
		else {
			return "NoHit";
		}
	}
}
