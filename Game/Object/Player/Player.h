#pragma once
#include "3D/WorldTransform.h"
#include "3D/Model.h"
#include "EngineManager/Input/Input.h"
#include "EngineManager/Input/Input.h"
#include "EngineManager/Collision/Collider.h"
#include "EngineManager/Collision/CollisionConfig.h"
#include "Object/ICharacter.h"
#include "EngineManager/GlobalVariables/GlobalVariables.h"
#include <optional>

class Player :public Collider, public ICharacter {
public:
	void Initialize(const std::vector<Model*>& models) override;
	void Update()override;
	void Draw(const ViewProjection& view)override;

	void IsCollision(const WorldTransform& worldtransform);
	void OnCollision() override;

	void IsFall();
	bool isHit_;

	const WorldTransform& GetWorldTransformBody() { return worldTransformBody_; }
	WorldTransform GetWorldTransform()override { return worldTransformBody_; }
	const WorldTransform& GetWorldTransformBase() { return worldTransformBody_; }
	
	StructSphere GetStructSphere() { return structSphere_; }
	OBB GetCollsionObb() { return collisionObb_; }

	void SetViewProjection(const ViewProjection* view) { viewProjection_ = view; }
	void SetObjectPos(const WorldTransform& worldtransform) { objectPos_ = worldtransform; }

	void Setparent(const WorldTransform* parent);
	void DeleteParent();
	
	bool GetIsAtack() { return isAtack; }
	bool isGameover() { return gameOver; }

private:
	enum class Behavior {
		kRoot,
		kAtack,
		kDash,
	};

	struct WorkDash {
		uint32_t dashParameter_ = 0;
		Vector3 move_;
		uint32_t cooltime_;
		uint32_t currentcooltime_;
		float velocity_;
	};

	WorkDash workDash_;
	Vector4 color;
	Input* input_ = nullptr;

	const ViewProjection* viewProjection_ = nullptr;
	StructSphere structSphere_;
	bool gameOver = false;
	WorldTransform worldTransform_;

	WorldTransform worldTransformHead_;
	WorldTransform worldTransformLarm_;
	WorldTransform worldTransformRarm_;
	WorldTransform worldTransformBody_;
	WorldTransform worldTransformHammer_;
	WorldTransform objectPos_;

	float floatingParametor_ = 0.0f;
	int animationFrame;

	Behavior behavior_ = Behavior::kRoot;
	std::optional<Behavior> behaviorRequest_ = std::nullopt;
	float cosin;

	OBB collisionObb_;
	Matrix4x4 Direction_;
	Quaternion quaternion_;
	Vector3 preMove_;
	Quaternion preQuaternion_;

	bool isDash_;
	bool isAtack;
	bool isMove_;
	float moveSpeed_;

private:
	void Move();
	void SetParentModel(const WorldTransform* parent);
	void ModelUpdateMatrix();
	void InitializeFloatGimmick();
	void UpdateFloatGimmick();

	void BehaviorRootUpdate();
	void BehaviorAtackUpdate();
	void BehaviorRootInitialize();
	void BehaviorAtackInitialize();

	void ApplyGlobalVariables();

	void BehaviorDashInitialize();

	void BehaviorDashUpdate();
};