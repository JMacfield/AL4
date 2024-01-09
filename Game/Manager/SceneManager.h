#pragma once

#pragma region エンジン
#include "EngineBase/YTEngine.h"
#include "EngineManager/Input/Input.h"
#include "EngineManager/Input/Input.h"
#include "EngineManager/Audio/Audio.h"
#include "EngineManager/GlobalVariables/GlobalVariables.h"
#include "EngineBase/ImGuiManager.h"
#include "EngineManager/Light/DirectionalLight.h"
#pragma endregion

#pragma region シーン
#include <Scene/Iscene.h>
#include <Scene/GameScene.h>
#include <Scene/TitleScene.h>
#include <Scene/ClearScene.h>
#pragma endregion

class SceneManager {
public:
	SceneManager();
	~SceneManager();

	void Initialize();
	void Run();
	
private:
	YTEngine* engine_;
	WinApp* winApp_ = nullptr;
	Input* input_ ;
	TextureManager* textureManager_;
	
	Audio* audio_;
	std::unique_ptr<Iscene> sceneArr_[3];
	
	GlobalVariables* glovalVariables_;
	ImGuiManger* imguiManager_;
	DirectionalLight* directionalLight_;
	
	int sceneNumber_;
	int preSceneNumber_;
};