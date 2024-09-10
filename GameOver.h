#pragma once
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class GameOver {
public:
	void Initialize(Model* model, uint32_t textureHandleOver);
	bool Update();
	void SetScene(int SetScene) { scene = SetScene; }
	void Draw(ViewProjection& viewProjection);

private:
	WorldTransform worldTransformOver_;
	uint32_t textureHandleOver_ = 0u;
	Input* input_ = nullptr;
	Model* modelOver_ = nullptr;

	int scene = 2;
	int sceneMode_ = 2;


	int timer_ = 0;

		
};
