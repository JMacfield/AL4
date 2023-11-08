#pragma once

#include "DirectXCommon.h"

class ImGuiManger {
public:
	static ImGuiManger* GetInstance();

	void Initialize(WinApp* winApp, DirectXCommon* directXCommon);
	void Draw();
	void Finalize();
		
	void Begin();
	void End();

private:
	DirectXCommon* directXCommon_;
};