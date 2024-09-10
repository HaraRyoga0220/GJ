#include "Food.h"
#include "ImGuiManager.h"
#include "Mymath.h"
#include"GameUI.h"
#include "GameCommonData.h"
#include <cassert>


void Food::Initialize(
    Model* model, uint32_t textureHandle, uint32_t textureHandle2, uint32_t textureHandle3,uint32_t textureHandle4,uint32_t textureHandle5,uint32_t textureHandle6,GameUI* gameui) {
	assert(model);
	model_ = model;
	gameui_ = gameui;

	//マウスの入力
	input_ = Input::GetInstance();
	//乱数　時刻を入れて初期化
	unsigned int currentTime = (unsigned int)time(nullptr);
	//乱数初期化
	srand(currentTime);

	//鍋に10個の物を入れる
	for (int i = 0; i < 6; i++) {
		GameCommonData::foods[i] = rand() % foodMax;
	}
	//鍋の中　選択されているもの
	GameCommonData::selectFood = rand() % 10;
	while (GameCommonData::foods[GameCommonData::selectFood] == -1) {
		GameCommonData::selectFood = rand() % 10;
	}
	//For文の初期化
	for (int i = 0; i < 5; i++) {
		worldTransform_[i].Initialize();
	}

	

	//食べ物のテクスチャ　↓
	//豆腐
	textureHandle_[0] = textureHandle;
	//CD
	textureHandle_[1] = textureHandle2;
	//ドーナッツ
	textureHandle_[2] = textureHandle3;
	//サツマイモ
	textureHandle_[3] = textureHandle4;
	//ラグビー
	textureHandle_[4] = textureHandle5;
	//レンガ
	textureHandle_[5] = textureHandle6;
}

void Food::Update() {

	for(int i=0;i<9;i++){
    if(GameCommonData::foods[i]<=-1){
        GameCommonData::foods[i] =GameCommonData::foods[i+1];
        GameCommonData::foods[i+1]=-1;

    }
}
if(GameCommonData::foods[1]<=-1){
GameCommonData::foods[1] = rand()%foodMax;
}

	//カメラが鍋に向いているときに
	

	if (mode == 1) {	
	//
		/*for (int i = 0; i < 10; i++) {
			if (GameCommonData::foods[i] == -1) {
				GameCommonData::foods[i] = GameCommonData::foods[i + 1];
				GameCommonData::foods[i + 1] = -1;
			}
		}
		if (GameCommonData::foods[0] == -1) {
				eatFlag = 0;
		} else if (eatFlag != 2) {
			    eatFlag = 1;
		}
		*/

		//選択した値が-1 の時に　再抽選
		while (GameCommonData::foods[GameCommonData::selectFood] == -1 && GameCommonData::eatFlag == 1) {
			GameCommonData::selectFood = rand() % 10;
		}
		//混ぜる　処理　↓
		//クリックされたときに食べ物を鍋の中に入れる
		if (takeFlag == 1 && worldTransform_[0].translation_.y > 0) {
			worldTransform_[0].translation_.y -= 0.1f;
			//食べ物をシャッフル　再抽選
			if (worldTransform_[0].translation_.y <= 0) {
				GameCommonData::selectFood = rand() % 10;
				while (GameCommonData::foods[GameCommonData::selectFood] == -1) {
					GameCommonData::selectFood = rand() % 10;
				}
				takeFlag = 0;
			}
		}
		//混ぜる　食べ物を上に表示する処理
		if (takeFlag == 0 && worldTransform_[0].translation_.y < 1.5f) {
			worldTransform_[0].translation_.y += 0.1f;
		}
		//ここまで　↑ 
		

		//食べるが押されたときにタイマーを作動　食べ物を明るく表示する
		if (GameCommonData::eatFlag == 2) {
			eatTimer--;
		}
		if (eatTimer <= 0) {
			GameCommonData::eatFlag = 1;
			eatTimer = 120;
			GameCommonData::foods[GameCommonData::selectFood] = -1;
		}
		

		/*ImGui::Begin("Foods");
		for (int i = 0; i < 10; i++) {
			ImGui::InputInt("i", &GameCommonData::foods[i]);
		}
		ImGui::End();
		ImGui::Text("eatFlag: %d", GameCommonData::eatFlag);
		ImGui::Text("selectFood: %d", GameCommonData::selectFood);*/

		for (int i = 0; i < 5; i++) {
			worldTransform_[i].UpdateMatrix();
		}
		//食べ物を黒く表示
		if (GameCommonData::eatFlag == 1) {
			worldTransform_[0].scale_ = {0.5f, 0.5f, 0.0f};
		}
		//食べ物を明るく表示
		if (GameCommonData::eatFlag == 2) {
			worldTransform_[0].scale_ = {0.5f, 0.5f, 0.001f};
		}
	}

	

	 //ImGui::Text("eatTimer: %d", eatTimer);
}
//初期化
void Food::Start() {
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

void Food::Draw(ViewProjection& viewProjection) {
	//カメラが鍋に向いている時に
	if (mode == 1) {
		for (int i = 0; i < 5; i++) {
			//豆腐
			if (GameCommonData::eatFlag >= 1 && GameCommonData::foods[GameCommonData::selectFood] == 0) {
				model_->Draw(worldTransform_[0], viewProjection, textureHandle_[0]);
			}
			//CD
			if (GameCommonData::eatFlag >= 1 && GameCommonData::foods[GameCommonData::selectFood] == 1) {
				model_->Draw(worldTransform_[0], viewProjection, textureHandle_[1]);
			}
			//ドーナッツ
			if (GameCommonData::eatFlag >= 1 && GameCommonData::foods[GameCommonData::selectFood] == 2) {
				model_->Draw(worldTransform_[0], viewProjection, textureHandle_[2]);
			}
			//サツマイモ
			if (GameCommonData::eatFlag >= 1 && GameCommonData::foods[GameCommonData::selectFood] == 3) {
				model_->Draw(worldTransform_[0], viewProjection, textureHandle_[3]);
			}
			//ラグビー
			if (GameCommonData::eatFlag >= 1 && GameCommonData::foods[GameCommonData::selectFood] == 4) {
				model_->Draw(worldTransform_[0], viewProjection, textureHandle_[4]);
			}
			//レンガ
			if (GameCommonData::eatFlag >= 1 && GameCommonData::foods[GameCommonData::selectFood] == 5) {
				model_->Draw(worldTransform_[0], viewProjection, textureHandle_[5]);
			}
		}
	}
}