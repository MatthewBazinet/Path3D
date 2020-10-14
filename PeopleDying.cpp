#include "PeopleDying.h"

#include "MMath.h"

PeopleDying::PeopleDying(Mesh* mesh_, Shader* shader_, Texture* texture_) :
	mesh(mesh_), shader(shader_), texture(texture_) {
	scale = 0.5f;
	angularVel = 540.0f;
	modelMatrixID = shader->getUniformID("modelMatrix");
	normalMatrixID = shader->getUniformID("normalMatrix");
}

PeopleDying::~PeopleDying() {}

bool PeopleDying::OnCreate() { return true; } /// Just a stub
void PeopleDying::OnDestroy() {}				  /// Just a stub
void PeopleDying::Update(float deltaTime_) {
	printf("%f\t%f\t%f\t%f\t%f\t%f\n", angle, angularVel, angularAcc, pos.x, vel.x, accel.x);
	Physics::SimpleNewtonMotion(*this, deltaTime_);
	scale = scale + deltaTime_/2;
	angularVel *= 0.99;
	modelMatrix = MMath::translate(pos) * MMath::rotate(angle, Vec3(0.0f, 1.0f, 0.0f)) * MMath::rotate(90, Vec3(1.0f, 0.0f, 0.0f)) * MMath::scale(scale, scale, scale);
}

void PeopleDying::Render() const {

	/// This is some fancy code.  Assigning a 4x4 matrix to a 3x3 matrix
	/// just steals the upper 3x3 of the 4x4 and assigns thoses values 
	/// to the 3x3.  
	Matrix3 normalMatrix = MMath::transpose(MMath::inverse(modelMatrix));

	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, modelMatrix);
	glUniformMatrix3fv(normalMatrixID, 1, GL_FALSE, normalMatrix);
	if (texture) {
		glBindTexture(GL_TEXTURE_2D, texture->getTextureID());
	}

	mesh->Render();

	/// Unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);
}

void PeopleDying::HandleEvents(const SDL_Event& event) {} /// Just a stub
