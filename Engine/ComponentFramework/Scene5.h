#ifndef SCENE5_H
#define SCENE5_H
#include "Scene.h"
#include "PlanetaryObject.h"
#include "PeopleDying.h"
#include "Camera.h"
#include "VMath.h"
#include "Noise.h"
#include "Trackball.h"
union SDL_Event;
class Scene5 : public Scene {
private:
	Camera* camera;
	Trackball* tb;
	Skybox* skybox;
	Shader* skyboxShader;
	unsigned int lightNum = 3;
	PlanetaryObject* earth;
	PlanetaryObject* moon;
	PeopleDying* people;
	Vec3 lightSources[3];
	Vec4 colors[3];
	Vec3 lightSource;
	Vec3 lightSource2;
	Mesh* meshPtr;
	Mesh* meshPeoplePtr;
	Shader* shaderPtr;
	Texture* texturePtr;
	Texture* earthTxtr;
	Texture* moonTxtr;
	Texture* marsTxtr;
	GLuint sunTexID;
	float elapsedTime;
public:
	explicit Scene5();
	virtual ~Scene5();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void HandleEvents(const SDL_Event& sdlEvent) override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
};


#endif // SCENE5_H