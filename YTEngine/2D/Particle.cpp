#include "Particle.h"

void Particle::Initialize(Model* model, Vector3 position)
{
	assert(model);
	model_ = model;

	isAlive_ = true;

	worldTransformParticle_.Initialize();

	worldTransformParticle_.translation_ = position;

	speed_.x = RandomSpeed();
	speed_.y = RandomSpeed();
	speed_.z = RandomSpeed();
}

void Particle::Update()
{
	if (isAlive_ == true)
	{
		particleTimer_--;
		worldTransformParticle_.translation_.x += speed_.x;
		worldTransformParticle_.translation_.y += speed_.y;
		worldTransformParticle_.translation_.z += speed_.z;
		worldTransformParticle_.rotation_.x += speed_.x;
		worldTransformParticle_.rotation_.y += speed_.y;
		/*worldTransformParticle_.scale_.x -= 0.1f;
		worldTransformParticle_.scale_.y -= 0.1f;
		worldTransformParticle_.scale_.z -= 0.1f;*/
		worldTransformParticle_.UpdateMatrix(RotationType::Euler);
	}

	if (particleTimer_ < 0)
	{
		isAlive_ = false;
	}

	ImGui::Begin("Particle");

	ImGui::End();
}

void Particle::Draw(const ViewProjection& viewProjection)
{
	if (isAlive_ == true)
	{
		model_->Draw(worldTransformParticle_, viewProjection);
	}
}

float Particle::RandomSpeed()
{
	float min = -0.4f;
	float max = 0.4f;

	return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}