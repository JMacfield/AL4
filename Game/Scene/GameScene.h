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
#include "Object/SkyDome/SkyDome.h"
#include "Object/Player/Player.h"
#include "Camera/FollowCamera.h"
#include "Object/Ground/Manager/GroundManager.h"
#include "Object/Goal/Goal.h"
#include "Object/Enemy/Enemy.h"

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
#pragma endregion

#pragma region ゲームの機能
	/*int count_;
	unique_ptr<SkyDome> skyDome_ = nullptr;
	unique_ptr<Model> skyDomeModel_ = nullptr;
	unique_ptr<Model> playerModel_ = nullptr;
	unique_ptr<Player> player_;
	unique_ptr<FollowCamera> followCamera_;
	
	unique_ptr<GroundManager> groundmanager_;
	unique_ptr<CollisionManager> collisionManager_;
	unique_ptr<Goal> goal_;
	unique_ptr<Enemy>enemy_;
	
	std::unique_ptr<Model> enemyHeadModel = nullptr;
	std::unique_ptr<Model> enemyBodyModel = nullptr;
	std::unique_ptr<Model> enemyL_armModel = nullptr;
	std::unique_ptr<Model> enemyR_armModel = nullptr;
	std::unique_ptr<Model> player_Hammer_ = nullptr;*/

	Vector3 axis = Normalise({ 1.0f,1.0f,1.0f });
	float angle = 0.44f;
#pragma endregion
};