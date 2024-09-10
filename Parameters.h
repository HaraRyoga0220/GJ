#include "Input.h"
#include "ImGuiManager.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Sprite.h"
#include "TextureManager.h"
#include "GameCommonData.h"
#include <Fade.h>
#include"Audio.h"

class Parameters {
public:
	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 描画
	void Draw();

	void SetMode(int SetMode) { turnmode = SetMode; }

	int GetHP() { return HP; }
	int GetSatietyLevel() { return satietylevel; }
	int GetMode() { return turnmode; }

	void SetHP(int setHp) { HP = setHp; }
	void SetSatietyLevel(int setsatietylevel) { satietylevel = setsatietylevel; }

	void SetArray(int SetArray) { array[5] = SetArray;}
	void SetNumberTex(int SetNumberTex) { numberTex[10] = SetNumberTex;}

	int GetArray() { return array[5]; }
	int GetNumberTex() { return numberTex[10]; }

	void Start();

	void Move();

private:
	// ワールド変換データ
	WorldTransform worldTransform_[10];
	Audio* damageSe_ = nullptr;
	// モデル
	Input* move_ = nullptr;
	Input* input_ = nullptr;
	TextureManager* textureManager_;
	uint32_t textureHandleNumber_ = 0;


	int turnmode = 0;

	int Timer = 0;

	int HP = 10;
	int satietylevel = 10;
	int turn = 1;
	
	//ダメージ
	uint32_t GameDataHandleDamageSE_ = 0;
	uint32_t DamageSE_ = 0;

	int black;
	int black2;
	int hp;
	int hv;
	int tn;
	int array[4] = {0};
	int number = 0;
	int drawNumber;
	int numberTex[10];
	int eachNumber[5] = {};
	int mouseX_ = 0;
	int mouseY_ = 0;
	std::unique_ptr<Fade>fade_;

	//テクスチャハンドル
	Sprite* satietylevel_ = nullptr;
	Sprite* hitpoint_ = nullptr;
	Sprite* paramate_ = nullptr;
	Sprite* sprite_[10];
	Sprite* turn_ = nullptr;
	Sprite* black_ = nullptr;
	Sprite* black2_ = nullptr;
};
