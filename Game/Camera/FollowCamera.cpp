#include "Camera/FollowCamera.h"
#include "MyMath/MyMath.h"
#include "EngineBase/ImGuiManager.h"
#include "Camera/LockOn.h"

void FollowCamera::Initialize() {
	viewProjection_.Initialize();
	input_ = Input::GetInstance();

	quaternion_ = CreateQuaternion(0.0f, { 0.0f,1.0f,0.0f });
	quaternion_ = Normalize(quaternion_);
	
	GlobalVariables* globalVariables{};
	globalVariables = GlobalVariables::GetInstance();
	const char* groupName = "Camera";
	
	GlobalVariables::GetInstance()->CreateGroup(groupName);
	globalVariables->AddItem(groupName, "delay", delay_);
	ApplyGlobalVariables();
}

void FollowCamera::Update() {
	ApplyGlobalVariables();
	Move();

	if (lockOn_ && lockOn_->Existtarget()) {
		Vector3 LockOntrans = lockOn_->GetTargetPos();
		Vector3 sub = LockOntrans - GetTargetWordPos();

		viewProjection_.rotation_.y = Angle({ 0.0f,0.0f,1.0f }, sub);//Lerp(delay_, rotate, viewprojection_.rotation_);
	}
	else {
		Rotate();
	}

	rotate = { viewProjection_.rotation_.x,rotate.y,viewProjection_.rotation_.z };
	
	viewProjection_.UpdateViewMatrix();
	viewProjection_.TransferMatrix();
}

void FollowCamera::SetTarget(const WorldTransform* target) {
	target_ = target;
}

Vector3 FollowCamera::GetTargetWordPos() {
	Vector3 result;
	result.x = target_->matWorld_.m[3][0];
	result.y = target_->matWorld_.m[3][1];
	result.z = target_->matWorld_.m[3][2];
	return result;
}

void FollowCamera::Move() {
	if (target_) {
		Vector3 offset = { 0.0f, 3.5f, -10.0f };

		Matrix4x4 rotateMatrix = MakeRotateMatrix(viewProjection_.rotation_);
		//Matrix4x4 rotateMatrix = quate(viewprojection_.rotation_);
		offset = TransformNormal(offset, rotateMatrix);
		Vector3 worldTranslate = { target_->matWorld_.m[3][0],target_->matWorld_.m[3][1],target_->matWorld_.m[3][2] };

		interTarget_ = Lerp(delay_, worldTranslate, interTarget_);
		viewProjection_.translation_ = interTarget_ + offset;
	}
}

void FollowCamera::Rotate() {
	XINPUT_STATE joystate;

	if (Input::GetInstance()->GetJoystickState(0, joystate)) {
		const float kRotateSpeed = 0.02f;
		viewProjection_.rotation_.y += (float)joystate.Gamepad.sThumbRX / SHRT_MAX * kRotateSpeed;
	}
}

void FollowCamera::ApplyGlobalVariables() {
	GlobalVariables* globalVariables = GlobalVariables::GetInstance();

	const char* groupName = "Camera";
	delay_ = globalVariables->GetFloatValue(groupName, "delay");
	if (delay_ >= 1.0f) {
		delay_ = 0.9999999f;
	}
	if (delay_ <= 0.0f) {
		delay_ = 0.0f;
	}
}

void FollowCamera::Change() {
	changeRotate = viewProjection_.rotation_;
}

void FollowCamera::Reset() {
	if (target_) {
		Vector3 worldTranslate = { target_->matWorld_.m[3][0],target_->matWorld_.m[3][1],target_->matWorld_.m[3][2] };
		interTarget_ = worldTranslate;
		viewProjection_.rotation_.y = target_->rotation_.y;
	}

	destinationAngleY_ = viewProjection_.rotation_.y;
}