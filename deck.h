#include "Input.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class deck {
public:
	// 初期化
	void Initialize(Model* model);

	// 更新
	void Update();

	void Start();

	void Draw(const ViewProjection& viewProjection);

private:
	// ワールド変換
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;

	Input* input_ = nullptr;
};
