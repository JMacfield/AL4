#pragma once

#include "Iscene.h"
#include "EngineManager/Input/Input.h"
#include "CommSystem/CommSystem.h"
#include "2D/Sprite.h"

class TitleScene : public Iscene {
public:
	~TitleScene()override;
	 
	void Initialize() override;

	 void Update() override;

	 void Draw() override;
	
	 void Finalize()override;

private:
	Input* input = nullptr;
	TextureManager* textureManager_ = nullptr;
	YTEngine* engine_;

	int count;

	uint32_t spriteTexture_;
	uint32_t fadeTexture_;
	std::unique_ptr<Sprite> sprite_;
	std::unique_ptr<Sprite> fadeSprite_;
	Transform spriteTransform_;
	Transform spriteUvTransform_;
	Vector4 spriteMaterial_;
	Vector4 fadeMaterial_;

	int fadeCounter_;
	bool isStart_;

	std::unique_ptr<Sprite> enemySprite_;
	Transform enemyTransform_;
	uint32_t enemyTexture_;

	std::unique_ptr<Sprite> enemyHandSprite_;
	Transform enemyHandTransform_;
	uint32_t enemyHandTexture_;

	float floatingParametor_ = 0.0f;

	std::unique_ptr<Sprite> cardSprite_;
	uint32_t cardTexture_;
	Transform cardTransform_;

	bool moveUp_;
};