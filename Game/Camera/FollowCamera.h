#pragma once

#include "3D/ViewProjection.h"
#include "3D/WorldTransform.h"
#include "EngineManager/Input/Input.h"
#include "EngineManager/GlobalVariables/GlobalVariables.h"

class FollowCamera {
public:
	void Initialize();
	void Update();
	
	void SetTarget(const WorldTransform* target);
	void Reset();

	const ViewProjection& GetViewProjection() { return viewprojection_; }
	Vector3 GetTargetWorldPosition();

private:
	ViewProjection viewprojection_;
	const WorldTransform* target_ = nullptr;
	Input* input_ = nullptr;
	Vector3 interTarget_ = {};

	float destinationAngleY_ = 0.0f;
	float delay_;

private:
	void Move();
	void Rotate();
	void ApplyGlobalVariables();
};