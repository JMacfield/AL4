#include "ClearScene.h"
#include "EngineBase/ImGuiManager.h"

ClearScene::~ClearScene() {

}

void ClearScene::Initialize() {
	input = Input::GetInstance();
	count = 0;

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
	
}

void ClearScene::Finalize() {

}
