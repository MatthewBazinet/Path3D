#ifndef PAWN_H
#define PAWN_H
#include "PhysicsObject.h"
class Pawn
{
public:
	Pawn();
	Pawn(PhysicsObject* body);
	~Pawn();

	PhysicsObject* body;

	void Update();

	void MoveInDir(Vec3 dir, float speed);

protected:
	float speed;
};

#endif