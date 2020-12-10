#include "Pawn.h"
#include "Physics.h"

Pawn::Pawn()
{
	meshBody = nullptr;
	speed = 1.0f;
	index = 0;
	vector<Node> path = vector<Node>();
	destination = Vec3();
}

Pawn::Pawn(MeshObject* aMeshBody)
{
	meshBody = aMeshBody;
	speed = 1.0f;
	index = 0;
}

Pawn::Pawn(MeshObject* aMeshBody, float aSpeed)
{
	meshBody = aMeshBody;
	speed = aSpeed;
	index = 0;
}

Pawn::~Pawn()
{
}

void Pawn::Update(float deltaTime)
{
	Physics::SimpleNewtonMotion(*meshBody, deltaTime);
	Vec3 pos = meshBody->getPos();
	if (path.size() > 0) {
		if (pos.x >= destination.x - 0.1 && pos.x <= destination.x + 0.1) {
			if (pos.y >= destination.y - 0.1 && pos.y <= destination.y + 0.1) {
				if (index == path.size()) {
					destination = meshBody->getPos();
					index = 0;
					path.clear();
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
	meshBody->setVel(vel);
}

void Pawn::FollowPath(vector<Node> aPath)
{
	path = aPath;
	destination.x = path[0].x;
	destination.y = path[0].y;
}
