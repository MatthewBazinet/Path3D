#ifndef CAMERA_H
#define CAMERA_H
#include "Vector.h"
#include "Matrix.h"
#include "Skybox.h"
#include "GameObject.h"

using namespace MATH;
class Camera : public GameObject{
private:
	Matrix4 projection;
	Matrix4 view;
	Matrix4 translate;
	Matrix4 rotate;
	Skybox* skybox;
public:
	inline Matrix4 getProjectionMatrix() const { return projection; }
	inline Matrix4 getViewMatrix() const { return view; }
	inline void setProjectionMatrix(Matrix4 projection_){ projection = projection_; }
	inline void setViewMatrix(Matrix4 view_) { view = view_;  }
	inline void setSkyBox(Skybox* skybox_) { skybox = skybox_; };
	inline void setRotationMatix(Matrix4 rotate_) { rotate = rotate_; };
	inline void setTranslationMatix(Matrix4 translate_) { translate = translate_; };
	bool OnCreate();
	void OnDestroy();
	void Update(const float deltaTime);
	void OrbitUpdate(const float deltaTime);
	void Render() const;
	void HandleEvents(const SDL_Event& event);
	Camera();
	~Camera();
};

#endif



