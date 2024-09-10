#include "Camera.h"
#include "ImGuiManager.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <cassert>

void Camera::Initialize() {
	input_ = Input::GetInstance();
	viewProjection_.Initialize();
	viewProjection_.translation_ = {0.0f, 2.0f, -3.0f};
	viewProjection_.rotation_ = {0.6f, 0.0f, 0.0f};
}

void Camera::Update() {
	Vector2 mousePosition = input_->GetMousePosition();
	mouseX_ = (int)mousePosition.x;
	mouseY_ = (int)mousePosition.y;
	Screen();
	if (mode == 1) {
		if (viewProjection_.rotation_.x <= 0.75f) {
			viewProjection_.rotation_.x += viewSpeed;
		}
		if (viewProjection_.translation_.y <= 2.5f) {
			viewProjection_.translation_.y += viewSpeed;
		}
		if (viewProjection_.translation_.z <= -2.0f) {
			viewProjection_.translation_.z += viewSpeed * 2;
		}

		viewProjection_.UpdateMatrix();
	} else if (mode == 0) {
		if (viewProjection_.rotation_.x >= 0.6f) {
			viewProjection_.rotation_.x -= viewSpeed;
		}
		if (viewProjection_.translation_.y >= 2.0f) {
			viewProjection_.translation_.y -= viewSpeed;
		}
		if (viewProjection_.translation_.z >= -3.0f) {
			viewProjection_.translation_.z -= viewSpeed * 2;
		}
		viewProjection_.UpdateMatrix();
	}
}

void Camera::Screen() {

	if (mouseY_ <= 200) {
		mode = 1;
	}
	// マウスが下の時に
	else if (mouseY_ >= 550) {
		// カード画面になる
		mode = 0;
	}
}