#include "TitleScene.h"
#include "EngineBase/ImGuiManager.h"

TitleScene::~TitleScene()
{
}
void TitleScene::Initialize()
{	
	engine_ = YTEngine::GetInstance();

	directXCommon_ = DirectXCommon::GetInstance();

	textureManager_ = TextureManager::GetInstance();

	viewProjection_.Initialize();
	viewProjection_.translation_ = { 0.0f,0.0f,-5.0f };

	input = Input::GetInstance();
	count = 0;

	planeModel_.reset(Model::CreateModelFromFile("Resource/Plane", "plane.obj"));
	planeModel_->SetColor({ 1.0f,1.0f,1.0f,1.0f });

	planeTransform.Initialize();
	planeTransform.scale_ = { 36.9f,20.8f,5.0f };
	planeTransform.rotation_ = { 0.0f,0.0f,3.14f };
	planeTransform.translation_ = { 0.0f,0.0f,0.0f };

}

void TitleScene::Update()
{

	ImGui::Begin("Debug");
	ImGui::DragFloat3("PlaneScale", &planeTransform.scale_.x, 0.1f);
	ImGui::DragFloat3("PlaneTranslate", &planeTransform.translation_.x, 0.1f);
	ImGui::DragFloat3("PlaneRotate", &planeTransform.rotation_.x, 0.01f);
	ImGui::End();

	ImGui::Begin("SceneManager");
	ImGui::InputInt("SceneNum", &sceneNum);
	ImGui::Text("count %d",count);
	ImGui::End();

	ImGui::Begin("TITLE");
	ImGui::Text("Push to A to Start");
	ImGui::End();

	if (input->PushKey(DIK_SPACE)) {
		sceneNum = GAME_SCENE;
		count++;
	}
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

	planeTransform.UpdateMatrix();
}

void TitleScene::Draw()
{
	engine_->ModelPreDraw();

	planeModel_->Draw(planeTransform, viewProjection_);
}

void TitleScene::Finalize()
{
}
