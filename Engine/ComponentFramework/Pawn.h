#ifndef PAWN_H
#define PAWN_H
#include "MeshObject.h"

struct GridWithWeights;
struct GridVec;

class Pawn
{

public:
	MeshObject* meshBody;
	Pawn();
	Pawn(MeshObject* aMeshBody);
	Pawn(MeshObject* aMeshBody, float aSpeed);
	~Pawn();



	void Update(float deltaTime);
	void Render();
	void FindPath(GridWithWeights grid, GridVec targetPosition);

	void MoveInDir(Vec3 dir);
	void FollowPath(vector<Vec3> aPath);
	Vec3 GetGridVec();

protected:
	float speed;
	int index;
	vector<Vec3> path;
	Vec3 destination;
	Vec3 direction;
};

#endif