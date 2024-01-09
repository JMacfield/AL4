#include "GameScene.h"

GameScene::~GameScene() {

}

void GameScene::Initialize() {
	engine_ = YTEngine::GetInstance();

	directXCommon_ = DirectXCommon::GetInstance();

	textureManager_ = TextureManager::GetInstance();
	
	input_ = Input::GetInstance();

	viewProjection_.Initialize();
	viewProjection_.translation_ = { 0.0f,5.0f,-20.0f };

	skyDomeModel_.reset(Model::CreateModelFromObj("Resource/SkyDome", "SkyDome.obj"));
	skyDome_ = make_unique<SkyDome>();
	skyDome_->Initialize(skyDomeModel_.get());
	
	//groundmanager_ = make_unique<GroundManager>();
	//groundmanager_->Initialize();
	
	//followCamera_.Initialize();

	GlobalVariables* globalVariables = GlobalVariables::GetInstance();
	const char* groupName = "view";
	globalVariables->CreateGroup(groupName);
	globalVariables->AddItem(groupName, "transration", viewProjection_.translation_);
	globalVariables->AddItem(groupName, "Rotate", viewProjection_.rotation_);

	card_ = make_unique<Card>();
	card_->Initialize();

	ApplyGlobalVariables();
}

void GameScene::Update() {
	card_->Update();

	if (card_->GetWin() == true) {
		sceneNum = CLEAR_SCENE;
	}
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
	skyDome_->Draw(viewProjection_);
	card_->Draw(viewProjection_);
	//groundmanager_->Draw(viewProjection_);
	
	engine_->PariclePreDraw();
}

void GameScene::ApplyGlobalVariables() {
	GlobalVariables* globalVariables = GlobalVariables::GetInstance();

	const char* groupName = "view";
	viewProjection_.rotation_ = globalVariables->GetVector3Value(groupName, "Rotate");
	viewProjection_.translation_ = globalVariables->GetVector3Value(groupName, "transration");
}

void GameScene::Draw2D() {
	engine_->SetBlendMode(kBlendModeNormal);
	
	card_->Draw2D();
}

void GameScene::Finalize() {



}