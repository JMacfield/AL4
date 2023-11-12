#pragma once

#include "3D/ViewProjection.h"
#include "3D/WorldTransform.h"

#include <3D/Model.h>
#include <vector>

enum ModelParts { kModelBody, kModelHead, kModelLarm, kModelRarm, kModelHammer };

class ICharacter {
public:
	virtual void Initialize(const std::vector<Model*>& models);

	virtual void Update();

	virtual void Draw(const ViewProjection& view);

protected:
	std::vector<Model*> models_;
	WorldTransform worldTransform_;
};

