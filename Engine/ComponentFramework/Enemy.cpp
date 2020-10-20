#include "Enemy.h"

Enemy::Enemy(Pawn* player)
{
	this->player = player;
	fovAngle = 90;
}

Enemy::Enemy(Pawn* player, float angleOfFieldOfView)
{
	this->player = player;
	fovAngle = angleOfFieldOfView;
}

Enemy::~Enemy()
{
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
	if (acos(VMath::dot((VMath::normalize(body->getPos() + player->body->getPos())), //Gets direction to player
		body->getForwardVector())) //Dotted with forward vector to check angle
		/ DEGREES_TO_RADIANS //acos returns radians so it must be converted
		< fovAngle) {
		//if(rayCast.forward.hit = player) {return true} else { return false}
		//RayCast needed
		return true;
	}
	else {
		return false;
	}
}
