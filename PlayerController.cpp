#include "PlayerController.h"

PlayerController::PlayerController(PhysicsObject* body)
{
}

PlayerController::~PlayerController()
{
	delete body;
	body = nullptr;
	
}

void PlayerController::Update()
{
	
	if (false) { 
		MoveInDir(Vec3(1,0,0), speed);
	}
}
