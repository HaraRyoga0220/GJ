#include "GameScene.h"
#include "TextureManager.h"
#include "ImGuiManager.h"
#include <cassert>

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	// ワールド
	worldTransform_.Initialize();
	//カメラ
	viewProjection_.Initialize();
	//カメラ
	viewProjection_.translation_ = {0.0f, 2.0f, -3.0f};
	viewProjection_.rotation_ = {0.6f, 0.0f, 0.0f};
	//背景
	textureHandleTitleBG_ = TextureManager::Load("back.png");
	spriteTBG_ = Sprite::Create(textureHandleTitleBG_, {0, 0});
	//背景
	textureHandleGameOverBG_ = TextureManager::Load("gameover.png");
	spriteOBG_ = Sprite::Create(textureHandleGameOverBG_, {0, 0});
	
	//モデル　↓
	// 鍋
	//Nabe_ = std::make_unique<Nabe>();
	//NabeModel_.reset(Model::CreateFromOBJ("nabe", true));
	//Nabe_->Initialize(NabeModel_.get());
	// こたつ
	//kotatsu_ = std::make_unique<kotatsu>();
	//kotatsuModel_.reset(Model::CreateFromOBJ("kotatsu", true));
	//kotatsu_->Initialize(kotatsuModel_.get());
	// コンロ
	//konro_ = std::make_unique<Konro>();
	//konroModel_.reset(Model::CreateFromOBJ("konro", true));
	//konro_->Initialize(konroModel_.get());
	// デッキ
	/*deck_ = std::make_unique<deck>();
	deckModel_.reset(Model::CreateFromOBJ("deck", true));
	deck_->Initialize(deckModel_.get());*/
	// 和室
	//haikei_ = std::make_unique<haikei>();
	//haikeimodel_.reset(Model::CreateFromOBJ("washitsu", true));
	//haikei_->Initialize(haikeimodel_.get());
	//ここまで　↑
	
	// カメラ
	camera_ = std::make_unique<Camera>();
	camera_->Initialize();
	

	//食材
	textureHandle_ = TextureManager::Load("/TextureFoods/Toufu.png");
	textureHandle2_ = TextureManager::Load("/TextureFoods/CD.png");
	textureHandle3_ = TextureManager::Load("/TextureFoods/Donuts.png");
	textureHandle4_ = TextureManager::Load("/TextureFoods/Imo.png");
	textureHandle5_ = TextureManager::Load("/TextureFoods/Ball.png");
	textureHandle6_ = TextureManager::Load("TextureFoods/Renga.png");

	cardmodel_.reset(Model::Create());
	food_ = std::make_unique<Food>();
	food_->Initialize(
	    cardmodel_.get(), textureHandle_, textureHandle2_, textureHandle3_,textureHandle4_,textureHandle5_,textureHandle6_,gameui_.get());

	// カード
	textureHandle_ = TextureManager::Load("card1.png");
	//まだ使ってない　↓
	textureHandleDonuts_ = TextureManager::Load("cardDonuts.png");
	textureHandleCD_ = TextureManager::Load("cardCD.png");
	textureHandleRenga_ = TextureManager::Load("cardRenga.png");
	textureHandleToufu_ = TextureManager::Load("cardToufu.png");
	textureHandleBall_ = TextureManager::Load("cardBall.png");
	textureHandleImo_ = TextureManager::Load("cardImo.png");

	card2model_.reset(Model::Create());
	card2_ = std::make_unique<Card2>();
	card2_->Initialize(
	    card2model_.get(), textureHandle_, 
		textureHandleToufu_, textureHandleRenga_,
	    textureHandleCD_, textureHandleDonuts_,textureHandleBall_,textureHandleImo_);

	// UI
	textureHandleShake_ = TextureManager::Load("shake.png");
	textureHandleEat_ = TextureManager::Load("taberu.png");
	textureHandleTurnend_ = TextureManager::Load("turnend.png");
	textureHandleHelp_ = TextureManager::Load("Help.png");
	UImodel_.reset(Model::Create());
	gameui_ = std::make_unique<GameUI>();
	gameui_->Initialize(
	    UImodel_.get(), textureHandleShake_, textureHandleEat_, textureHandleTurnend_,textureHandleHelp_,food_.get(), card2_.get());

	
	
	//タイトル											 
	textureHandleTitle_ = TextureManager::Load("Title2.png");
	Titlemodel_.reset(Model::Create());
	Title_ = std::make_unique<Title>();
	Title_->Initialize(cardmodel_.get(), textureHandleTitle_);
	// ゲームオーバー										 
	GameOver = TextureManager::Load("gameover.png");

	//フェード
	textureHandleBlack_ = TextureManager::Load("black.png");
	spriteBlack_.reset(Sprite::Create(textureHandleBlack_, {0, 0}));
	//フェードの生成
	fade_ = std::make_unique<Fade>();
	fade_->Initialize(spriteBlack_.get(),textureHandleBlack_);
	//サウンド
	audio_ = Audio::GetInstance();
	GameDataHandleBGM_ = audio_->LoadWave("Audio/MusMus-BGM-089.wav");
	// パラメータ
	Parameters_ = std::make_unique<Parameters>();
	Parameters_->Initialize();

	// 隠す
	nyossu_ = std::make_unique<nyossu>();
	nyossu_->Initialize();
	
	//クリック画像の点滅
	 titleTimer_ = 0;
	
	
}

