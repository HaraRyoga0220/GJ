#include "Parameters.h"
#include "ImGuiManager.h"
#include "Mymath.h"
#include <cassert>

void Parameters::Initialize() {
	
	input_ = Input::GetInstance();
	textureManager_ = TextureManager::GetInstance();

	/*black = TextureManager::Load("nyossu.png");
	black2 = TextureManager::Load("nyossu.png");*/
	hp = TextureManager::Load("HP.png");
	hv = TextureManager::Load("HV.png");
	tn = TextureManager::Load("turn.png");
	numberTex[0] = TextureManager::Load("number0.png");
	numberTex[1] = TextureManager::Load("number1.png");
	numberTex[2] = TextureManager::Load("number2.png");
	numberTex[3] = TextureManager::Load("number3.png");
	numberTex[4] = TextureManager::Load("number4.png");
	numberTex[5] = TextureManager::Load("number5.png");
	numberTex[6] = TextureManager::Load("number6.png");
	numberTex[7] = TextureManager::Load("number7.png");
	numberTex[8] = TextureManager::Load("number8.png");
	numberTex[9] = TextureManager::Load("number9.png");

	for (int i = 0; i < 6; i++) {
		sprite_[i] = Sprite::Create(numberTex[i], {100.0f, 100.0f}, {1, 1, 1, 1}, {0.5f, 0.5f});
	}

	hitpoint_ = Sprite::Create(hp, {116.0f, 100.0f}, {1, 1, 1, 1}, {0.5f, 0.5f});
	satietylevel_ = Sprite::Create(hv, {226.0f, 100.0f}, {1, 1, 1, 1}, {0.5f, 0.5f});
	turn_ = Sprite::Create(tn, {626.0f, 100.0f}, {1, 1, 1, 1}, {0.5f, 0.5f});
	//black_ = Sprite::Create(black, {116.0f, 100.0f}, {1, 1, 1, 1}, {0.5f, 0.5f});
	//black2_ = Sprite::Create(black, {226.0f, 100.0f}, {1, 1, 1, 1}, {0.5f, 0.5f});

		//ダメージ
	damageSe_ = Audio::GetInstance();
	GameDataHandleDamageSE_ = damageSe_->LoadWave("Audio/Damage.mp3");
}

void Parameters::Update() {

	if (HP > 10) {
		HP = 10;
	}
	if (satietylevel > 10) {
		satietylevel = 10;
	}
	if (HP < 0)
	{
		HP = 0;
	}
	if (satietylevel < 0)
	{
		satietylevel = 0;
	}


	Move();
}
//初期化
void Parameters::Start() {
	HP = 10;
	turn = 1;
	satietylevel = 10;

}

