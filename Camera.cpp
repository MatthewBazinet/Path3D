#include "Camera.h"
#include "MMath.h"

bool Camera::OnCreate()
{
	return false;
}

void Camera::OnDestroy()
{
}

void Camera::Update(const float deltaTime)
{
	view = rotate * translate;
}

void Camera::OrbitUpdate(const float deltaTime)
{
	view = translate * rotate;
}

void Camera::Render() const
{
	if (skybox) {
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		glUseProgram(skybox->getShader()->getProgram());

		/// These pass the matricies and the light position to the GPU
		glUniformMatrix4fv(skybox->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, projection);
		glUniformMatrix4fv(skybox->getShader()->getUniformID("cameraRotationMatrix"), 1, GL_FALSE, rotate);
		skybox->Render();
		glUseProgram(0);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
	}
}

void Camera::HandleEvents(const SDL_Event& event)
{
}


Camera::Camera() {
	setProjectionMatrix(MMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 100.0f));
	//setViewMatrix(MMath::lookAt(Vec3(0.0, 0.0, 10.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f)));

	rotate = MMath::rotate(0.0f,0.0f,1.0f,0.0f);
	translate = MMath::translate(0.0f,0.0f,-10.0f);
	view = rotate * translate;
}

Camera::~Camera() {}

