#include "ImGuiManager.h"
#include "Mymath.h"
#include "Food.h"
#include "Card2.h"
#include "GameUI.h"
#include "GameCommonData.h"
#include <cassert>
#include <iostream>
#include <TextureManager.h>
void GameUI::Initialize(
    Model* model, uint32_t textureHandleShake, uint32_t textureHandleEat,
    uint32_t textureHandleTurnend, uint32_t textureHandleHelp,Food* food, Card2*card2) {
	assert(model);
	model_ = model;
	food_ = food;
	card2_ = card2;
	for (int i = 0; i < 3; i++) {
		if (GameCommonData::cards[i] == -1) {
			GameCommonData::cards[i] = rand() % GameCommonData::cardMax;
		}
	}
	unsigned int currentTime = (unsigned int)time(nullptr);
	srand(currentTime);

	for (int i = 0; i < 5; i++) {
		worldTransform_[i].Initialize();
	}

	input_ = Input::GetInstance();
	textureHandleShake_ = textureHandleShake;
	textureHandleEat_ = textureHandleEat;
	textureHandleTurnend_ = textureHandleTurnend;
	textureHandleHelp_ = textureHandleHelp;

	worldTransform_[0].translation_ = {0.0f, 1.5f, -0.5f};
	worldTransform_[0].rotation_ = {0.3f, 0.0f, 0.0f};
	worldTransform_[0].scale_ = {0.5f, 0.5f, 0.0f};

	// 混ぜる
	worldTransform_[1].translation_ = {0.4f, 1.3f, -0.9f};
	worldTransform_[1].rotation_ = {0.8f, 0.0f, 0.0f};
	worldTransform_[1].scale_ = {0.2f, 0.2f, 0.001f};
	// 食べる
	worldTransform_[2].translation_ = {-0.4f, 1.3f, -0.9f};
	worldTransform_[2].rotation_ = {0.8f, 0.0f, 0.0f};
	worldTransform_[2].scale_ = {0.2f, 0.2f, 0.001f};

	// ターン終了
	worldTransform_[3].translation_ = {-1.4f, 0.2f, -1.5f};
	worldTransform_[3].rotation_ = {0.8f, 0.0f, 0.0f};
	worldTransform_[3].scale_ = {0.15f, 0.15f, 0.001f};
	//ヘルプ
    worldTransform_[4].translation_= {1.5f, 0.182f, -1.6f};
	worldTransform_[4].rotation_ = {0.8f, 0.0f, 0.0f};
    worldTransform_[4].scale_ = {0.1f, 0.1f, 0.001f};

	if (card2_->GetCardFlag() == 0) {
				// カードを有効化
			cardFlag = 1;
			card2_->SetCardFlag(cardFlag);
			}
			//混ぜる回数をリセット　二回にセット
			takeCount = 2;
			GameCommonData::eatFlag = 1;
			eatTimer = 120;

			//フードに混ぜる回数の値を渡す
			food_->SetTakeCount(takeCount);
			//カードクラスにカードの有無を渡す
			card2_->SetCardFlag(cardFlag);
	
	//カードを引く時の効果音
	drawSe_ = Audio::GetInstance();
	DrawHandleSE_ = drawSe_->LoadWave("Audio/drawSe.wav");
			
	//咀嚼音
	eatSe_ = Audio::GetInstance();
	GameDataHandleEatSE_ = eatSe_->LoadWave("Audio/get.mp3");


	//ルール
	rule = TextureManager::Load("rule.png");

	rule_ = Sprite::Create(rule, {640.0f, 360.0f}, {1, 1, 1, 0.98f}, {0.5f, 0.5f});
}

void GameUI::Update() {
	Vector2 mousePosition = input_->GetMousePosition();
	mouseX_ = (int)mousePosition.x;
	mouseY_ = (int)mousePosition.y;
	// Imgui　ここから　↓
	/*ImGui::Text("takeCount: %d", takeCount);
	ImGui::Text("cardFlag: %d", cardFlag);
	ImGui::Text("TurnEndFlag: %d",turnEndFlag);*/
	
	// ここまで　↑
	for (int i = 0; i < 5; i++) {
		worldTransform_[i].UpdateMatrix();
	}
	TurnEnd();
	Take();
	Eat();
	Shake();

	
}

//混ぜるを入力された時の処理
void GameUI::Take() {
	if (takeCount <= 0 || GameCommonData::eatFlag== 0) {
		worldTransform_[1].scale_ = {0.2f, 0.2f, 0.0f};
	} else if (takeCount >= 0 ||GameCommonData::eatFlag == 1) {
		worldTransform_[1].scale_ = {0.2f, 0.2f, 0.001f};
	}
	if (GameCommonData::eatFlag == 0) {
		worldTransform_[2].scale_ = {0.2f, 0.2f, 0.0f};
	}
}

