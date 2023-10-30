#pragma once

#include "EngineBase/YTEngine.h"
#include "EngineManager/Input/Input.h"
#include "MyMath/MyMath.h"
#include "2D/Triangle.h"
#include "IScene.h"
#include "2D/Sprite.h"
#include "3D/Sphere.h"
#include "3D/Model.h"
#include "3D/WorldTransform.h"
#include "3D/ViewProjection.h"
#include "EngineManager/Collision/CollisionManager.h"
#include "EngineManager/Texture/TextureManager.h"
#include "EngineManager/GlobalVariables/GlobalVariables.h"

using namespace std;

class GameScene : public Iscene {
public:
	~GameScene();
	void Initialize() override;
	void Update() override;
	
	void Draw() override;
	void Finalize() override;

private:
#pragma region 基本機能
	YTEngine* engine_;
	DirectXCommon* directXCommon_;
	Sprite* sprite_;
	TextureManager* textureManager_;
	Input* input_;
	ViewProjection viewProjection_;

	int blendCount_;
	
	void Draw2D();
	void Draw3D();
	void ApplyGlobalVariables();
#pragma endregion

#pragma region ゲームの機能
	
#pragma endregion
};