#include <glew.h>
#include <iostream>
#include<SDL_events.h>
#include "Debug.h"
#include "Scene0.h"
#include "Camera.h"
#include "MeshObject.h"
#include "ObjLoader.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "MMath.h"
#include "Debug.h"
#include "Physics.h"
#include "PlayerController.h"
#include "Pawn.h"
#include "Pathfinding.h"



Scene0::Scene0(): camera(nullptr), plane(nullptr), wallOne(nullptr), wallTwo(nullptr), wallThree(nullptr), wallFour(nullptr), wallFive(nullptr), wallSix(nullptr), wallSeven(nullptr), meshPtr(nullptr),shaderPtr(nullptr),texturePtr(nullptr),playerMesh(nullptr),enemy1(nullptr) {
	Debug::Info("Created Scene0: ", __FILE__, __LINE__);
}

Scene0::~Scene0() {}

bool Scene0::OnCreate() {
	camera = new Camera();
	camera->setRotationMatix(MMath::rotate(-90, Vec3(1, 0, 0)));
	camera->setTranslationMatix(MMath::translate(0, 30, 0));

	lightSource = Vec3(-100.0f, 0.0f, -10.0f);
	lightSource2 = Vec3(100.0f, 0.0f, -10.0f);
	lightSources[0] = Vec3(-100.0f, 0.0f, -10.0f);
	lightSources[1] = Vec3(100.0f, 0.0f, -10.0f);
	lightSources[2] = Vec3(0.0f, 100.0f, -10.0f);
	colors[0] = Vec4(0.1f, 0.1f, 0.6f,0.0f);
	colors[1] = Vec4(0.6f, 0.1f, 0.1f,0.0f);
	colors[2] = Vec4(0.1f, 0.6f, 0.1f,0.0f);

	if (ObjLoader::loadOBJ("meshes/Cube.obj") == false) {
		return false;
	}
	meshPtr = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);

	if (ObjLoader::loadOBJ("meshes/Sphere.obj") == false) {
		return false;
	}

	playerMesh = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);

	shaderPtr = new Shader("multiPhongVert.glsl", "multiPhongFrag.glsl");
	//shaderPtr = new Shader("textureVert.glsl", "textureFrag.glsl");
	texturePtr = new Texture();
	if (meshPtr == nullptr|| shaderPtr == nullptr || texturePtr == nullptr) {
		Debug::FatalError("Couldn't create game object assets", __FILE__, __LINE__);
		return false;
	}


	if (texturePtr->LoadImage("textures/mario_main.png") == false) {
		Debug::FatalError("Couldn't load texture", __FILE__, __LINE__);
		return false;
	}
	player = new PlayerController(new MeshObject(playerMesh, shaderPtr, texturePtr));
	player->meshBody->setPos(Vec3(2, 1, 0));
	player->meshBody->setScale(Vec3(0.5, 0.5, 0.5));

	if (player == nullptr) {
		Debug::FatalError("GameObject could not be created", __FILE__, __LINE__);
		return false;
	}
	enemy1 = new Pawn(new MeshObject(meshPtr, shaderPtr, texturePtr));
	enemy1->meshBody->setPos(Vec3(5, 1, 0));
	enemy1->meshBody->setScale(Vec3(0.25, 0.25, 0.25));

	if (enemy1 == nullptr) {
		Debug::FatalError("GameObject could not be created", __FILE__, __LINE__);
		return false;
	}


	//Sets plane
	plane = new MeshObject(meshPtr, shaderPtr, texturePtr);
	if (plane == nullptr) {
		Debug::FatalError("GameObject could not be created", __FILE__, __LINE__);
		return false;
	}
	plane->setPos(Vec3(5.0f, 2.5f, 5.0f));
	plane->setScale(Vec3(6.0f,0.5f,6.0f));
	plane->Update(1.0f);

	//Sets first wall location and size
	wallOne = new MeshObject(meshPtr, shaderPtr, texturePtr);
	if (wallOne == nullptr) {
		Debug::FatalError("GameObject could not be created", __FILE__, __LINE__);
		return false;
	}
	wallOne->setPos(Vec3(0.75f, 1.0f, 5.0f));
	wallOne->setScale(Vec3(1.5f, 0.5f, 0.5f));
	wallOne->Update(1.0f);


	//Sets second wall location and size
	wallTwo = new MeshObject(meshPtr, shaderPtr, texturePtr);
	if (wallTwo == nullptr) {
		Debug::FatalError("GameObject could not be created", __FILE__, __LINE__);
		return false;
	}
	wallTwo->setPos(Vec3(10.0f-0.75f, 1.0f, 5.0f));
	wallTwo->setScale(Vec3(1.5f, 0.5f, 0.5f));
	wallTwo->Update(1.0f);


	//Sets third wall location and size
	wallThree = new MeshObject(meshPtr, shaderPtr, texturePtr);
	if (wallThree == nullptr) {
		Debug::FatalError("GameObject could not be created", __FILE__, __LINE__);
		return false;
	}
	wallThree->setPos(Vec3(0.0, 1.0, 10.0));
	wallThree->setScale(Vec3(0.5f, 0.5f, 0.5f));
	wallThree->Update(1.0f);

	//Sets fourth wall location and size
	wallFour = new MeshObject(meshPtr, shaderPtr, texturePtr);
	if (wallFour == nullptr) {
		Debug::FatalError("GameObject could not be created", __FILE__, __LINE__);
		return false;
	}
	wallFour->setPos(Vec3(10.0, 1.0, 10.0));
	wallFour->setScale(Vec3(0.5f, 0.5f, 0.5f));
	wallFour->Update(1.0f);

	//Sets fifth wall location and size
	wallFive = new MeshObject(meshPtr, shaderPtr, texturePtr);
	if (wallFive == nullptr) {
		Debug::FatalError("GameObject could not be created", __FILE__, __LINE__);
		return false;
	}
	wallFive->setPos(Vec3(10.0, 1.0, 0.0));
	wallFive->setScale(Vec3(0.5f, 0.5f, 0.5f));
	wallFive->Update(1.0f);

	//Sets sixth wall location and size
	wallSix = new MeshObject(meshPtr, shaderPtr, texturePtr);
	if (wallSix == nullptr) {
		Debug::FatalError("GameObject could not be created", __FILE__, __LINE__);
		return false;
	}
	wallSix->setPos(Vec3(0.0, 1.0, 0.0));
	wallSix->setScale(Vec3(0.5f, 0.5f, 0.5f));
	wallSix->Update(1.0f);

	//Sets seventh wall location and size
	wallSeven = new MeshObject(meshPtr, shaderPtr, texturePtr);
	if (wallSeven == nullptr) {
		Debug::FatalError("GameObject could not be created", __FILE__, __LINE__);
		return false;
	}
	wallSeven->setPos(Vec3(3.8, 10.0, 1.5));
	wallSeven->setScale(Vec3(0.5f, 0.5f, 0.5f));
	wallSeven->Update(1.0f);


	GridWithWeights grid = GridWithWeights(10, 10);
	grid.addRect(0, 5, 3, 6);
	grid.addRect(7, 5, 10, 6);
	grid.addRect(0, 0, 1, 1);
	grid.addRect(9, 9, 10, 10);
	grid.addRect(0,9,1,10);
	grid.addRect(9,0,10,1);

	Vec3 pos = enemy1->GetGridVec();
	Vec3 targetPosition = player->GetGridVec();
	GridVec start{ pos.x, pos.y }, goal{ targetPosition.x, targetPosition.y };
	std::unordered_map<GridVec, GridVec> cameFrom;
	std::unordered_map<GridVec, double> costSoFar;
	Pathfinding::aStarSearch(grid, start, goal, cameFrom, costSoFar);
	std::vector<GridVec> path = Pathfinding::makePath(start, goal, cameFrom);
	std::vector<Vec3> vecPath;
	for (unsigned int i = 0; i < path.size(); i++) {
		vecPath.push_back(Vec3(path[i].x,0, path[i].y));
	}

	enemy1->FollowPath(vecPath);

	return true;
}

