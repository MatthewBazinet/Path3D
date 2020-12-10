#include "Enemy.h"
#include "Physics.h"

Enemy::Enemy(MeshObject* aMeshObject, Pawn* player)
{
	meshBody = aMeshObject;
	this->player = player;
	fovAngle = 90;
}

Enemy::Enemy(MeshObject* aMeshObject, Pawn* player, float angleOfFieldOfView)
{
	meshBody = aMeshObject;
	this->player = player;
	fovAngle = angleOfFieldOfView;
}

Enemy::~Enemy()
{
	delete meshBody;
	meshBody = nullptr;
	delete player;
	player = nullptr;
}

void Enemy::Update()
{
	if (CanSeePlayer()) {
		
	}
	else {

	}

}

bool Enemy::CanSeePlayer()
{
	Raycast ray = Raycast(meshBody->getPos(), meshBody->getForwardVector());
	if (acos(VMath::dot((VMath::normalize(meshBody->getPos() + player->meshBody->getPos())), meshBody->getForwardVector())) / DEGREES_TO_RADIANS < fovAngle) {
		//Gets direction to player
		//Dotted with forward vector to check angle
		//acos returns radians so it must be converted

		if (ray.getTag(player->meshBody, 1)._Equal("Player")) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}
