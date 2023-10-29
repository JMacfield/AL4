#pragma once
#include "3D/ViewProjection.h"
#include "3D/WorldTransform.h"
#include "EngineManager/Input/Input.h"

class FollowCamera {
public:
	void Initialize();

	void Update();
	void SetTarget(const WorldTransform* target);
	const ViewProjection& GetViewProjection() { return viewprojection_; }
	Vector3 GettargetWordPos();
private:
	ViewProjection viewprojection_;
	const WorldTransform* target_ = nullptr;
	Input* input_ = nullptr;

private:
	void Move();
	void Rotate();
};
