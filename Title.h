#pragma once
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include"Audio.h"

class Title {
public:
	void Initialize(Model* model, uint32_t textureHandleTitle);
	bool Update();
	void SetScene(int SetScene) { scene = SetScene; }
	void Draw(ViewProjection& viewProjection);

	void Start();
	void End();
	void SetMouse(int x, int y) {
		mouseX_ = x;
		mouseY_ = y;
	}
private:
	WorldTransform worldTransform_;
	uint32_t textureHandleTitle_ = 0u;
	Input* input_ = nullptr;
	Model* model_ = nullptr;

	Sprite* fadeSprite_ = nullptr;
	Sprite* fadeSprite2_ = nullptr;
	Vector4 fadeColor_ = {1.0f, 1.0f, 1.0f, 1.0f};

	int mouseX_;
	int mouseY_;
	int scene = 0;

	uint32_t timer_ = 0;

	//サウンド
	Audio* audio_ = nullptr;
	uint32_t TitleDataHandleBGM_ = 0;
	uint32_t TitleBGM_ = 0;
};
