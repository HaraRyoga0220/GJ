#include "ImGuiManager.h"
#include "Mymath.h"
#include "haikei.h"
#include <cassert>
void haikei::Initialize(Model* model) {
	assert(model);
	model_ = model;

	worldTransform_.Initialize();
	input_ = Input::GetInstance();

	worldTransform_.translation_ = {0.0f, 0.0f, 0.0};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.scale_ = {-3.0f, -3.0f, -3.0f};
}

void haikei::Update() {
	worldTransform_.UpdateMatrix();	
}

void haikei::Start() {
	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.scale_ = {-3.0f, -3.0f, -3.0f};
}
void haikei::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection);
}
