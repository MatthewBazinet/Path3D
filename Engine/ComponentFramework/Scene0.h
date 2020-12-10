#ifndef SCENE0_H
#define SCENE0_H
#include "Scene.h"
#include "Vector.h"
using namespace MATH;

/// Forward declarations 
union SDL_Event;
class Camera;
class MeshObject;
class Mesh;
class Shader;
class Texture;
class Enemy;

class Scene0 : public Scene {
private:
	Camera *camera;
	unsigned int lightNum = 3;
	MeshObject *demoObject;
	Enemy *enemy1;
	Vec3 lightSources[3];
	Vec4 colors[3];
	Vec3 lightSource;
	Vec3 lightSource2;
	Mesh *meshPtr;
	Shader *shaderPtr;
	Texture *texturePtr;
public:
	explicit Scene0();
	virtual ~Scene0();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event &sdlEvent) override;
};


#endif // SCENE0_H