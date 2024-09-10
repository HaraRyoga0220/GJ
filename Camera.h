#pragma once
#include "Input.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class Camera {
public:
	// 初期化
	void Initialize();

	// 更新
	void Update();
	//
	void Screen();

	void SetMouse(int x, int y) {
		mouseX_ = x;
		mouseY_ = y;
	}

	int GetMode() { return mode; }

	/// <summary>
	/// ビュープロジェクションを取得
	/// </summary>
	/// <returns>ビュープロジェクション</returns>
	const ViewProjection& GetViewProjection() { return viewProjection_; }

private:
	Input* input_ = nullptr;

	int mouseX_ = 0;
	int mouseY_ = 0;
	int mode = 0;
	// カメラ
	ViewProjection viewProjection_;

	float viewSpeed = 0.025f;
};