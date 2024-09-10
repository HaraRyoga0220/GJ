#include "GameOver.h"
#include "GameScene.h"
#include "ImGuiManager.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <TextureManager.h>

void GameOver::Initialize(Model* model, uint32_t textureHandleOver) {

	modelOver_ = model;
	input_ = Input::GetInstance();
	textureHandleOver_ = textureHandleOver;

	worldTransformOver_.Initialize();
	worldTransformOver_.translation_ = {0.0f, 2.1f, -1.5f};
	worldTransformOver_.rotation_ = {1.0f,0.0f,0.0f};
	worldTransformOver_.scale_ = {0.5f,0.5f, 0.001f};
	worldTransformOver_.UpdateMatrix();
}

bool GameOver::Update() {

	if (Input::GetInstance()->IsTriggerMouse(0)){



		return true;
	}  
	return false;
}



void GameOver::Draw(ViewProjection& viewProjection) {
	modelOver_->Draw(worldTransformOver_, viewProjection, textureHandleOver_);
}
