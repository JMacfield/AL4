#pragma once

#include "Iscene.h"
#include "EngineManager/Input/Input.h"
#include "CommSystem/CommSystem.h"
#include "EngineManager/Texture/TextureManager.h"
#include "EngineBase/YTEngine.h"
#include "2D/Sprite.h"

class ClearScene : public Iscene {
public:
	~ClearScene()override;

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Finalize()override;

private:
	Input* input = nullptr;

	TextureManager* textureManager_ = nullptr;
	YTEngine* engine_;

	uint32_t spriteTexture_;
	std::unique_ptr<Sprite> sprite_;
	Transform spriteTransform_;
	Transform spriteUvTransform_;
	Vector4 spriteMaterial_;

	int count;
};