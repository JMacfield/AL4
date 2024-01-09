#include "ClearScene.h"
#include "EngineBase/ImGuiManager.h"

ClearScene::~ClearScene() {

}

void ClearScene::Initialize() {
	input = Input::GetInstance();
	textureManager_ = TextureManager::GetInstance();
	engine_ = YTEngine::GetInstance();

	count = 0;

	spriteTexture_ = textureManager_->Load("Resource/title.png");

	Vector4 a = { 0.0f,0.0f,0.0f,1.0f };
	Vector4 b = { 1280.0f,720.0f,0.0f,1.0f };

	sprite_ = std::make_unique<Sprite>();
	sprite_->Initialize(a, b);

	spriteTransform_ = { {1.0f,1.0f, 1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };

	spriteUvTransform_ = { {1.0f,1.0f,1.0f}, {0.0f,0.0f,0.0f}, {0.0f,0.0f,0.0f} };

	spriteMaterial_ = { 1.0f,1.0f,1.0f,1.0f };
}

void ClearScene::Update() {




	if (input->PressKey(DIK_SPACE)) {
		sceneNum = GAME_SCENE;
	}


	if (sceneNum < 0) {
		sceneNum = 0;
	}
}

void ClearScene::Draw() {
	engine_->SpritePreDraw();
	sprite_->Draw(spriteTransform_, spriteUvTransform_, spriteMaterial_, spriteTexture_);
}

void ClearScene::Finalize() {

}
