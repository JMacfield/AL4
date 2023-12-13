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
	//int a;
	//unique_ptr<Particle> particle;
	//int count_;
	//unique_ptr<SkyDome> skyDome_ = nullptr;
	//unique_ptr<Model> skyDomeModel_ = nullptr;
	//unique_ptr<Model> playerModel_ = nullptr;
	//unique_ptr<Player> player_;
	//unique_ptr<FollowCamera> followCamera_;
	////unique_ptr<ground> ground_;
	//unique_ptr<GroundManager> groundmanager_;
	//unique_ptr<CollisionManager> collisionManager_;
	//unique_ptr<Goal> goal_;
	//list<Enemy*> enemys_;
	//unique_ptr<Enemy>enemy_;
	//unique_ptr<LookOn> lockOn_;
	//std::unique_ptr<Model> enemyHeadModel = nullptr;
	//std::unique_ptr<Model> enemyBodyModel = nullptr;
	//std::unique_ptr<Model> enemyL_armModel = nullptr;
	//std::unique_ptr<Model> enemyR_armModel = nullptr;
	//std::unique_ptr<Model> HeadModel = nullptr;
	//std::unique_ptr<Model> BodyModel = nullptr;
	//std::unique_ptr<Model> L_armModel = nullptr;
	//std::unique_ptr<Model> R_armModel = nullptr;
	//std::unique_ptr<Model> player_Hammer_ = nullptr;
	//std::vector<Model*>enemyModels;

	//std::unique_ptr<Model> particleModel_;
#pragma endregion
};