#pragma once

#include "3D/Model.h"
#include "3D/WorldTransform.h"
#include "3D/ViewProjection.h"

class Particle
{
public:
	void Initialize(Vector3 position);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	float RandomSpeed();

	bool GetIsAlive() { return isAlive_; };

	void SetIsAlive(bool isAlive) { isAlive_ = isAlive; };

private:
	Model* model_;

	WorldTransform worldTransformParticle_;

	Vector3 speed_;

	int particleTimer_ = 150;

	bool isAlive_ = false;
};