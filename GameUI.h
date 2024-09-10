#pragma once

#include "Input.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include"time.h"
#include<stdlib.h>
#include <Audio.h>
#include"Sprite.h"


class Food;
class Card2;
// 自キャラ
class GameUI {
public:
	// 初期化
	void Initialize(
	    Model* model, uint32_t textureHandleShake, uint32_t textureHandleEat,
	    uint32_t textureHandleTurnend,uint32_t textureHandleHelp, Food* food, Card2* card2);

	// 更新
	void Update();

	// 描画
	void Draw(ViewProjection& viewProjection);

	void Start();

	void TurnEnd();

	void Eat();

	void Shake();

	void Take();

	void Rule();

	void SetMode(int SetMode) { mode = SetMode; }
	void SetCardFlag(int SetCardFlag) { cardFlag = SetCardFlag; }
	void SetTakeFlag(int SetTakeFlag) { takeFlag = SetTakeFlag; }
	void SetEatTimer(int SetEatTimer) { eatTimer = SetEatTimer; }
	void SetTakeCount(int SetTakeCount) { takeCount = SetTakeCount; }
	void SetMouse(int x, int y) {
		mouseX_ = x;
		mouseY_ = y;
	}
	
	// ワールド変換データ
	WorldTransform worldTransform_[5];
	// モデル
	Model* model_ = nullptr;
	Audio* drawSe_ = nullptr;
	Audio* eatSe_ = nullptr;

	// カメラから受け渡し　モード
	int mode = 0;
	

	int mouseX_ = 0;
	int mouseY_ = 0;

	// カードの処理　ここから↓
	int select = 0;
	int cardFlag = 0;
	// ここまで　↑

	int eatTimer = 120;
	int takeCount = 2;
	int takeFlag = 0;
	//クールタイム
	int culltime = 120;
	int turnEndFlag = 0;

	Input* input_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandleShake_ = 0u;
	uint32_t textureHandleEat_ = 0u;
	uint32_t textureHandleTurnend_ = 0u;
	uint32_t textureHandleHelp_ = 0u;

	//カードを引く効果音
	uint32_t DrawHandleSE_ = 0;
	uint32_t DrawSE_ = 0;

	//咀嚼音
	uint32_t GameDataHandleEatSE_ = 0;
	uint32_t EatSE_ = 0;


	Food* food_;
	Card2* card2_;

	private:
	int rule;
	Sprite* rule_ = nullptr;
};