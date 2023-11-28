#include "ICharacter.h"

void ICharacter::Initialize(const std::vector<Model*>& models, Vector3 pos) {
	models_ = models;
	worldTransform_.translation_ = pos;
	worldTransform_.Initialize();
}

void ICharacter::Update() {
	worldTransform_.UpdateMatrix();
}

void ICharacter::Draw(const ViewProjection& view) {
	for (Model* model : models_) {
		model->Draw(worldTransform_, view);
	}
}