void Parameters::Move() {
		// 空腹度とHPの内部
		if (Input::GetInstance()->IsTriggerMouse(0) && mouseX_ >= 50 && mouseX_ <= 140 &&mouseY_ >= 570 && mouseY_ <= 650) 
	{
		turnmode = 1;
	}
	if (turnmode == 1) {
		Timer++;
		if (Timer >= 120) {
			turn += 1;
			satietylevel -= 2;
			turnmode = 0;
			Timer = 0;
				
			if (satietylevel <= 0) {
				HP -= 2;
			} else {
				HP += 1;
			}
		}
	}
	if (HP <= 0) {
		
		GameCommonData::SceneMode = 2;
	}

		if (GameCommonData::eatFlag == 2 && GameCommonData::mode ==0) {
		//豆腐
		if (GameCommonData::foods[GameCommonData::selectFood] ==0) {
			satietylevel += 4;
			GameCommonData::mode = 1;
		}
		//CD
		if (GameCommonData::foods[GameCommonData::selectFood] ==1) {
			
			DamageSE_ = damageSe_->PlayWave(GameDataHandleDamageSE_, false);HP -= 2;
			satietylevel += 2;
			GameCommonData::mode = 1;
		}
		//ドーナツ
		if (GameCommonData::foods[GameCommonData::selectFood] ==2) {
			HP += 3;
			satietylevel += 4;
			GameCommonData::mode = 1;
		}
		//サツマイモ
		if (GameCommonData::foods[GameCommonData::selectFood] ==3) {
			satietylevel += 5;
			GameCommonData::mode = 1;
		}
		//ラグビー
		if (GameCommonData::foods[GameCommonData::selectFood] ==4) {
			DamageSE_ = damageSe_->PlayWave(GameDataHandleDamageSE_, false);
			HP -= 4;
			satietylevel += 3;
			GameCommonData::mode = 1;
		}
		//レンガ
		if (GameCommonData::foods[GameCommonData::selectFood] == 5) {
			DamageSE_ = damageSe_->PlayWave(GameDataHandleDamageSE_, false);
			HP -= 5;
			satietylevel += 4;
			GameCommonData::mode = 1;
		}
		}

		

	Vector2 mousePosition = input_->GetMousePosition();
	mouseX_ = (int)mousePosition.x;
	mouseY_ = (int)mousePosition.y;


	

	//HPの10の位
	int h = HP;
	array[0] = (h % 10);
	h /= 10;
	if (h > 0) {
		
	//HPの1の位
		array[1] = (h % 10);
		h /= 10;
	} else {
		array[1] = 0;
	}

	//空腹度の10の位
	int s = satietylevel;
	array[2] = (s % 10);
	s /= 10;
	if (s > 0) {

	//空腹度の1の位
		array[3] = (s % 10);
		s /= 10;
	} else {
		array[3] = 0;
	}
	//ターン10の位
	int d = turn;
	array[4] = (d % 10);
	d /= 10;
	if (d > 0) {

	//ターン1の位
		array[5] = (d % 10);
		d /= 10;
	} else {
		array[5] = 0;
	}

	
}

void Parameters::Draw() { 
	//HPの画像
		hitpoint_->SetSize({128, 128});
	    hitpoint_->SetTextureHandle(hp);
	    hitpoint_->Draw();
	//空腹度の画像
		satietylevel_->SetSize({128, 128});
	    satietylevel_->SetTextureHandle(hv);
	    satietylevel_->Draw();
	//ターンの文字
		turn_->SetSize({128, 80});
		turn_->SetTextureHandle(tn);
		turn_->Draw();
	
	//HPの１０の位
		sprite_[0]->SetSize({32, 64});
		sprite_[0]->SetTextureHandle(numberTex[array[1]]);
		sprite_[0]->Draw();
	//HPの１の位
	    sprite_[1]->SetSize({32, 64});
	    sprite_[1]->SetPosition({132, 100});
	    sprite_[1]->SetTextureHandle(numberTex[array[0]]);
	    sprite_[1]->Draw();
	//空腹度の１０の位
		 sprite_[2]->SetSize({32, 64});
	    sprite_[2]->SetPosition({232, 100});
	    sprite_[2]->SetTextureHandle(numberTex[array[2]]);
	    sprite_[2]->Draw();
	//空腹度の１の位
		sprite_[3]->SetSize({32, 64});
	    sprite_[3]->SetPosition({200, 100});
	    sprite_[3]->SetTextureHandle(numberTex[array[3]]);
	    sprite_[3]->Draw();
	//ターンの10の位
		sprite_[4]->SetSize({32, 64});
	    sprite_[4]->SetPosition({740, 100});
	    sprite_[4]->SetTextureHandle(numberTex[array[4]]);
	    sprite_[4]->Draw();
	//ターンの1の位
		sprite_[5]->SetSize({32, 64});
	    sprite_[5]->SetPosition({700, 100});
	    sprite_[5]->SetTextureHandle(numberTex[array[5]]);
	    sprite_[5]->Draw();

		if (GameCommonData::SceneMode == 2) {

		// ターンの10の位
		sprite_[4]->SetSize({32, 64});
		sprite_[4]->SetPosition({740, 300});
		sprite_[4]->SetTextureHandle(numberTex[array[4]]);
		sprite_[4]->Draw();
		// ターンの1の位
		sprite_[5]->SetSize({32, 64});
		sprite_[5]->SetPosition({700, 300});
		sprite_[5]->SetTextureHandle(numberTex[array[5]]);
		sprite_[5]->Draw();
	    };
		
}