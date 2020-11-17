#include "Enemy.h"
#include "Physics.h"

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
	Raycast ray = Raycast(body->getPos(),body->getForwardVector());
	if (acos(VMath::dot((VMath::normalize(body->getPos() + player->body->getPos())), //Gets direction to player
		body->getForwardVector())) //Dotted with forward vector to check angle
		/ DEGREES_TO_RADIANS //acos returns radians so it must be converted
		< fovAngle) {
		if (ray.getTag(player->body, 1) == "Player") {
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