void GameScene::Update() {
	switch (GameCommonData::SceneMode) {
	case 0://タイトル
		
	//フェード
	  if (Title_->Update() == true)
	  {
		  fade_->FadeOutStart();
	  }
	  if (fade_->IsEnd() == true) {

	        audio_->StopWave(TitleBGM_);
			Start2();
			GameCommonData::SceneMode = 1u;

			fade_->FadeInStart();
	  }
		// カメラ
		viewProjection_.translation_ = {0.0f, 2.0f, -3.0f};
		viewProjection_.rotation_ = {0.6f, 0.0f, 0.0f};
		viewProjection_.Initialize();
		//初期化
		haikei_->Start();
		food_->Start();
		card2_->Start();
		for (int i = 0; i < 6; i++) {
		GameCommonData::foods[i] = rand() % foodMax;
	}
		
		break;

	case 1://ゲーム

		//モデルアップデート
		Nabe_->Update();
		kotatsu_->Update();
		konro_->Update();
		deck_->Update();
		haikei_->Update();
		Parameters_->Update();
		//ここまで　↑

		//アップデート
		food_->Update();
		card2_->Update();
		gameui_->Update();
		camera_->Update();
		
		//ここまで　↑
		

		//シーン　アップデート
		Title_->Update();

		//ここまで　↑
	

		//マウス　値受け渡し
		card2_->SetMouse(mouseX_, mouseY_);
		food_->SetMouse(mouseX_, mouseY_);
		gameui_->SetMouse(mouseX_, mouseY_);
		//ここまで　↑
		
		
		//モード受け渡し
		gameui_->SetMode(camera_->GetMode());
		food_->SetMode(camera_->GetMode());
		card2_->SetMode(camera_->GetMode());
		//ここまで　↑
		
		gameui_->SetTakeCount(food_->GetTakeCount());
		
		gameui_->SetCardFlag(card2_->GetCardFlag());
	
		
		//カメラ
		viewProjection_.matView = camera_->GetViewProjection().matView;
		viewProjection_.matProjection = camera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();

		case 2://ゲームオーバー
		
		


			break;
	}
	    fade_->Update();
}



void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	
	/// </summary>
	
	switch (GameCommonData::SceneMode) {
	case 0:
		spriteTBG_->Draw();
		break;
	case 1:
	
		break;
	case 2:
		spriteOBG_->Draw();
		break;
	}
	  fade_->Update();

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);


	switch (GameCommonData::SceneMode) {

	case 0:
		Title_->Draw(viewProjection_);
		
		break;

	case 1:
		haikei_->Draw(viewProjection_);
		Nabe_->Draw(viewProjection_);
		kotatsu_->Draw(viewProjection_);
		konro_->Draw(viewProjection_);
		deck_->Draw(viewProjection_);
		food_->Draw(viewProjection_);
		card2_->Draw(viewProjection_);
		gameui_->Draw(viewProjection_);
	
	

		break;

    case 2:
		

		break;
	
	}
	
	  
	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary
	
	switch (GameCommonData::SceneMode) {

	case 0:
		fade_->Draw();
		break;
	case 1:
		Parameters_->Draw();
		gameui_->Rule();
		break;

    case 2:
	    
	
		Parameters_->Draw();
		
		if (GameOver_->Update() == true)
		 {
			GameCommonData::SceneMode = 0u;
		    audio_->StopWave(GameSceneBGM_);
			fade_->FadeInStart();
		  audio_->PlayWave(TitleDataHandleBGM_);
		  
		 }
		
		Parameters_->Start();
		


		 nyossu_->Draw();
		 
    fade_->Update();
	fade_->Draw();
		break;
	}
	
	
	
	
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::Start2() {
	GameSceneBGM_ = audio_->PlayWave(GameDataHandleBGM_, true);

}


