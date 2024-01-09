#pragma once

#include "EngineBase/YTEngine.h"
#include "EngineManager/Input/Input.h"
#include "MyMath/MyMath.h"
#include "2D/Triangle.h"
#include "Iscene.h"
#include "2D/Sprite.h"
#include "3D/Sphere.h"
#include "3D/Model.h"
#include "3D/WorldTransform.h"
#include "3D/ViewProjection.h"
#include "EngineManager/Collision/CollisionManager.h"
#include "EngineManager/Texture/TextureManager.h"
#include "EngineManager/GlobalVariables/GlobalVariables.h"
#include "Object/SkyDome/SkyDome.h"
#include "Object/Player/Player.h"
#include "Camera/FollowCamera.h"
#include "Object/Ground/Manager/GroundManager.h"
#include "Object/Goal/Goal.h"
#include "Object/Enemy/Enemy.h"
#include "Camera/LockOn.h"
#include "2D/Particle.h"
#include <list>
#include "Card/Card.h"

using namespace std;

class GameScene :public Iscene {
public:
	~GameScene();

	void Initialize()override;
	void Update()override;
	void Draw()override;
	
	void Finalize()override;

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

	//FollowCamera followCamera_;
#pragma endregion

#pragma region ゲームの機能
	unique_ptr<SkyDome> skyDome_ = nullptr;
	unique_ptr<Model> skyDomeModel_ = nullptr;
	
	//unique_ptr<GroundManager> groundmanager_;
	unique_ptr<Card> card_;
#pragma endregion
};