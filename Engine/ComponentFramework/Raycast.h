#ifndef RAYCAST_H
#define RAYCAST_H

#include "Vector.h"
#include "PhysicsObject.h"

using namespace MATH;


class Raycast
{
	friend class Physics;
protected:
	Vec3 start, dir;
public:
	Raycast();
	Raycast(Vec3 start_, Vec3 dir_);
	~Raycast();
	Vec3 currentPosition(float t) const;
	float distanceToPoint(Vec3 point) const;
	std::string getTag(PhysicsObject object[], int length);
};

#endif

