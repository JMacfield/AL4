#pragma once

#include "3D/ViewProjection.h"
#include "3D/WorldTransform.h"
#include "EngineManager/Input/Input.h"
#include "EngineManager/GlobalVariables/GlobalVariables.h"

class LookOn;

class FollowCamera {
public:
	void Initialize();
	void Update();

	void SetTarget(const WorldTransform* target);
	const ViewProjection& GetViewProjection() { return viewProjection_; }
	
	Vector3 GetTargetWordPos();
	
	void Reset();
	void SetLockOn(const LookOn* lockon) { lockOn_ = lockon; }
	void DeletelockOn() { lockOn_ = nullptr; }

private:
	ViewProjection viewProjection_;

	const WorldTransform* target_ = nullptr;
	
	Input* input_ = nullptr;
	Vector3 interTarget_ = {};
	
	const LookOn* lockOn_ = nullptr;
	
	float destinationAngleY_ = 0.0f;
	float delay_;
	
	Vector3 rotate;
	
	bool isChange;
	
	Vector3 changeRotate;
	Quaternion quaternion_;

private:
	void Move();
	void Rotate();
	void ApplyGlobalVariables();
	void Change();
};