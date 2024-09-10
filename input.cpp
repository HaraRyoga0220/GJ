#include "Input.h"

#include <cassert>
#include <vector>

#include "ImGuiManager.h"
#include "WinApp.h"

// Input* Input::GetInstance() {
//	static Input instans;
//	return &instans;
// }

// void Input::Initialize() {
//	HRESULT result = S_FALSE;
// #pragma region DirectInputオブジェクトの生成
//	// DirectInputオブジェクトの生成
//	result = DirectInput8Create(
//	    WinApp::GetInstance()->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8,
//	    reinterpret_cast<void**>(dInput_.GetAddressOf()), nullptr);
//	assert(SUCCEEDED(result));
// #pragma endregion DirectInputオブジェクトの生成
//
// #pragma region キーボード設定
//	// キーボードデバイスの生成
//	result = dInput_->CreateDevice(GUID_SysKeyboard, &devKeyboard_, NULL);
//	assert(SUCCEEDED(result));
//
//	// 入力データ形式のセット(キーボード)
//	result = devKeyboard_->SetDataFormat(&c_dfDIKeyboard); // 標準形式
//	assert(SUCCEEDED(result));
//
//	// 排他制御レベルのセット
//	result = devKeyboard_->SetCooperativeLevel(
//	    WinApp::GetInstance()->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
//	assert(SUCCEEDED(result));
// #pragma endregion キーボード設定
//
// #pragma region マウス設定
//	// マウスデバイスの生成
//	result = dInput_->CreateDevice(GUID_SysMouse, &devMouse_, NULL);
//	assert(SUCCEEDED(result));
//
//	// 入力データ形式のセット
//	result = devMouse_->SetDataFormat(&c_dfDIMouse); // マウス用のデータ・フォーマットを設定
//	assert(SUCCEEDED(result));
//
//	// 排他制御レベルのセット
//	result = devMouse_->SetCooperativeLevel(
//	    WinApp::GetInstance()->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
//	assert(SUCCEEDED(result));
// #pragma endregion マウス設定
// #pragma region ジョイスティック
//	/*result = dInput_->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, this,
//	DIEDFL_ATTACHEDONLY); assert(SUCCEEDED(result));*/
//
//	// XInput 初期化
//	for (DWORD i = 0; i < XUSER_MAX_COUNT; ++i) {
//		Joystick joystick;
//		joystick.type_ = PadType::XInput;
//		joystick.device_ = nullptr; // XInput では DirectInput デバイスは使用しない
//		devJoysticks_.push_back(joystick);
//	}
// #pragma endregion
// }

// void Input::Update() {
//	devKeyboard_->Acquire(); // キーボード動作開始
//	devMouse_->Acquire();    // マウス動作開始
//	 前回のキー入力を保存
//	keyPre_ = key_;
//
//	mousePre_ = mouse_;
//
//	 キーの入力
//	devKeyboard_->GetDeviceState((DWORD)size(key_), key_.data());
//
//	 マウスの入力
//	devMouse_->GetDeviceState(sizeof(DIMOUSESTATE), &mouse_);
// }

bool Input::PushMouse(int32_t keyNumber) const {
	if (mouse_.rgbButtons[keyNumber]) {
		return true;
	}

	// 押していない
	return false;
}

bool Input::TriggerMouse(int32_t keyNumber) const {
	// 前回が0で、今回が0でなければトリガー
	if (!mousePre_.rgbButtons[keyNumber] && mouse_.rgbButtons[keyNumber]) {
		return true;
	}
	// トリガーでない
	return false;
}

bool Input::ExitMouse(int32_t keyNumber) const {
	// 前回が0ではなくて、今回が0
	if (mousePre_.rgbButtons[keyNumber] && !mouse_.rgbButtons[keyNumber]) {
		return true;
	}
	return false;
}

// int32_t Input::GetWheel() const { return static_cast<int32_t>(mouse_.lZ); }

Vector2 Input::GetMouseMove() const { return {(float)mouse_.lX, (float)mouse_.lY}; }
