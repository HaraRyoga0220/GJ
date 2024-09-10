#include "Input.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include"time.h"
#include<stdlib.h>

class GameUI;
// 自キャラ
class Food {
public:
	
	// 初期化
	void Initialize(Model* model, uint32_t textureHandle, uint32_t textureHandle2, uint32_t textureHandle3,uint32_t textureHandle4,uint32_t textureHandle5, uint32_t textutureHandle6,GameUI* gameui_);
	// 更新
	void Update();
	// 描画
	void Draw(ViewProjection& viewProjection);
	//初期化
	void Start();
	//受け渡しエリア
	void SetMode(int SetMode) { mode = SetMode; }
	int GetTakeCount() { return takeCount; }
	void SetTakeCount(int count) { takeCount = count; }
	

	void SetTakeFlag(int SetTakeFlag) { takeFlag = SetTakeFlag; }
	void SetEatTimer(int SetEatTimer) { eatTimer = SetEatTimer; }

	//ここまで　↑
	

	// ワールド変換データ
	WorldTransform worldTransform_[5];
	// 食材モデル
	Model* model_ = nullptr;
	
	//マウス
	void SetMouse(int x, int y) {
		mouseX_ = x;
		mouseY_ = y;
	}


	int mode = 0;
	int type = 0;

	//食べる
	int eatTimer = 120;
	//混ぜる
	int takeFlag = 0;
	int takeCount = 2;
	//鍋の中身
	int foodMax = 6;
	
	int mixedCount = 0;
	//マウス
	int mouseX_ = 0;
	int mouseY_ = 0;

	Input* input_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_[10];

	GameUI* gameui_;
};