void GameUI::Eat() {
	// 食べる　処理↓
	//鍋の画面
	if (mode == 1) {
		//食べれる　EatFlag が　1の時　マウス操作を入力できる
		if (Input::GetInstance()->IsTriggerMouse(0) && mouseX_ >= 340 && mouseX_ <= 530 &&
		    mouseY_ >= 340 && mouseY_ <= 530 && GameCommonData::eatFlag==1) {
			//食べ物を明るく表示しタイマーを起動する
			GameCommonData::eatFlag = 2;
			GameCommonData::mode = 0;
			EatSE_ = eatSe_->PlayWave(GameDataHandleEatSE_, false);
		}
	}
}

void GameUI::Shake() {
	// 混ぜるをクリック
	if (takeCount > 0) {
		if (Input::GetInstance()->IsTriggerMouse(0) && mouseX_ >= 740 && mouseX_ <= 960 &&
		    mouseY_ >= 340 && mouseY_ <= 540) {
			//
			takeFlag = 1;
			takeCount -= 1;
			food_->SetTakeCount(takeCount);
			food_->SetTakeFlag(takeFlag);
		}
	}
}

void GameUI::TurnEnd() {
	// マウスの位置を取る
	Vector2 mousePosition = input_->GetMousePosition();
	mouseX_ = (int)mousePosition.x;
	mouseY_ = (int)mousePosition.y;
	if (mode == 0) {
		// ターン終了
		if (Input::GetInstance()->IsTriggerMouse(0) && mouseX_ >= 50 && mouseX_ <= 140 && mouseY_ >= 570 && mouseY_ <= 650) {
			//カードがない時に
			if (card2_->GetCardFlag() == 0) {
				// カードを有効化
				cardFlag = 1;
				card2_->SetCardFlag(cardFlag);
				DrawSE_ = drawSe_->PlayWave(DrawHandleSE_, false);
			}
			for (int i = 0; i < 3; i++) {
		if (GameCommonData::cards[i] == -1) {
			GameCommonData::cards[i] = rand() % GameCommonData::cardMax;
		}
	}
			//混ぜる回数をリセット　二回にセット
			takeCount = 2;
			GameCommonData::eatFlag = 1;
			eatTimer = 120;

			//フードに混ぜる回数の値を渡す
			food_->SetTakeCount(takeCount);
			//カードクラスにカードの有無を渡す
			card2_->SetCardFlag(cardFlag);
			//カードがあるときに
				for (int i = 0; i < 3; i++) {
					if (GameCommonData::cards[i] == -1) {
						GameCommonData::cards[i] = rand() % GameCommonData::cardMax;
					}
				}
		}
	}
}

void GameUI::Rule() {
	if (Input::GetInstance() && mouseX_ >= 1200 && mouseX_ <= 1265 &&
	    mouseY_ >= 600 && mouseY_ <= 680) {
		rule_->SetSize({1280, 720});
		rule_->SetTextureHandle(rule);
		rule_->Draw();
		}
	}


// 位置初期化
void GameUI::Start() {
	for (int i = 0; i < 3; i++) {
		if (GameCommonData::cards[i] == -1) {
			GameCommonData::cards[i] = rand() % GameCommonData::cardMax;
		}
	}
	    worldTransform_[0].translation_ = {0.0f, 1.5f, -0.5f};
	    worldTransform_[0].rotation_ = {0.3f, 0.0f, 0.0f};
	    worldTransform_[0].scale_ = {0.5f, 0.5f, 0.001f};

	    worldTransform_[1].translation_ = {0.4f, 1.3f, -0.9f};
	    worldTransform_[1].rotation_ = {0.8f, 0.0f, 0.0f};
	    worldTransform_[1].scale_ = {0.2f, 0.2f, 0.001f};

	    worldTransform_[2].translation_ = {-0.4f, 1.3f, -0.9f};
	    worldTransform_[2].rotation_ = {0.8f, 0.0f, 0.0f};
	    worldTransform_[2].scale_ = {0.2f, 0.2f, 0.001f};
}

void GameUI::Draw(ViewProjection& viewProjection) {
	// 画面が上の時に
	if (mode == 1) {
		//混ぜる
		model_->Draw(worldTransform_[1], viewProjection, textureHandleShake_);
		//食べる
		model_->Draw(worldTransform_[2], viewProjection, textureHandleEat_);
	}
	// 画面が下の時に
	if (mode == 0) {
		//ターン終了
		model_->Draw(worldTransform_[3], viewProjection, textureHandleTurnend_);
		//ヘルプ
        model_->Draw(worldTransform_[4], viewProjection, textureHandleHelp_);
	}
}