#include "TitleScene.h"
#include "EngineBase/ImGuiManager.h"

TitleScene::~TitleScene() {

}

void TitleScene::Initialize() {	
	input = Input::GetInstance();
	count = 0;

}

void TitleScene::Update() {
	XINPUT_STATE joyState;
	
	if (!input->GetJoystickState(0, joyState)) {
		return;
	}
	
	if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A) {
		sceneNum = GAME_SCENE;
	}

	if (sceneNum < 0) {
		sceneNum = 0;
	}

	setlocale(LC_CTYPE, "");
	try {
		// Get
		auto task = Get<json::value>(L"http://localhost:3000/swgames/");
		const json::value j = task.get();
		auto array = j.as_array();
		for (int i = 0; i < j.size(); i++) {
			std::wcout << array[i].at(U("ID")) << std::endl;
		}
	}
	catch (const std::exception& e) {
		printf("Error Exception:%s\n", e.what());
	}
}

void TitleScene::Draw() {
	ImGui::Begin("TITLE");
	ImGui::Text("Push to A to Start");
	ImGui::End();
}

void TitleScene::Finalize() {

}
