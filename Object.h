#pragma once
#include "Input.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class Konro {
public:
	// 初期化
	void Initialize(Model* model);

	// 更新
	void Update();

	void Draw(const ViewProjection& viewProjection);

private:
	// ワールド変換
	WorldTransform worldTransformOfKonro_;
	// モデル
	Model* model_ = nullptr;

	Input* input_ = nullptr;
};

class kotatsu {
public:
	// 初期化
	void Initialize(Model* model);

	// 更新
	void Update();

	void Draw(const ViewProjection& viewProjection);

private:
	// ワールド変換
	WorldTransform worldTransformOfKotatsu_;
	// モデル
	Model* model_ = nullptr;

	Input* input_ = nullptr;
};

class Nabe {
public:
	// 初期化
	void Initialize(Model* model);

	// 更新
	void Update();

	void Draw(const ViewProjection& viewProjection);

private:
	// ワールド変換
	WorldTransform worldTransformOfNabe_;
	// モデル
	Model* model_ = nullptr;

	Input* input_ = nullptr;
};

class deck {
public:
	// 初期化
	void Initialize(Model* model);

	// 更新
	void Update();

	void Draw(const ViewProjection& viewProjection);

private:
	// ワールド変換
	WorldTransform worldTransformOfDeck_;
	// モデル
	Model* model_ = nullptr;

	Input* input_ = nullptr;
};