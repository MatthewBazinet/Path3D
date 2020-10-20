#ifndef SCENE0_H
#define SCENE0_H
#include "Scene.h"
#include "Vector.h"
using namespace MATH;

/// Forward declarations 
union SDL_Event;
class Camera;
class DemoObject;
class Mesh;
class Shader;
class Texture;

class Scene0 : public Scene {
private:
	Camera *camera;
	unsigned int lightNum = 3;
	DemoObject *demoObject;
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