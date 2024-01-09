#include "TitleScene.h"
#include "EngineBase/ImGuiManager.h"

TitleScene::~TitleScene() {

}

void TitleScene::Initialize() {	
	input = Input::GetInstance();
	count = 0;

}

void TitleScene::Update() {
	
	
	
	
	if (input->PressKey(DIK_SPACE)) {
		sceneNum = GAME_SCENE;
	}


	if (sceneNum < 0) {
		sceneNum = 0;
	}
}

void TitleScene::Draw() {
	ImGui::Begin("TITLE");
	ImGui::Text("Push to A to Start");
	ImGui::End();
}

void TitleScene::Finalize() {

}
