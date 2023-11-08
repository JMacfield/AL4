#include "EngineBase/ImGuiManager.h"

ImGuiManger* ImGuiManger::GetInstance() {
	static ImGuiManger instance;
	return &instance;
}

void ImGuiManger::Initialize(WinApp* winApp, DirectXCommon* directXCommon) {
	directXCommon_ = directXCommon;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(winApp->GetHwnd());
	ImGui_ImplDX12_Init(directXCommon_->GetDevice().Get(),
		directXCommon_->GetbackBufferCount(),
		directXCommon_->getRtvDesc().Format,
		directXCommon_->GetSrvHeap().Get(),
		directXCommon_->GetSrvHeap()->GetCPUDescriptorHandleForHeapStart(),
		directXCommon_->GetSrvHeap()->GetGPUDescriptorHandleForHeapStart());
}

void ImGuiManger::Finalize() {
	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiManger::Begin() {
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ID3D12DescriptorHeap* descriptorHeaps[] = { directXCommon_->GetSrvHeap().Get()};
	directXCommon_->GetCommandList()->SetDescriptorHeaps(1, descriptorHeaps);
}

void ImGuiManger::End() {
	ImGui::Render();
}

void ImGuiManger::Draw() {
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), directXCommon_->GetCommandList().Get());
}