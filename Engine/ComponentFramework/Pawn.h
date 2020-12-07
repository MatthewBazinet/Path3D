#ifndef PAWN_H
#define PAWN_H
#include "PhysicsObject.h"
#include "Pathfinding.h"
class Pawn
{
public:
	Pawn();
	Pawn(PhysicsObject* aBody);
	Pawn(PhysicsObject* aBody, float aSpeed);
	Pawn(float aSpeed);
	~Pawn();

	PhysicsObject* body;

	void Update(float deltaTime);

	void MoveInDir(Vec3 dir);
	void FollowPath(vector<Node> aPath);

protected:
	float speed;
	int index;
	vector<Node> path;
	Vec3 destination;
};

#endif