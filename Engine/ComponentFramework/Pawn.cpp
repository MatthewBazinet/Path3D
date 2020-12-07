#include "Pawn.h"
#include "Physics.h"

Pawn::Pawn()
{
	body = new PhysicsObject();
	speed = 1.0f;
	index = 0;
}

Pawn::Pawn(PhysicsObject* aBody)
{
	body = aBody;
	speed = 1.0f;
	index = 0;

}

Pawn::Pawn(PhysicsObject* aBody, float aSpeed)
{
	body = aBody;
	speed = aSpeed;
	index = 0;
}

Pawn::Pawn(float aSpeed)
{
	body = new PhysicsObject();
	speed = aSpeed;
	index = 0;
}

Pawn::~Pawn()
{
}

void Pawn::Update(float deltaTime)
{
	Physics::SimpleNewtonMotion(*body, deltaTime);
	Vec3 pos = body->getPos();
	if (path.size > 0) {
		if (pos.x >= destination.x - 0.1 && pos.x <= destination.x + 0.1) {
			if (pos.y >= destination.y - 0.1 && pos.y <= destination.y + 0.1) {
				if (index == path.size) {
					destination = body->getPos();
					index = 0;
					path.clear;
				}
				else {
					index++;
					destination.x = path[index].x;
					destination.y = path[index].y;
				}
			}
		}
		Vec3 direction = VMath::normalize(destination + pos);
		MoveInDir(direction);
	}
}

void Pawn::MoveInDir(Vec3 dir)
{
	Vec3 vel = dir * speed;
	body->setVel(vel);
}

void Pawn::FollowPath(vector<Node> aPath)
{
	path = aPath;
	destination.x = path[0].x;
	destination.y = path[0].y;
}
