#pragma once

#include "2D/Sprite.h"
#include "EngineManager/Input/Input.h"
#include "EngineManager/Texture/TextureManager.h"

#include <memory>
#include <string>

class Card {
public:
	void Initialize();
	void Update();
	void Draw();

private:
	TextureManager* textureManager_;
	Input* input_;

	uint32_t spriteTexture_[6];
	std::unique_ptr<Sprite> sprite_[6];

	Transform spriteTransform_[6];
	Transform spriteUvTransform_;
	Vector4 spriteMaterial_[6];

	bool isShow = false;
};