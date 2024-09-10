#include "ImGuiManager.h"
#include "Mymath.h"
#include "Card2.h"
#include"Food.h"
#include "GameCommonData.h"
#include <iostream>
#include <cassert>

void Card2::Initialize(
    Model* model, uint32_t textureHandle, uint32_t textureHandleCD, uint32_t textureHandleDonuts,
    uint32_t textureHandleToufu, uint32_t textureHandleRenga,uint32_t textureHandleBall,uint32_t textureHandleImo) {
	assert(model);
	model_ = model;
	input_ = Input::GetInstance();

	unsigned int currentTime = (unsigned int)time(nullptr);
	srand(currentTime);
	for (int i = 0; i < 3; i++) {
		worldTransform_[i].Initialize();
	}

	//カード　↓
	textureHandle_ = textureHandle;
	//カードテクスチャ
	textureHandleCard_[0] = textureHandleToufu;
	textureHandleCard_[1] = textureHandleRenga;
	textureHandleCard_[2] =  textureHandleCD;
	textureHandleCard_[3] = textureHandleDonuts;
	textureHandleCard_[4] = textureHandleBall;
	textureHandleCard_[5] = textureHandleImo;
	//ここまで　↑


	//カードの位置　↓
	//左
	worldTransform_[0].translation_ = {1.4f, 0.9f, -1.98f};
	worldTransform_[0].rotation_ = {0.9f, 0.0f, 0.0f};
	worldTransform_[0].scale_ = {0.18f, 0.25f, 0.0001f};
	//真ん中
	worldTransform_[1].translation_ = {1.4f, 0.9f, -1.98f};
	worldTransform_[1].rotation_ = {0.9f, 0.0f, 0.0f};
	worldTransform_[1].scale_ = {0.18f, 0.25f, 0.0001f};
	//右
	worldTransform_[2].translation_ = {1.4f, 0.9f, -1.98f};
	worldTransform_[2].rotation_ = {0.9f, 0.0f, 0.0f};
	worldTransform_[2].scale_ = {0.18f, 0.25f, 0.0001f};
	//ここまで　↑

	

	
	//カードを使う時の効果音
	se_ = Audio::GetInstance();
	PlayHandleSE_ = se_->LoadWave("Audio/playSe.wav");
}

void Card2::Update() {
	//ImGui::Text("select: %d" ,selectedCardIndex_);
	//ImGui::Text("Mouse Position: %d, %d", mouseX_, mouseY_);
	//マウスの位置を取る
		Vector2 mousePosition = input_->GetMousePosition();
	    mouseX_ = (int)mousePosition.x;
		mouseY_ = (int)mousePosition.y;
	 // マウスでカードを選択
	SelectCardWithMouse();
	Move();
	Use();


}

//カードを使う
void Card2::Use() {
	if (mode == 0) {
		//カードがある時
		if (cardFlag == 1) {
			// カードをクリックした時
			if (Input::GetInstance()->IsTriggerMouse(0)&&selectedCardIndex_ >= -1) {
				for (int i = 0; i < 10; i++) {
					if (GameCommonData::foods[i] == -1) {
						worldTransform_[selectedCardIndex_].translation_.x = 4.0f;
						GameCommonData::foods[i] =
						    GameCommonData::cards[selectedCardIndex_];
						GameCommonData::cards[selectedCardIndex_] = -1;
						
						// カードを消す
						 {
							cardFlag = 0;

						}
					}
				}
			}
		}
	}
}

//カードを座標にもっていく
void Card2::Move() {
	
	// ターン終了が実行されたらカードを座標まで持っていく
	for (int i = 0; i < 3; i++) {
		if (cardFlag == 1 ) {
			if (worldTransform_[i].translation_.x >= -0.4f + i * 0.4) {
				worldTransform_[i].translation_.x -= speed;
			}
		}
	}
}

	// 初期値に戻す
	void Card2::Start() {
		worldTransform_[0].translation_ = {1.4f, 0.9f, -1.98f};
		worldTransform_[0].rotation_ = {0.9f, 0.0f, 0.0f};
		worldTransform_[0].scale_ = {0.18f, 0.25f, 0.0001f};

		worldTransform_[1].translation_ = {1.4f, 0.9f, -1.98f};
		worldTransform_[1].rotation_ = {0.9f, 0.0f, 0.0f};
		worldTransform_[1].scale_ = {0.18f, 0.25f, 0.0001f};

		worldTransform_[2].translation_ = {1.4f, 0.9f, -1.98f};
		worldTransform_[2].rotation_ = {0.9f, 0.0f, 0.0f};
		worldTransform_[2].scale_ = {0.18f, 0.25f, 0.0001f};
	}

void Card2::SelectCardWithMouse() {
	// マウスの座標を取得
	 Vector2 mousePosition = input_->GetMousePosition();
	 mouseX_ = (int)mousePosition.x;
	 mouseY_ = (int)mousePosition.y;
	 selectedCardIndex_ = -1;
	//カード選択
	if (mouseX_ >= 270 && mouseX_ <= 470) {
		selectedCardIndex_ = 0;
	}
	if (mouseX_ >= 510 && mouseX_ <= 720) {
		selectedCardIndex_ = 1;
	}
	if (mouseX_ >= 740 && mouseX_ <= 950) {
		selectedCardIndex_ = 2;
	}

	//カードを選択しているかの判定
	for (int i = 0; i < 3; i++) {
		worldTransform_[i].UpdateMatrix();
		// カードが選択されている場合、位置を少し上にずらす
		if (i == selectedCardIndex_) {
			    worldTransform_[i].translation_.y = 1.0f;
			    //select = i; // ずらす距離を調整する
		} else if (i != selectedCardIndex_) {
			    worldTransform_[i].translation_.y = 0.9f;
		}
	}
}


void Card2::Draw(ViewProjection& viewProjection) {
	//カード描画
	for (int i = 0; i < 3; i++) {
		if (GameCommonData::cards[i] >= 0 && GameCommonData::cards[i]>=0) {
		model_->Draw(worldTransform_[i], viewProjection,textureHandleCard_[GameCommonData::cards[i]]);
		}
	}
}