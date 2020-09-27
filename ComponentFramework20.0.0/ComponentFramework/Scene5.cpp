#include <glew.h>
#include <iostream>
#include "Debug.h"
#include "Scene5.h"
#include "Camera.h"
#include "DemoObject.h"
#include "ObjLoader.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "MMath.h"
#include "Debug.h"
#include "Physics.h"

Scene5::Scene5() : camera(nullptr), earth(nullptr), moon(nullptr), meshPtr(nullptr), shaderPtr(nullptr), texturePtr(nullptr) {
	Debug::Info("Created Scene5: ", __FILE__, __LINE__);
}

Scene5::~Scene5() {}

bool Scene5::OnCreate() {
	camera = new Camera();
	tb = new Trackball();
	lightSource = Vec3(0.0f, 0.0f, 10.0f);
	elapsedTime = 0.0f;
	//lightSource2 = Vec3(100.0f, 0.0f, -10.0f);
	//lightSources[0] = Vec3(-100.0f, 0.0f, -10.0f);
//	lightSources[1] = Vec3(100.0f, 0.0f, -10.0f);
	//lightSources[2] = Vec3(0.0f, 100.0f, -10.0f);
	//colors[0] = Vec4(0.1f, 0.1f, 0.6f, 0.0f);
	//colors[1] = Vec4(0.6f, 0.1f, 0.1f, 0.0f);
	//colors[2] = Vec4(0.1f, 0.6f, 0.1f, 0.0f);

	if (ObjLoader::loadOBJ("meshes/Sphere.obj") == false) {
		return false;
	}
	meshPtr = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);
	meshPeoplePtr = new Mesh(GL_POINTS, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);
	//shaderPtr = new Shader("multiPhongVert.glsl", "multiPhongFrag.glsl");
	shaderPtr = new Shader("3dtextureVert.glsl", "3dtextureFrag.glsl");
	texturePtr = new Texture();
	earthTxtr = new Texture();
	moonTxtr = new Texture();
	marsTxtr = new Texture();
	sunTexID = GLuint();
	if (meshPtr == nullptr || shaderPtr == nullptr || texturePtr == nullptr || earthTxtr == nullptr || moonTxtr == nullptr || marsTxtr == nullptr) {
		Debug::FatalError("Couldn't create game object assets", __FILE__, __LINE__);
		return false;
	}

	sunTexID = CreateNoise3D();

	if (earthTxtr->LoadImage("textures/earthclouds.jpg") == false) {
		Debug::FatalError("Couldn't load texture", __FILE__, __LINE__);
		return false;
	}
	if (moonTxtr->LoadImage("textures/moon.jpg") == false) {
		Debug::FatalError("Couldn't load texture", __FILE__, __LINE__);
		return false;
	}
	if (marsTxtr->LoadImage("textures/mars.jpg") == false) {
		Debug::FatalError("Couldn't load texture", __FILE__, __LINE__);
		return false;
	}

	earth = new PlanetaryObject(meshPtr, shaderPtr, earthTxtr);
	if (earth == nullptr) {
		Debug::FatalError("GameObject could not be created", __FILE__, __LINE__);
		return false;
	}
	people = new PeopleDying(meshPeoplePtr, shaderPtr, moonTxtr);
	if (people == nullptr) {
		Debug::FatalError("GameObject could not be created", __FILE__, __LINE__);
		return false;
	}
	/*moon = new PlanetaryObject(meshPtr, shaderPtr, moonTxtr);
	if (moon == nullptr) {
		Debug::FatalError("GameObject could not be created", __FILE__, __LINE__);
		return false;
	}*/
	earth->setPos(Vec3(0.0f, 0.0f, 0.0f));
	earth->setAngularVelocity(0);
	earth->setScale(2.0f);
	//	earth->setVel(Vec3(20.f,2.1f,1.0f));

		/*moon->setPos(Vec3(-50.0, 0.0, 0.0));
	moon->setAngularVelocity(10);
		moon->setScale(0.5f);*/


	if (ObjLoader::loadOBJ("meshes/Cube.obj") == false) {
		return false;
	}

	meshPtr = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);
	//shaderPtr = new Shader("multiPhongVert.glsl", "multiPhongFrag.glsl");
	skyboxShader = new Shader("skyboxVert.glsl", "skyboxFrag.glsl");
	texturePtr = new Texture();
	skybox = new Skybox(meshPtr, skyboxShader);
	camera->setTranslationMatix(MMath::translate(0, 0, -10));
	camera->setSkyBox(skybox);
	return true;
	camera->setSkyBox(skybox);
}

void Scene5::HandleEvents(const SDL_Event& sdlEvent) {
	tb->HandleEvents(sdlEvent);
}

void Scene5::Update(const float deltaTime) {
	earth->Update(deltaTime);

	camera->setRotationMatix(tb->getMatrix4());
	camera->OrbitUpdate(deltaTime);
	elapsedTime += deltaTime;
}

void Scene5::Render() const {
	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	camera->Render();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_3D);
	/// Draw your scene here
	GLuint program = earth->getShader()->getProgram();
	glUseProgram(program);

	// These pass the matricies and the light position to the GPU
	glUniformMatrix4fv(earth->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix());
	glUniformMatrix4fv(earth->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, camera->getViewMatrix());
	glUniform3fv(earth->getShader()->getUniformID("lightPos"), 1, lightSource);
	glUniform1f(earth->getShader()->getUniformID("time"), elapsedTime);


	glBindTexture(GL_TEXTURE_3D, sunTexID);
	earth->Render();
	glBindTexture(GL_TEXTURE_3D, 0);
	//people->Render();

	//moon->Render();

	glUseProgram(0);
}


void Scene5::OnDestroy() {
	if (camera) delete camera, camera = nullptr;
	if (meshPtr) delete meshPtr, meshPtr = nullptr;
	if (texturePtr) delete texturePtr, texturePtr = nullptr;
	if (shaderPtr) delete shaderPtr, shaderPtr = nullptr;
	if (earth) delete earth, earth = nullptr;
	if (moon) delete moon, moon = nullptr;
	if (tb) delete tb, tb = nullptr;
	DeleteNoise3D();
}
