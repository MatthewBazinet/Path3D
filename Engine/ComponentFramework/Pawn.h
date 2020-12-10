#ifndef PAWN_H
#define PAWN_H
#include "PhysicsObject.h"
#include "Pathfinding.h"
#include "MeshObject.h"

class Pawn
{
public:
	MeshObject* meshBody;
	Pawn();
	Pawn(MeshObject* aMeshBody);
	Pawn(MeshObject* aMeshBody, float aSpeed);
	~Pawn();



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