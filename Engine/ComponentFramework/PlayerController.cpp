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

void PlayerController::HandleEvents()
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
			event.key.keysym.sym = true;
		}
		if (event.type == SDL_KEYUP)
		{
			event.key.keysym.sym = false;
		}
	}

	if (SDLK_w)
	{
		//move player forward
		meshBody->setVel(Vec3(0.0f, 1.0f, 0.0f));
		//std::cout << "you clicked w on the keyboard" << std::endl;
		if (SDLK_LSHIFT)
		{
			//make player sprint
			meshBody->setVel(Vec3(0.0f, 2.0f, 0.0f));
		}
	}
	if (SDLK_a)
	{
		//move player left
		meshBody->setVel(Vec3(-1.0f, 0.0f, 0.0f));
		if (SDLK_LSHIFT)
		{
			//make player sprint
			meshBody->setVel(Vec3(-2.0f, 0.0f, 0.0f));
		}
	}
	if (SDLK_s)
	{
		//move player backward
		meshBody->setVel(Vec3(0.0f, -1.0f, 0.0f));
		if (SDLK_LSHIFT)
		{
			//make player sprint
			meshBody->setVel(Vec3(0.0f, -2.0f, 0.0f));
		}
	}
	if (SDLK_d)
	{
		//move player right
		meshBody->setVel(Vec3(1.0f, 0.0f, 0.0f));

		if (SDLK_LSHIFT)
		{
			//make player sprint
			meshBody->setVel(Vec3(2.0f, 0.0f, 0.0f));
		}
	}
	if (SDLK_c)
	{
		//make player crouch
	}

}

void PlayerController::Update(float deltaTime)
{
	Physics::SimpleNewtonMotion(*meshBody, deltaTime);
}
