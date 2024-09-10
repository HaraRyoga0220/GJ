#include "Object.h"
#include "ImGuiManager.h"
#include "Input.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <cassert>

// コンロ
void Konro::Initialize(Model* model) {
	assert(model);
	model_ = model;
	worldTransformOfKonro_.Initialize();
	input_ = Input::GetInstance();

	worldTransformOfKonro_.translation_ = {0.0f, 0.0f, 0.0f};
	worldTransformOfKonro_.rotation_ = {0.0f, 4.715f, 0.0f};
	worldTransformOfKonro_.scale_ = {1.0f, 1.0f, 1.0f};
}
void Konro::Update() {

	//ImGui::Begin("Konro");
	//ImGui::DragFloat3("tr", &worldTransformOfKonro_.translation_.x, 0.1f);
	//ImGui::DragFloat3("rot", &worldTransformOfKonro_.rotation_.x, 0.1f);
	//ImGui::DragFloat3("sc", &worldTransformOfKonro_.scale_.x, 0.1f);
	//ImGui::End();
	worldTransformOfKonro_.UpdateMatrix();
}
void Konro::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransformOfKonro_, viewProjection);
}

// こたつ
void kotatsu::Initialize(Model* model) {
	assert(model);
	model_ = model;
	worldTransformOfKotatsu_.Initialize();
	input_ = Input::GetInstance();

	worldTransformOfKotatsu_.translation_ = {0.0f, -1.7f, 0.0f};
	worldTransformOfKotatsu_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransformOfKotatsu_.scale_ = {3.0f, 3.0f, 3.0f};
}
void kotatsu::Update() {

	/*ImGui::Begin("kotatsu");
	ImGui::DragFloat3("tr", &worldTransformOfKotatsu_.translation_.x, 0.1f);
	ImGui::DragFloat3("rot", &worldTransformOfKotatsu_.rotation_.x, 0.1f);
	ImGui::DragFloat3("sc", &worldTransformOfKotatsu_.scale_.x, 0.1f);
	ImGui::End();*/
	worldTransformOfKotatsu_.UpdateMatrix();
}
void kotatsu::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransformOfKotatsu_, viewProjection);
}

// 鍋
void Nabe::Initialize(Model* model) {
	assert(model);
	model_ = model;
	worldTransformOfNabe_.Initialize();
	input_ = Input::GetInstance();

	worldTransformOfNabe_.translation_ = {0.0f, 0.0f, 0.0f};
	worldTransformOfNabe_.rotation_ = {0.0f, 1.6f, 0.0f};
	worldTransformOfNabe_.scale_ = {1.0f, 1.0f, 1.0f};
}
void Nabe::Update() {

	//ImGui::Begin("Nabe");
	//ImGui::DragFloat3("tr", &worldTransformOfNabe_.translation_.x, 0.1f);
	//ImGui::DragFloat3("rot", &worldTransformOfNabe_.rotation_.x, 0.1f);
	//ImGui::DragFloat3("sc", &worldTransformOfNabe_.scale_.x, 0.1f);
	//ImGui::End();
	worldTransformOfNabe_.UpdateMatrix();
}
void Nabe::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransformOfNabe_, viewProjection);
}

// デッキ
void deck::Initialize(Model* model) {
	assert(model);
	model_ = model;

	worldTransformOfDeck_.Initialize();
	input_ = Input::GetInstance();

	worldTransformOfDeck_.translation_ = {1.4f, 0.0f, -1.3f};
	worldTransformOfDeck_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransformOfDeck_.scale_ = {0.04f, -0.1f, 0.04f};
}
void deck::Update() {

	//ImGui::Begin("deck");
	//ImGui::DragFloat3("tr", &worldTransformOfDeck_.translation_.x, 0.1f);
	//ImGui::DragFloat3("rot", &worldTransformOfDeck_.rotation_.x, 0.1f);
	//ImGui::DragFloat3("sc", &worldTra*/nsformOfDeck_.scale_.x, 0.1f);
	//ImGui::End();
	worldTransformOfDeck_.UpdateMatrix();
}
void deck::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransformOfDeck_, viewProjection);
}