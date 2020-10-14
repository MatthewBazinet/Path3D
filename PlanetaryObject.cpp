#include "PlanetaryObject.h"

#include "MMath.h"

PlanetaryObject::PlanetaryObject(Mesh* mesh_, Shader* shader_, Texture* texture_) :
	mesh(mesh_), shader(shader_), texture(texture_) {
	modelMatrixID = shader->getUniformID("modelMatrix");
	normalMatrixID = shader->getUniformID("normalMatrix");
	delete satelite;
	satelite = nullptr;
}

PlanetaryObject::PlanetaryObject(Mesh* mesh_, Shader* shader_, Texture* texture_, Texture* textureSat_) :
	mesh(mesh_), shader(shader_), texture(texture_) {
	modelMatrixID = shader->getUniformID("modelMatrix");
	normalMatrixID = shader->getUniformID("normalMatrix");
	satelite = new PlanetaryObject(mesh, shader, textureSat_);
	satelite->setPos(Vec3(-2.5f, 0.0f, 0.0f));
	satelite->setAngularVelocity(1);
	satelite->setScale(scale / 2);
}

PlanetaryObject::PlanetaryObject(Mesh* mesh_, Shader* shader_, Texture* texture_, Texture* textureSat_, Texture* textureSatSat_):
	mesh(mesh_), shader(shader_), texture(texture_) {
	scale = 1.0f;
		modelMatrixID = shader->getUniformID("modelMatrix");
		normalMatrixID = shader->getUniformID("normalMatrix");
		satelite = new PlanetaryObject(mesh, shader, textureSat_, textureSatSat_);
		satelite->setPos(Vec3(-5.0f, 0.0f, 0.0f));
		satelite->setAngularVelocity(1);
		satelite->setScale(scale / 2);
}

PlanetaryObject::~PlanetaryObject() {}

bool PlanetaryObject::OnCreate() { return true; } /// Just a stub
void PlanetaryObject::OnDestroy() {}				  /// Just a stub
void PlanetaryObject::Update(float deltaTime_) {
	printf("%f\t%f\t%f\t%f\t%f\t%f\n", angle, angularVel, angularAcc, pos.x, vel.x, accel.x);
	Physics::SimpleNewtonMotion(*this, deltaTime_);
	modelMatrix = MMath::translate(pos) * MMath::rotate(angle, Vec3(0.0f, 1.0f, 0.0f)) * MMath::rotate(-90, Vec3(1.0f, 0.0f, 0.0f)) * MMath::scale(scale,scale,scale);
	
	if (satelite) {
		satelite->setAngularVelocity(angularVel/27);
		satelite->setPos(Vec3(5, 0, 0));
		satelite->setScale(scale/4);
		satelite->MoonUpdate(deltaTime_, pos);
	}
}
void PlanetaryObject::MoonUpdate(float deltaTime_, Vec3 planetPos) {
	printf("%f\t%f\t%f\t%f\t%f\t%f\n", angle, angularVel, angularAcc, pos.x, vel.x, accel.x);
	Physics::SimpleNewtonMotion(*this, deltaTime_);
	modelMatrix = MMath::translate(planetPos) * MMath::rotate(angle, Vec3(0.0f,1.0f,0.0f)) * MMath::translate(pos) * MMath::rotate(-90,Vec3(0,1,0)) * MMath::scale(scale, scale, scale);
	if (satelite) {
		satelite->setAngularVelocity(angularVel/2);
		satelite->setPos(Vec3(1.5,0,0));
		satelite->setScale(scale/2);
		satelite->MoonUpdate(deltaTime_, planetPos + MMath::rotate(angle, Vec3(0.0f, 1.0f, 0.0f)) * pos);
	}
}

void PlanetaryObject::Render() const {
	if (satelite) {
		satelite->Render();
	}
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

void PlanetaryObject::HandleEvents(const SDL_Event& event) {} /// Just a stub

