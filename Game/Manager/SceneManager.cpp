#include "Manager/SceneManager.h"
#include "EngineBase/ImGuiManager.h"

SceneManager::SceneManager() {

}

SceneManager::~SceneManager() {
	imguiManager_->Finalize();
	audio_->xAudio2.Reset();
}

void SceneManager::Run() {
	Initialize();

	while (true) {
		// メッセージ処理
		if (winApp_->ProcessMessage()) {
			break;
		}

		imguiManager_->Begin();
        input_->Update();
		glovalVariables_->Update();
		directionalLight_->Update();
		engine_->BeginFrame();
		
		preSceneNumber_ = sceneNumber_;
		sceneNumber_ = sceneArr_[sceneNumber_]->GetSceneNum();

		if (sceneNumber_ != preSceneNumber_) {
			sceneArr_[preSceneNumber_]->Finalize();
			sceneArr_[sceneNumber_]->Initialize();
			
		}
		sceneArr_[sceneNumber_]->Update();
		if (input_->PushKey(DIK_1)) {
			audio_->SoundPlayWave(audio_->xAudio2.Get(), audio_->soundDatas[0]);
		}
		
		sceneArr_[sceneNumber_]->Draw();
		
		imguiManager_->End();
#ifdef _DEBUG
imguiManager_->Draw();
#endif // DEBUG

		engine_->EndFrame();
	}

	CoUninitialize();
	engine_->Finalize();
	sceneArr_[sceneNumber_]->Finalize();
}

void SceneManager::Initialize() {
	CoInitializeEx(0, COINIT_MULTITHREADED);

	engine_ = YTEngine::GetInstance();
	engine_->Initialize( 1280, 720);
	
	winApp_ = WinApp::GetInstance();
    
	input_=Input::GetInstance();
	input_->Initialize(winApp_);
	
	textureManager_ = TextureManager::GetInstance();
	textureManager_->Initialize();
	
	imguiManager_ = ImGuiManger::GetInstance();
	imguiManager_->Initialize(winApp_, engine_->GetDirectXCommon());
	
	glovalVariables_ = GlobalVariables::GetInstance();
	glovalVariables_->LoadFiles();
	
	directionalLight_ = DirectionalLight::GetInstance();
	directionalLight_->Initialize();
	
	sceneArr_[TITLE_SCENE] = std::make_unique <TitleScene>();
	sceneArr_[GAME_SCENE] = std::make_unique <GameScene>();
	sceneNumber_ = TITLE_SCENE;
	sceneArr_[sceneNumber_]->Initialize();
	
	audio_ = Audio::GetInstance();
	audio_->Initialize();
}