#include "PlayerController.h"
#include<glew.h>
#include<iostream>
#include<SDL_scancode.h>
#include<SDL_events.h>
#include<SDL.h>
#include "MMath.h"
#include "Physics.h"

PlayerController::PlayerController(MeshObject* meshBody)
{
	this->meshBody = meshBody;
	
}

PlayerController::~PlayerController()
{
	delete meshBody;
	meshBody = nullptr;
	
}

void PlayerController::HandleEvents(const SDL_Event& event)
{

	switch (event.key.keysym.scancode) {
	case SDL_SCANCODE_W:

		//move player forward
		meshBody->setVel(Vec3(0.0f, 0.0f, 1.0f));
		//std::cout << "you clicked w on the keyboard" << std::endl;
		break;
	case SDL_SCANCODE_A:
		//move player left
		meshBody->setVel(Vec3(-1.0f, 0.0f, 0.0f));
		break;
	case SDL_SCANCODE_S:
		//move player backward
		meshBody->setVel(Vec3(0.0f, 0.0f, -1.0f));
		break;
	case SDL_SCANCODE_D:
		//move player right
		meshBody->setVel(Vec3(1.0f, 0.0f, 0.0f));
		break;
	}
	if (event.type == SDL_KEYUP) {
		meshBody->setVel(Vec3(0));
	}



}

void PlayerController::Update(float deltaTime)
{
	Physics::SimpleNewtonMotion(*meshBody, deltaTime);
	meshBody->Update(deltaTime);
}
