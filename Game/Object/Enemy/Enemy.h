#pragma once

#include "EngineManager/Collision/Collider.h"
#include "EngineManager/Collision/CollisionConfig.h"
#include "3D/WorldTransform.h"
#include "3D/Model.h"
#include "EngineManager/Input/Input.h"
#include "3D/ViewProjection.h"
#include "Object/ICharacter.h"

class Enemy :public ICharacter, public Collider {
public:
	void Initialize(const std::vector<Model*>& models) override;
	void Update()override;
	void Draw(const ViewProjection& view)override;

	StructSphere GetStructSphere() { return structSphere_; }
	void OnCollision() override;
	const WorldTransform& GetWorldTransformBody() { return worldTransformBody_; }
	WorldTransform GetWorldTransform()override { return worldTransformBase_; }
	void IsDead();
	bool GetisAlive() { return isAlive_; }

private:
	WorldTransform worldTransformBase_;
	WorldTransform worldTransformHead_;
	WorldTransform worldTransformLarm_;
	WorldTransform worldTransformRarm_;
	WorldTransform worldTransformBody_;

	Input* input_ = nullptr;
	const ViewProjection* viewProjection_ = nullptr;
	float floatingParametor_ = 0.0f;
	int animationFrame;
	
	Vector3 move_;
	StructSphere structSphere_;
	bool isAlive_;

private:
	void Move();
	void SetParent(const WorldTransform* parent);
	void ModelUpdateMatrix();
	void InitializeFloatGimmick();
	void UpdateFloatGimmick();
};