#include "GameScene.h"

GameScene::~GameScene() {

}

void GameScene::Initialize() {
	engine_ = YTEngine::GetInstance();
	directXCommon_ = DirectXCommon::GetInstance();
	textureManager_ = TextureManager::GetInstance();
	
	viewProjection_.Initialize();
	viewProjection_.translation_ = { 0.0f,0.0f,-5.0f };
	
	/*collisionManager_ = make_unique<CollisionManager>();
	input_ = Input::GetInstance();
	int a = textureManager_->Load("Resource/tex.png");
	playerModel_.reset(Model::CreateModelFromObj("Resource/CUBE", "CUBE.obj"));
	player_ = make_unique<Player>();
	enemyBodyModel.reset(Model::CreateModelFromObj("Resource/float_Body", "float_Body.obj"));
	enemyHeadModel.reset(Model::CreateModelFromObj("Resource/float_Head", "float_head.obj"));
	enemyL_armModel.reset(Model::CreateModelFromObj("Resource/float_L_arm", "float_L_arm.obj"));
	enemyR_armModel.reset(Model::CreateModelFromObj("Resource/float_R_arm", "float_R_arm.obj"));
	player_Hammer_.reset(Model::CreateModelFromObj("Resource/Hammer", "hammer.obj"));
	std::vector<Model*>playerModels = { enemyBodyModel.get(),enemyHeadModel.get(),enemyL_armModel.get(),enemyR_armModel.get(),player_Hammer_.get() };
	player_->Initialize(playerModels);
	followCamera_ = std::make_unique<FollowCamera>();
	followCamera_->Initialize();
	followCamera_->SetTarget(&player_->GetWorldTransformBase());
	player_->SetViewProjection(&followCamera_->GetViewProjection());
	skyDomeModel_.reset(Model::CreateModelFromObj("Resource/SkyDome", "SkyDome.obj"));
	skyDome_ = make_unique<SkyDome>();
	skyDome_->Initialize(skyDomeModel_.get());
	groundmanager_ = make_unique<GroundManager>();
	groundmanager_->Initialize();
	goal_ = make_unique<Goal>();
	goal_->Initialize({ 0.0f,2.0f,62.0f }, { 1.0f,1.0f,1.0f });
	enemy_ = make_unique<Enemy>();

	std::vector<Model*>enemyModels = { enemyBodyModel.get(),enemyHeadModel.get(),enemyL_armModel.get(),enemyR_armModel.get() };
	enemy_->Initialize(enemyModels);
	blendCount_ = 0;

	ApplyGlobalVariables();
	count_ = 0;*/

	blendCount_ = 0;
}

