#include "Camera/FollowCamera.h"
#include "MyMath/MyMath.h"
#include "EngineBase/ImGuiManager.h"

void FollowCamera::Initialize() {
	viewprojection_.Initialize();
	input_ = Input::GetInstance();

	GlobalVariables* globalVariables{};
	globalVariables = GlobalVariables::GetInstance();
	const char* groupName = "Camera";

	GlobalVariables::GetInstance()->CreateGroup(groupName);
	globalVariables->AddItem(groupName, "Delay", delay_);
	ApplyGlobalVariables();
}

void FollowCamera::Update() {
	Move();
	Rotate();
	ApplyGlobalVariables();

	viewprojection_.UpdateViewMatrix();
	viewprojection_.TransferMatrix();
}

void FollowCamera::SetTarget(const WorldTransform* target) {
	target_ = target;
}

Vector3 FollowCamera::GetTargetWorldPosition() {
	Vector3 result;

	result.x = target_->matWorld_.m[3][0];
	result.y = target_->matWorld_.m[3][1];
	result.z = target_->matWorld_.m[3][2];
	
	return result;
}

void FollowCamera::Move() {
	if (target_) {

		Vector3 offset = { 0.0f, 2.0f, -10.0f };

		Matrix4x4 rotateMatrix = MakeRotateMatrix(viewprojection_.rotation_);

		offset = TransformNormal(offset, rotateMatrix);
		Vector3 worldTranslate = { target_->matWorld_.m[3][0],target_->matWorld_.m[3][1],target_->matWorld_.m[3][2] };
		
		interTarget_ = Lerp(delay_, worldTranslate, interTarget_);
		viewprojection_.translation_ = Add(GetTargetWorldPosition(), offset);
	}
}

void FollowCamera::Rotate() {
	XINPUT_STATE joystate;

	if (Input::GetInstance()->GetJoystickState(0, joystate)) {
		const float kRotateSpeed = 0.02f;
		viewprojection_.rotation_.y += (float)joystate.Gamepad.sThumbRX / SHRT_MAX * kRotateSpeed;
	}
}

void FollowCamera::ApplyGlobalVariables() {
	GlobalVariables* globalVariables = GlobalVariables::GetInstance();

	const char* groupName = "Camera";
	delay_ = globalVariables->GetFloatValue(groupName, "Delay");

	if (delay_ >= 1.0f) {
		delay_ = 0.9999999f;
	}
	if (delay_ <= 0.0f) {
		delay_ = 0.0f;
	}
}

void FollowCamera::Reset() {
	if (target_) {
		Vector3 worldTranslate = { target_->matWorld_.m[3][0],target_->matWorld_.m[3][1],target_->matWorld_.m[3][2] };
		interTarget_ = worldTranslate;
		viewprojection_.rotation_.y = target_->rotation_.y;
	}

	destinationAngleY_ = viewprojection_.rotation_.y;
}
