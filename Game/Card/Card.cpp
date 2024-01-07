#include "Card/Card.h"

void Card::Initialize() {
	textureManager_ = TextureManager::GetInstance();
	input_ = Input::GetInstance();

	spriteTexture_[0] = textureManager_->Load("Resource/Card/blue3.png");
	spriteTexture_[1] = textureManager_->Load("Resource/Card/green5.png");
	spriteTexture_[2] = textureManager_->Load("Resource/Card/greenplus.png");
	spriteTexture_[3] = textureManager_->Load("Resource/Card/red4.png");
	spriteTexture_[4] = textureManager_->Load("Resource/Card/red6.png");
	spriteTexture_[5] = textureManager_->Load("Resource/Card/yellow4.png");

	Vector4 a = { 0.0f,0.0f,0.0f,1.0f };
	Vector4 b = { 200.0f,400.0f,0.0f,1.0f };

	sprite_[0] = std::make_unique<Sprite>();
	sprite_[0]->Initialize(a,b);

	sprite_[1] = std::make_unique<Sprite>();
	sprite_[1]->Initialize(a,b);

	sprite_[2] = std::make_unique<Sprite>();
	sprite_[2]->Initialize(a,b);

	sprite_[3] = std::make_unique<Sprite>();
	sprite_[3]->Initialize(a,b);

	sprite_[4] = std::make_unique<Sprite>();
	sprite_[4]->Initialize(a,b);

	sprite_[5] = std::make_unique<Sprite>();
	sprite_[5]->Initialize(a,b);

	spriteTransform_[0] = { {0.5f,0.5f,0.5f},{0.0f,0.0f,0.0f},{150.0f,500.0f,0.0f} };
	spriteTransform_[1] = { {0.5f,0.5f,0.5f},{0.0f,0.0f,0.0f},{300.0f,500.0f,0.0f} };
	spriteTransform_[2] = { {0.5f,0.5f,0.5f},{0.0f,0.0f,0.0f},{450.0f,500.0f,0.0f} };
	spriteTransform_[3] = { {0.5f,0.5f,0.5f},{0.0f,0.0f,0.0f},{600.0f,500.0f,0.0f} };
	spriteTransform_[4] = { {0.5f,0.5f,0.5f},{0.0f,0.0f,0.0f},{750.0f,500.0f,0.0f} };
	spriteTransform_[5] = { {0.5f,0.5f,0.5f},{0.0f,0.0f,0.0f},{900.0f,500.0f,0.0f} };

	spriteUvTransform_ = { {1.0f,1.0f,1.0f}, {0.0f,0.0f,0.0f}, {0.0f,0.0f,0.0f} };

	spriteMaterial_[0] = { 1.0f,1.0f,1.0f,0.5f };
	spriteMaterial_[1] = { 1.0f,1.0f,1.0f,0.5f };
	spriteMaterial_[2] = { 1.0f,1.0f,1.0f,0.5f };
	spriteMaterial_[3] = { 1.0f,1.0f,1.0f,0.5f};
	spriteMaterial_[4] = { 1.0f,1.0f,1.0f,0.5f};
	spriteMaterial_[5] = { 1.0f,1.0f,1.0f,0.5f };
}

void Card::Update() {
	static char text[8] = "Red 6";

	if (input_->PushKey(DIK_2)) {
		isShow = true;
	}

	if (isShow == true) {
		spriteMaterial_[3] = { 1.0f,1.0f,1.0f,1.0f };
		spriteMaterial_[4] = { 1.0f,1.0f,1.0f,1.0f };

		ImGui::Begin("Info");
		ImGui::Text("%s", text);
		ImGui::End();
	}

	ImGui::Begin("Debug");
	ImGui::Text("Press key 1 to Get Next Card Info");
	ImGui::End();
}

void Card::Draw() {
	sprite_[0]->Draw(spriteTransform_[0], spriteUvTransform_, spriteMaterial_[0], spriteTexture_[0]);
	sprite_[1]->Draw(spriteTransform_[1], spriteUvTransform_, spriteMaterial_[1], spriteTexture_[1]);
	sprite_[2]->Draw(spriteTransform_[2], spriteUvTransform_, spriteMaterial_[2], spriteTexture_[2]);
	sprite_[3]->Draw(spriteTransform_[3], spriteUvTransform_, spriteMaterial_[3], spriteTexture_[3]);
	sprite_[4]->Draw(spriteTransform_[4], spriteUvTransform_, spriteMaterial_[4], spriteTexture_[4]);
	sprite_[5]->Draw(spriteTransform_[5], spriteUvTransform_, spriteMaterial_[5], spriteTexture_[5]);
}