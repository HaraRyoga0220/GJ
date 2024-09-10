#include "Input.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include"Audio.h"

// 自キャラ
class Card2 {
public:
	// 初期化
	void Initialize(
	    Model* model, uint32_t textureHandle, 
		uint32_t textureHandleCD, uint32_t textureHandleDonuts,
	    uint32_t textureHandleToufu, uint32_t textureHandleRenga,uint32_t textureHandleBall,uint32_t textureHandleImo);

	void Start();
	// 更新
	void Update();

	//移動
	void Move();
	void Use();
	// 描画
	void Draw(ViewProjection& viewProjection);

	void SelectCardWithMouse();
	void SetMouse(int x, int y) {
		mouseX_ = x;
		mouseY_ = y;
	}

	void SetMode(int SetMode) { mode = SetMode; }
	int GetCardFlag() { return cardFlag; }
	void SetCardFlag(int SetCardFlag) { cardFlag = SetCardFlag; }

private:
	// ワールド変換データ
	WorldTransform worldTransform_[4];
	// モデル
	Model* model_ = nullptr;
	//効果音
	Audio* se_ = nullptr;
	//インプット
	Input* input_ = nullptr;
	//モード
	int mode = 0;
	//カードの処理
	int selectedCardIndex_ = -1;
	//int select = 0;
	int cardFlag = 0;
	static const int cardMax = 6;
	//マウス
	int mouseX_ = 0;
	int mouseY_ = 0;

	float speed = 0.04f;

	float cardtimer = 0;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	//食材カード
	uint32_t textureHandleCard_[10] = {0u};

	//カードを引く効果音
	uint32_t DrawHandleSE_ = 0;
	uint32_t DrawSE_ = 0;

	//カードを使う時の効果音
	uint32_t PlayHandleSE_ = 0;
	uint32_t PlaySE_ = 0;

};