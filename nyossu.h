#include "Input.h"
#include "ImGuiManager.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Sprite.h"
#include "TextureManager.h"
#include "GameCommonData.h"


class nyossu {
public:
	// 初期化
	void Initialize();



	// 描画
	void Draw();



private:
	// ワールド変換データ
	WorldTransform worldTransform_[10];
	// モデル
	Input* move_ = nullptr;
	Input* input_ = nullptr;
	TextureManager* textureManager_;
	uint32_t textureHandleNumber_ = 0;
	

	int black;
	int black2;
	int black3;
	

	//テクスチャハンドル
	
	Sprite* black_ = nullptr;
	Sprite* black2_ = nullptr;
	Sprite* black3_ = nullptr;
};
