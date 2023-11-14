#include "FollowCamera.h"
#include "EngineManager/GlobalVariables/GlobalVariables.h"

void FollowCamera::Initialize() {
	//ビュープロジェクションの初期化
	viewProjection_.Initialize();

	GlobalVariables* globalVariables = {};
	globalVariables = GlobalVariables::GetInstance();

	const char* groupName = "FollowCamera";
	GlobalVariables::GetInstance()->CreateGroup(groupName);
	//グループを追加
	globalVariables->CreateGroup(groupName);
	globalVariables->AddItem(groupName, "Delay", delay_);
};

void FollowCamera::Update() {

	//追従対象がいれば
	if (target_) {
		//追従座標の補間
		interTarget_ = Lerp(interTarget_, GetTargetWorldPosition(), delay_);
	}

	//追従対象からのオフセット
	Vector3 offset = FollowCamera::Offset();
	//カメラ座標
	viewProjection_.translation_ = Add(interTarget_, offset);

	XINPUT_STATE joyState{};

	//旋回操作
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		//しきい値
		const float threshold = 0.7f;

		//回転フラグ
		bool isRotation = false;

		//回転量
		Vector3 rotation = {
			(float)joyState.Gamepad.sThumbRY / SHRT_MAX,
			(float)joyState.Gamepad.sThumbRX / SHRT_MAX,
			0.0f
		};

		//スティックの押し込みが遊び範囲を超えていたら回転フラグをtureにする
		if (Length(rotation) > threshold) {
			isRotation = true;
		}

		if (isRotation) {
			//回転速度
			const float kRotSpeedX = 0.02f;
			const float kRotSpeedY = 0.04f;

			destinationAngleX_ -= rotation.x * kRotSpeedX;
			destinationAngleY_ += rotation.y * kRotSpeedY;
		}
	}

	viewProjection_.rotation_.x = LerpShortAngle(viewProjection_.rotation_.x, destinationAngleX_, 0.1f);
	viewProjection_.rotation_.y = LerpShortAngle(viewProjection_.rotation_.y, destinationAngleY_, 0.1f);

	//ビュー行列の更新
	viewProjection_.UpdateMatrix();

	//グローバル変数の適応
	FollowCamera::ApplyGlobalVariables();
};

Vector3 FollowCamera::Offset() {
	//追従対象からのオフセット
	Vector3 offset = { 0.0f, 2.0f, -20.0f };
	//回転行列の合成
	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(viewProjection_.rotation_.x);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(viewProjection_.rotation_.y);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(viewProjection_.rotation_.z);
	Matrix4x4 rotateMatrix = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));
	//オフセットをカメラの回転に合わせて回転させる
	offset = TransformNormal(offset, rotateMatrix);

	return offset;
}


void FollowCamera::Reset() {
	//追従対象がいれば
	if (target_) {
		//追従座標・角度の初期化
		interTarget_ = target_->translation_;
		viewProjection_.rotation_.x = target_->rotation_.x;
		viewProjection_.rotation_.y = target_->rotation_.y;
	}
	destinationAngleX_ = viewProjection_.rotation_.x;
	destinationAngleY_ = viewProjection_.rotation_.y;

	//追従対象からのオフセット
	Vector3 offset = FollowCamera::Offset();
	viewProjection_.translation_ = Add(interTarget_, offset);
}

void FollowCamera::SetTarget(const WorldTransform* target) {
	target_ = target;
	FollowCamera::Reset();
}

Vector3 FollowCamera::GetTargetWorldPosition() {
	Vector3 pos{};
	pos.x = target_->matWorld_.m[3][0];
	pos.y = target_->matWorld_.m[3][1];
	pos.z = target_->matWorld_.m[3][2];
	return pos;
}

void FollowCamera::ApplyGlobalVariables() {
	GlobalVariables* globalVariables = GlobalVariables::GetInstance();
	const char* groupName = "FollowCamera";
	
	delay_ = globalVariables->GetFloatValue(groupName, "Delay");
}