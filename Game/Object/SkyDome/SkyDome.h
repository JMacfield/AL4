#pragma once

#include "3D/Model.h"
#include "3D/WorldTransform.h"
#include "3D/ViewProjection.h"

class SkyDome {
public:
	void Initialize(Model* model);

	void Update();

	void Draw(const ViewProjection& viewPrijection);

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
};