void Scene0::HandleEvents(const SDL_Event &sdlEvent) {
	player->HandleEvents(sdlEvent);
	if (sdlEvent.type == SDL_KEYDOWN) {
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_P) {
			GridWithWeights grid = GridWithWeights(10, 10);
			grid.addRect(0, 5, 3, 6);
			grid.addRect(7, 5, 10, 6);
			grid.addRect(0, 0, 1, 1);
			grid.addRect(9, 9, 10, 10);
			grid.addRect(0, 9, 1, 10);
			grid.addRect(9, 0, 10, 1);

			Vec3 targetPosition = player->GetGridVec();
			targetPosition.print();
			GridVec goal{ targetPosition.x, targetPosition.y };
			enemy1->FindPath(grid, goal);
		}
	}
}

void Scene0::Update(const float deltaTime) {
	enemy1->Update(deltaTime);

	player->Update(deltaTime);
	camera->setTranslationMatix(MMath::translate(Vec3(-player->meshBody->getPos().x, player->meshBody->getPos().y + 30.0f, -player->meshBody->getPos().z)));
	camera->Update(deltaTime);
}

void Scene0::Render() const {
	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	/// Draw your scene here
	GLuint program = plane->getShader()->getProgram();
	glUseProgram(program);

	/// These pass the matricies and the light position to the GPU
	glUniformMatrix4fv(plane->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix());
	glUniformMatrix4fv(plane->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, camera->getViewMatrix());
	glUniform3fv(plane->getShader()->getUniformID("lightPos[0]"), 3, *lightSources);
	glUniform4fv(plane->getShader()->getUniformID("colors[0]"), 3, *colors);
	plane->Render();

	//wall one
	program = wallOne->getShader()->getProgram();
	glUseProgram(program);

	/// These pass the matricies and the light position to the GPU
	glUniformMatrix4fv(wallOne->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix());
	glUniformMatrix4fv(wallOne->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, camera->getViewMatrix());
	glUniform3fv(wallOne->getShader()->getUniformID("lightPos[0]"), 3, *lightSources);
	glUniform4fv(wallOne->getShader()->getUniformID("colors[0]"), 3, *colors);
	wallOne->Render();

	//wall two
	program = wallTwo->getShader()->getProgram();
	glUseProgram(program);

	/// These pass the matricies and the light position to the GPU
	glUniformMatrix4fv(wallTwo->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix());
	glUniformMatrix4fv(wallTwo->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, camera->getViewMatrix());
	glUniform3fv(wallTwo->getShader()->getUniformID("lightPos[0]"), 3, *lightSources);
	glUniform4fv(wallTwo->getShader()->getUniformID("colors[0]"), 3, *colors);
	wallTwo->Render();

	//wall three
	program = wallThree->getShader()->getProgram();
	glUseProgram(program);

	/// These pass the matricies and the light position to the GPU
	glUniformMatrix4fv(wallThree->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix());
	glUniformMatrix4fv(wallThree->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, camera->getViewMatrix());
	glUniform3fv(wallThree->getShader()->getUniformID("lightPos[0]"), 3, *lightSources);
	glUniform4fv(wallThree->getShader()->getUniformID("colors[0]"), 3, *colors);
	wallThree->Render();

	//wall four
	program = wallFour->getShader()->getProgram();
	glUseProgram(program);

	/// These pass the matricies and the light position to the GPU
	glUniformMatrix4fv(wallFour->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix());
	glUniformMatrix4fv(wallFour->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, camera->getViewMatrix());
	glUniform3fv(wallFour->getShader()->getUniformID("lightPos[0]"), 3, *lightSources);
	glUniform4fv(wallFour->getShader()->getUniformID("colors[0]"), 3, *colors);
	wallFour->Render();

	//wall five
	program = wallFive->getShader()->getProgram();
	glUseProgram(program);

	/// These pass the matricies and the light position to the GPU
	glUniformMatrix4fv(wallFive->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix());
	glUniformMatrix4fv(wallFive->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, camera->getViewMatrix());
	glUniform3fv(wallFive->getShader()->getUniformID("lightPos[0]"), 3, *lightSources);
	glUniform4fv(wallFive->getShader()->getUniformID("colors[0]"), 3, *colors);
	wallFive->Render();

	//wall six
	program = wallSix->getShader()->getProgram();
	glUseProgram(program);

	/// These pass the matricies and the light position to the GPU
	glUniformMatrix4fv(wallSix->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix());
	glUniformMatrix4fv(wallSix->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, camera->getViewMatrix());
	glUniform3fv(wallSix->getShader()->getUniformID("lightPos[0]"), 3, *lightSources);
	glUniform4fv(wallSix->getShader()->getUniformID("colors[0]"), 3, *colors);
	wallSix->Render();

	//wall seven
	program = wallSeven->getShader()->getProgram();
	glUseProgram(program);

	/// These pass the matricies and the light position to the GPU
	glUniformMatrix4fv(wallSeven->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix());
	glUniformMatrix4fv(wallSeven->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, camera->getViewMatrix());
	glUniform3fv(wallSeven->getShader()->getUniformID("lightPos[0]"), 3, *lightSources);
	glUniform4fv(wallSeven->getShader()->getUniformID("colors[0]"), 3, *colors);
	wallSeven->Render();

	program = player->meshBody->getShader()->getProgram();
	glUseProgram(program);

	/// These pass the matricies and the light position to the GPU
	glUniformMatrix4fv(player->meshBody->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix());
	glUniformMatrix4fv(player->meshBody->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, camera->getViewMatrix());
	glUniform3fv(player->meshBody->getShader()->getUniformID("lightPos[0]"), 3, *lightSources);
	glUniform4fv(player->meshBody->getShader()->getUniformID("colors[0]"), 3, *colors);
	player->Render();

	program = enemy1->meshBody->getShader()->getProgram();
	glUseProgram(program);

	/// These pass the matricies and the light position to the GPU
	glUniformMatrix4fv(enemy1->meshBody->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix());
	glUniformMatrix4fv(enemy1->meshBody->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, camera->getViewMatrix());
	glUniform3fv(enemy1->meshBody->getShader()->getUniformID("lightPos[0]"), 3, *lightSources);
	glUniform4fv(enemy1->meshBody->getShader()->getUniformID("colors[0]"), 3, *colors);
	enemy1->Render();

	glUseProgram(0);
}


void Scene0::OnDestroy() {
	if (camera) delete camera, camera = nullptr;
	if (meshPtr) delete meshPtr, meshPtr = nullptr;
	if (texturePtr) delete texturePtr, texturePtr = nullptr;
	if (shaderPtr) delete shaderPtr, shaderPtr = nullptr;
	if (plane) delete plane, plane = nullptr;

	if (wallOne) delete wallOne, wallOne = nullptr;
	if (wallTwo) delete wallTwo, wallTwo = nullptr;
	if (wallThree) delete wallThree, wallThree = nullptr; 
	if (wallFour) delete wallFour, wallFour = nullptr;
	if (wallFive) delete wallFive, wallFive = nullptr;
	if (wallSix) delete wallSix, wallSix = nullptr;
	if (wallSeven) delete wallSeven, wallSeven = nullptr;

	if (playerMesh) delete playerMesh, playerMesh = nullptr;
	if (player) delete player, player = nullptr;
	if (enemy1) delete enemy1, enemy1 = nullptr;

}
