#include "Pawn.h"
#include "Physics.h"
#include "MMath.h"
#include "Pathfinding.h"

Pawn::Pawn()
{
	meshBody = nullptr;
	speed = 1.0f;
	index = 0;
	//vector<Node> path = vector<Node>();
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

		if (pos.x >= destination.x - 0.5 && pos.x <= destination.x + 0.5) {
			if (pos.z >= destination.z - 0.5 && pos.z <= destination.z + 0.5) {

				index++;
				if (index >= path.size()) {
					destination = meshBody->getPos();
					index = 0;
					path.clear();
					direction = Vec3(0);
				}
				else {
					destination.x = path[index].x;
					destination.z = path[index].z;
					direction = VMath::normalize(destination - pos);
				}
			}
		}
		MoveInDir(direction);
	}
}

void Pawn::Render()
{
	meshBody->setModelMatrix(MMath::translate(meshBody->getPos()) * MMath::rotate(meshBody->getAngle(), Vec3(0, 1, 0)) * MMath::scale(meshBody->getScale()));
	meshBody->Render();
}



void Pawn::FindPath(GridWithWeights grid, GridVec targetPosition)
{
	GridVec start{ meshBody->getPos().x, meshBody->getPos().y };
	std::unordered_map<GridVec, GridVec> came_from;
	std::unordered_map<GridVec, double> cost_so_far;
	Pathfinding::a_star_search(grid, start, targetPosition, came_from, cost_so_far);
	std::vector<GridVec> path = Pathfinding::reconstruct_path(start, targetPosition, came_from);
	std::vector<Vec3> vecPath;
	for (unsigned int i = 0; i < path.size(); i++) {
		vecPath.push_back(Vec3(path[i].x, 0, path[i].y));
	}

	FollowPath(vecPath);
}


void Pawn::MoveInDir(Vec3 dir)
{
	Vec3 vel = dir * speed;
	meshBody->setVel(vel);
}

void Pawn::FollowPath(vector<Vec3> aPath)
{
	path = aPath;
	destination.x = path[0].x;
	destination.z = path[0].z;
}

Vec3 Pawn::GetGridVec()
{
	Vec3 location;
	location.x = round(meshBody->getPos().x);
	location.y = round(meshBody->getPos().z);

	return location;

}


