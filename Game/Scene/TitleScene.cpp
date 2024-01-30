#include "TitleScene.h"
#include "EngineBase/ImGuiManager.h"

TitleScene::~TitleScene() {

}

void TitleScene::Initialize() {	
	input = Input::GetInstance();
	textureManager_ = TextureManager::GetInstance();
	engine_ = YTEngine::GetInstance();

	count = 0;

	spriteTexture_ = textureManager_->Load("Resource/title.png");
	fadeTexture_ = textureManager_->Load("Resource/black.png");

	Vector4 a = { 0.0f,0.0f,0.0f,1.0f };
	Vector4 b = { 1280.0f,720.0f,0.0f,1.0f };

	sprite_ = std::make_unique<Sprite>();
	sprite_->Initialize(a, b);

	fadeSprite_ = std::make_unique<Sprite>();
	fadeSprite_->Initialize(a, b);

	spriteTransform_ = { {1.0f,1.0f, 1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
	
	spriteUvTransform_ = { {1.0f,1.0f,1.0f}, {0.0f,0.0f,0.0f}, {0.0f,0.0f,0.0f} };

	spriteMaterial_ = { 1.0f,1.0f,1.0f,1.0f };
	fadeMaterial_ = { 1.0f,1.0f,1.0f,0.0f };

	fadeCounter_ = 0;
	isStart_ = false;
}

void TitleScene::Update() {
	if (input->PressKey(DIK_SPACE)) {
		isStart_ = true;
	}

	if (isStart_ == true) {
		fadeMaterial_.w += 0.01f;
	}

	if (fadeMaterial_.w >= 1.0f) {
		isStart_ = false;
		sceneNum = GAME_SCENE;
	}


	if (sceneNum < 0) {
		sceneNum = 0;
	}
}

void TitleScene::Draw() {
	ImGui::Begin("TITLE");
	ImGui::Text("Push to A to Start");
	ImGui::End();

	engine_->SpritePreDraw();
	sprite_->Draw(spriteTransform_, spriteUvTransform_, spriteMaterial_, spriteTexture_);
	fadeSprite_->Draw(spriteTransform_, spriteUvTransform_, fadeMaterial_, fadeTexture_);
}

void TitleScene::Finalize() {

}
