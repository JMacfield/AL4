#pragma once

#include "Iscene.h"
#include "EngineManager/Input/Input.h"

#include "3D/Model.h"
#include "3D/WorldTransform.h"

class TitleScene : public Iscene {
public:
	~TitleScene()override;
	 
	void Initialize() override;

	 void Update() override;

	 void Draw() override;
	
	 void Finalize()override;

private:
	YTEngine* engine_;
	DirectXCommon* directXCommon_;
	TextureManager* textureManager_;
	Input* input_;
	ViewProjection viewProjection_;

	Input* input = nullptr;
	int count;

	std::unique_ptr<Model> planeModel_;
	WorldTransform planeTransform;
};