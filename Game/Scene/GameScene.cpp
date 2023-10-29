#include "gameScene.h"


GameScene::~GameScene()
{
	
}

void GameScene::Initialize()
{
	engine_ = YTEngine::GetInstance();
	directXCommon_ = DirectXCommon::GetInstance();
	textureManager_ = TextureManager::GetInstance();
	input_ = Input::GetInstance();

	collisionManager_ = make_unique<CollisionManager>();
	int a= textureManager_->Load("Resource/tex.png");

	viewProjection_.Initialize();
	viewProjection_.translation_ = { 0.0f,0.0f,-5.0f };

	playerModel_.reset(Model::CreateModelFromObj("Resource", "saikoro.obj"));
	player_ = make_unique<Player>();
	player_->Initialize(playerModel_.get());
	
	followCamera_ = std::make_unique<FollowCamera>();
	followCamera_->Initialize();
	followCamera_->SetTarget(&player_->GetWorldTransformBase());
	
	player_->SetViewProjection(&followCamera_->GetViewProjection());
	
	skyDomeModel_ .reset( Model::CreateModelFromObj("Resource","skyDome.obj"));
	skyDome_ = make_unique<SkyDome>();
	skyDome_->Initialize(skyDomeModel_.get());
	
	groundManager_ = make_unique<GroundManager>();
	groundManager_->Initialize();
	
	goal_ = make_unique<Goal>();
	goal_->Initialize({0.0f,2.0f,62.0f},{1.0f,1.0f,1.0f});
	
	enemy_ = make_unique<Enemy>();
	enemyBodyModel.reset(Model::CreateModelFromObj("Resource", "saikoro.obj"));
	enemyHeadModel.reset(Model::CreateModelFromObj("Resource", "saikoro.obj"));
	enemyL_armModel.reset(Model::CreateModelFromObj("Resource", "float_L_arm.obj"));
	enemyR_armModel.reset(Model::CreateModelFromObj("Resource", "float_R_arm.obj"));
	
	std::vector<Model*>enemyModels = { enemyBodyModel.get(),enemyHeadModel.get(),enemyL_armModel.get(),enemyR_armModel.get() };
	enemy_->Initialize(enemyModels);
	
	GlobalVariables* globalVariables{};
	globalVariables = GlobalVariables::GetInstance();
	
	blendCount_ = 0;
	
	const char* groupName = "Player";
	
	GlobalVariables::GetInstance()->CreateGroup(groupName);
	globalVariables->AddItem(groupName, "Test", 90.0f);
	ApplyGlobalVariables();
	
	count_ = 0;
}

void GameScene::Update()
{
	count_++;
	groundManager_->Update();
	player_->Update();
	enemy_->Update();
	if (player_->isGameover() == true) {
		Initialize();
	}
	player_->isHit_ = false;
	
	goal_->Update();
	
		for (int i = 0; i < 2; i++) {
			if (IsCollision(groundManager_->GetOBB(i), player_->GetStructSphere())) {
				player_->isHit_ = true;
				player_->SetObjectPos(groundManager_->GetGround(i)->GetWorldTransform());
			}
		}
		if (count_ >= 5) {
			if (IsCollision(groundManager_->GetOBB(2), player_->GetStructSphere())) {
				player_->isHit_ = true;
				player_->IsCollision(groundManager_->GetMoveGround()->GetWorldTransform());
			}
			else {
				player_->DeleteParent();
			}
		}
	

	viewProjection_.UpdateMatrix();
	followCamera_->Update();
	viewProjection_.matView = followCamera_->GetViewProjection().matView;
	viewProjection_.matProjection = followCamera_->GetViewProjection().matProjection;
	viewProjection_.TransferMatrix();

	ImGui::Begin("Scene");

	ImGui::InputInt("SceneNum", &sceneNum);
	if (sceneNum > 1) {
		sceneNum = 1;
	}
	ImGui::End();

	collisionManager_->ClearColliders();
	collisionManager_->AddCollider(player_.get());
	collisionManager_->AddCollider(goal_.get());
	collisionManager_->AddCollider(enemy_.get());
	if (count_ >= 5) {
		collisionManager_->CheckAllCollision();
	}
}


void GameScene::Draw()
{
	
	//3D描画準備
	engine_->ModelPreDraw();
	Draw3D();
	//2D描画準備
	engine_->SpritePreDraw();
	Draw2D();
}

void GameScene::Draw3D()
{
	skyDome_->Draw(viewProjection_);
	player_->Draw(viewProjection_);
	groundManager_->Draw(viewProjection_);
	goal_->Draw(viewProjection_);
	enemy_->Draw(viewProjection_);
}

void GameScene::ApplyGlobalVariables()
{
	GlobalVariables* globalVariables = GlobalVariables::GetInstance();

	const char* groupName = "Player";
	
}

void GameScene::Draw2D() {
	engine_->SetBlendMode(blendCount_);
}
void GameScene::Finalize() {
		
}