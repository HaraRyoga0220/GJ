#include "ImGuiManager.h"
#include "Mymath.h"
#include "kotatsu.h"
#include <cassert>
void kotatsu::Initialize(Model* model) {
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	input_ = Input::GetInstance();

	worldTransform_.translation_ = {0.0f, -1.7f, 0.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.scale_ = {3.0f, 3.0f, 3.0f};
}

void kotatsu::Start() {
	worldTransform_.translation_ = {0.0f, -1.7f, 0.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.scale_ = {3.0f, 3.0f, 3.0f};
}

void kotatsu::Update() {

	ImGui::Begin("kotatsu");
	ImGui::DragFloat3("tr", &worldTransform_.translation_.x, 0.1f);
	ImGui::DragFloat3("rot", &worldTransform_.rotation_.x, 0.1f);
	ImGui::DragFloat3("sc", &worldTransform_.scale_.x, 0.1f);
	ImGui::End();
	worldTransform_.UpdateMatrix();
}

void kotatsu::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection);
}