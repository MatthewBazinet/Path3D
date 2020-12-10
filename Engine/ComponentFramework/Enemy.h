#ifndef ENEMY_H
#define ENEMY_H

#include "Pawn.h"

class Enemy: public Pawn
{

public:
	Enemy(MeshObject* aMeshObject, Pawn* player);
	Enemy(MeshObject* aMeshObject, Pawn* player, float angleOfFieldOfView);
	~Enemy();

	void Update();

private:
	Pawn* player;
	float fovAngle;
	bool CanSeePlayer();
};

#endif