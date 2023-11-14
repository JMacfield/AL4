#include "WinApp.h"
#include "EngineManager/Icon/Icon.h"

#include <string>

LRESULT  WinApp::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam)) {
		return true;
	}

	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wparam, lparam);
}

void WinApp::CreateGameWindow(const wchar_t* title, int32_t clientWidth, int32_t clientheight) {
	wc_.lpfnWndProc =WindowProc;
	wc_.lpszClassName = L"CG2WINDOWClass";
	wc_.hInstance = GetModuleHandle(nullptr);
	wc_.hCursor = LoadCursor(nullptr, IDC_ARROW);
	
	/*HICON loadedIcon = LoadIcon(wc_.hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wc_.hIcon = loadedIcon;*/

	RegisterClass(&wc_);
	
	AdjustWindowRect(&wrc_, WS_OVERLAPPEDWINDOW, false);
	
	hwnd_ = CreateWindow(
		wc_.lpszClassName,
		title,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,//表示X座標
		CW_USEDEFAULT,//表示Y座標
		wrc_.right - wrc_.left,//ウィンドウ横幅
		wrc_.bottom - wrc_.top,//ウィンドウ縦幅
		nullptr,//親ウィンドウハンドル
		nullptr,//メニューハンドル
		wc_.hInstance,//インスタンスハンドル
		nullptr//オプション
	);

	timeBeginPeriod(1);

#ifdef _DEBUG
     debugController_ = nullptr;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController_)))) {
		//デバッグレイヤーを有効化する
		debugController_->EnableDebugLayer();
		//さらにGPU側でもチェックを行うようにする
		debugController_->SetEnableGPUBasedValidation(true);
	}
#endif  

	ShowWindow(hwnd_, SW_SHOW);
}

WinApp* WinApp::GetInstance() {
	static WinApp instance;
	return &instance;
}

bool WinApp::Procesmessage() {
	MSG msg{};

	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	// 終了メッセージを受けたらループを離脱
	if (msg.message == WM_QUIT) {
		return true;
	}

	return false;
}

void WinApp::Finalize() {
	debugController_->Release();
}