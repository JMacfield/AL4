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

	viewProjection_.Initialize();
	viewProjection_.translation_ = { 0.0f,0.0f,-5.0f };
}

void GameScene::Update() {
	
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

void GameScene::Draw3D() {
}

void GameScene::ApplyGlobalVariables()
{
	
}

void GameScene::Draw2D() {
	engine_->SetBlendMode(blendCount_);
}
void GameScene::Finalize() {
		
}