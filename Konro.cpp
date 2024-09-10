#include "ImGuiManager.h"
#include "Mymath.h"
#include "Konro.h"
#include <cassert>
void Konro::Initialize(Model* model) {
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	input_ = Input::GetInstance();

	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.rotation_ = {0.0f, 4.715f, 0.0f};
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
}
void Konro::Start() {
	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.rotation_ = {0.0f, 4.715f, 0.0f};
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
}

void Konro::Update() {

	ImGui::Begin("Konro");
	ImGui::DragFloat3("tr", &worldTransform_.translation_.x, 0.1f);
	ImGui::DragFloat3("rot", &worldTransform_.rotation_.x, 0.1f);
	ImGui::DragFloat3("sc", &worldTransform_.scale_.x, 0.1f);
	ImGui::End();
	worldTransform_.UpdateMatrix();
}

void Konro::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection);
}