void GameScene::Update() {
	/*count_++;
	groundmanager_->Update();

	enemy_->Update();
	if (player_->isGameover() == true) {
		Initialize();
	//}
	//player_->isHit_ = false;

	//goal_->Update();
	//if (count_ >= 5) {
	//	for (int i = 0; i < 2; i++) {
			if (IsCollision(groundmanager_->GetOBB(i), player_->GetStructSphere())) {
				player_->isHit_ = true;
				player_->SetObjectPos(groundmanager_->GetGround(i)->GetWorldTransform());
			}
		}

		if (IsCollision(groundmanager_->GetOBB(2), player_->GetStructSphere())) {
			player_->isHit_ = true;
			player_->IsCollision(groundmanager_->GetMoveGround()->GetWorldTransform());
		}
		else {
			player_->DeleteParent();
		}


		if (player_->GetIsAtack()) {
			if (IsCollision(player_->GetCollsionObb(), enemy_->GetStructSphere())) {
				enemy_->IsDead();
			}
		}
	}
	player_->Update();
	viewProjection_.UpdateMatrix();
	followCamera_->Update();
	viewProjection_.matView = followCamera_->GetViewProjection().matView;
	viewProjection_.matProjection = followCamera_->GetViewProjection().matProjection;
	viewProjection_.TransferMatrix();


	if (sceneNum > 1) {
		sceneNum = 1;
	}


	collisionManager_->ClearColliders();
	collisionManager_->AddCollider(player_.get());
	collisionManager_->AddCollider(goal_.get());
	if (enemy_) {
		if (enemy_->GetisAlive()) {
			collisionManager_->AddCollider(enemy_.get());
		}
	}
	if (count_ >= 20) {
		collisionManager_->CheckAllCollision();
	}*/

	Vector3 from0 = Normalize(Vector3{1.0f,1.0f,1.0f});
	Vector3 to0 = -from0;
	Vector3 from1 = Normalize(Vector3{ -0.6f,0.9f,0.2f });
	Vector3 to1 = -from1;

	Matrix4x4 rotateMatrix0 = DirectionToDirection(
		Normalize(Vector3{ 1.0f,1.0f,1.0f }), Normalize(Vector3{ -1.0f,0.0f,0.0f }));
	Matrix4x4 rotateMatrix1 = DirectionToDirection(from0, to0);
	Matrix4x4 rotateMatrix2 = DirectionToDirection(from1, to1);

	ImGui::Begin("Show RotateMatrix");
	ImGui::Text("rotateMatrix0");
	ImGui::Text("%4.3f %4.3f %4.3f %4.3f", rotateMatrix0.m[0][0], rotateMatrix0.m[0][1], rotateMatrix0.m[0][2], rotateMatrix0.m[0][3]);
	ImGui::Text("%4.3f %4.3f %4.3f %4.3f", rotateMatrix0.m[1][0], rotateMatrix0.m[1][1], rotateMatrix0.m[1][2], rotateMatrix0.m[1][3]);
	ImGui::Text("%4.3f %4.3f %4.3f %4.3f", rotateMatrix0.m[2][0], rotateMatrix0.m[2][1], rotateMatrix0.m[2][2], rotateMatrix0.m[2][3]);
	ImGui::Text("%4.3f %4.3f %4.3f %4.3f", rotateMatrix0.m[3][0], rotateMatrix0.m[3][1], rotateMatrix0.m[3][2], rotateMatrix0.m[3][3]);
	ImGui::Text("");
	ImGui::Text("rotateMatrix1");
	ImGui::Text("%4.3f %4.3f %4.3f %4.3f", rotateMatrix1.m[0][0], rotateMatrix1.m[0][1], rotateMatrix1.m[0][2], rotateMatrix1.m[0][3]);
	ImGui::Text("%4.3f %4.3f %4.3f %4.3f", rotateMatrix1.m[1][0], rotateMatrix1.m[1][1], rotateMatrix1.m[1][2], rotateMatrix1.m[1][3]);
	ImGui::Text("%4.3f %4.3f %4.3f %4.3f", rotateMatrix1.m[2][0], rotateMatrix1.m[2][1], rotateMatrix1.m[2][2], rotateMatrix1.m[2][3]);
	ImGui::Text("%4.3f %4.3f %4.3f %4.3f", rotateMatrix1.m[3][0], rotateMatrix1.m[3][1], rotateMatrix1.m[3][2], rotateMatrix1.m[3][3]);
	ImGui::Text("");
	ImGui::Text("rotateMatrix2");
	ImGui::Text("%4.3f %4.3f %4.3f %4.3f", rotateMatrix2.m[0][0], rotateMatrix2.m[0][1], rotateMatrix2.m[0][2], rotateMatrix2.m[0][3]);
	ImGui::Text("%4.3f %4.3f %4.3f %4.3f", rotateMatrix2.m[1][0], rotateMatrix2.m[1][1], rotateMatrix2.m[1][2], rotateMatrix2.m[1][3]);
	ImGui::Text("%4.3f %4.3f %4.3f %4.3f", rotateMatrix2.m[2][0], rotateMatrix2.m[2][1], rotateMatrix2.m[2][2], rotateMatrix2.m[2][3]);
	ImGui::Text("%4.3f %4.3f %4.3f %4.3f", rotateMatrix2.m[3][0], rotateMatrix2.m[3][1], rotateMatrix2.m[3][2], rotateMatrix2.m[3][3]);
	ImGui::End();
}


void GameScene::Draw() {
	//3D描画準備
	engine_->ModelPreDraw();
	Draw3D();
	//2D描画準備
	engine_->SpritePreDraw();
	Draw2D();
}

void GameScene::Draw3D() {
	/*skyDome_->Draw(viewProjection_);
	player_->Draw(viewProjection_);
	groundmanager_->Draw(viewProjection_);
	goal_->Draw(viewProjection_);
	enemy_->Draw(viewProjection_);*/

}

void GameScene::ApplyGlobalVariables() {
	
}

void GameScene::Draw2D() {
	engine_->SetBlendMode(blendCount_);
}
void GameScene::Finalize() {

}