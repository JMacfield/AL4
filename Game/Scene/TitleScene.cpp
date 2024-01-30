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
	enemyTexture_ = textureManager_->Load("Resource/Enemy/enemy.png");
	enemyHandTexture_ = textureManager_->Load("Resource/EnemyHand/enemyHand.png");
	cardTexture_ = textureManager_->Load("Resource/Card/Blue0/blue0.png");

	Vector4 a = { 0.0f,0.0f,0.0f,1.0f };
	Vector4 b = { 1280.0f,720.0f,0.0f,1.0f };

	Vector4 a1 = { 0.0f,0.0f,0.0f,1.0f };
	Vector4 b1 = { 200.0f,200.0f,0.0f,1.0f };

	enemyHandSprite_ = std::make_unique<Sprite>();
	enemyHandSprite_->Initialize(Vector4{ 0.0f,0.0f,0.0f,1.0f }, Vector4{ 120.0f,120.0f,0.0f,1.0f });

	sprite_ = std::make_unique<Sprite>();
	sprite_->Initialize(a, b);

	fadeSprite_ = std::make_unique<Sprite>();
	fadeSprite_->Initialize(a, b);

	enemySprite_ = std::make_unique<Sprite>();
	enemySprite_->Initialize(a1, b1);

	cardSprite_ = std::make_unique<Sprite>();
	cardSprite_->Initialize(Vector4{ 0.0f,0.0f,0.0f,1.0f }, Vector4{ 80.0f,80.0f,0.0f,1.0f });
	cardTransform_ = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{1080.0f,620.0f,0.0f} };

	enemyTransform_ = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{1000.0f,450.0f,0.0f} };
	enemyHandTransform_ = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{1020.0f,510.0f,0.0f} };

	spriteTransform_ = { {1.0f,1.0f, 1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
	
	spriteUvTransform_ = { {1.0f,1.0f,1.0f}, {0.0f,0.0f,0.0f}, {0.0f,0.0f,0.0f} };

	spriteMaterial_ = { 1.0f,1.0f,1.0f,1.0f };
	fadeMaterial_ = { 1.0f,1.0f,1.0f,0.0f };

	fadeCounter_ = 0;
	isStart_ = false;

	moveUp_ = true;
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

	uint16_t T = 120;

	float step = 2.0f * (float)M_PI / T;
	float floatingAmplitude = 0.3f;

	floatingParametor_ += step;
	floatingParametor_ = (float)std::fmod(floatingParametor_, 2.0f * M_PI);

	/*enemyTransform_.translate.y = std::sin(floatingParametor_) * floatingAmplitude + 1.0f;
	enemyHandTransform_.translate.y = std::sin(floatingParametor_) * floatingAmplitude + 1.0f;*/

	if (moveUp_ == true) {
		enemyTransform_.translate.y -= 1.0f;
		enemyHandTransform_.translate.y -= 0.5f;
		spriteTransform_.translate.y -= 0.5f;
		cardTransform_.translate.y -= 0.2f;
	}

	if (enemyTransform_.translate.y < 420.0f) {
		moveUp_ = false;
	}

	if (moveUp_ == false) {
		enemyTransform_.translate.y += 1.0f;
		enemyHandTransform_.translate.y += 0.5f;
		spriteTransform_.translate.y += 0.5f;
		cardTransform_.translate.y += 0.2f;
	}

	if (enemyTransform_.translate.y > 480.0f) {
		moveUp_ = true;
	}

	ImGui::Begin("Debug");
	ImGui::DragFloat3("Trans", &cardTransform_.translate.x, 0.1f);
	ImGui::End();
}

void TitleScene::Draw() {
	ImGui::Begin("TITLE");
	ImGui::Text("Push to A to Start");
	ImGui::End();

	engine_->SpritePreDraw();

	sprite_->Draw(spriteTransform_, spriteUvTransform_, spriteMaterial_, spriteTexture_);

	enemySprite_->Draw(enemyTransform_, spriteUvTransform_, spriteMaterial_, enemyTexture_);
	enemyHandSprite_->Draw(enemyHandTransform_, spriteUvTransform_, spriteMaterial_, enemyHandTexture_);
	cardSprite_->Draw(cardTransform_, spriteUvTransform_, spriteMaterial_, cardTexture_);

	fadeSprite_->Draw(spriteTransform_, spriteUvTransform_, fadeMaterial_, fadeTexture_);
}

void TitleScene::Finalize() {

}
