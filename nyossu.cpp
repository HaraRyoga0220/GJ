#include "nyossu.h"
#include "ImGuiManager.h"
#include "Mymath.h"
#include <cassert>

void nyossu::Initialize() {
	
	input_ = Input::GetInstance();
	textureManager_ = TextureManager::GetInstance();

	black = TextureManager::Load("nyossu.png");
	black2 = TextureManager::Load("nyossu.png");
	black3 = TextureManager::Load("nyossu.png");
	
	black_ = Sprite::Create(black, {116.0f, 100.0f}, {1, 1, 1, 1}, {0.5f, 0.5f});
	black2_ = Sprite::Create(black, {226.0f, 90.0f}, {1, 1, 1, 1}, {0.5f, 0.5f});
	black3_ = Sprite::Create(black, {626.0f, 90.0f}, {1, 1, 1, 1}, {0.5f, 0.5f});
}



void nyossu::Draw() { 
	
		//隠す
		black_->SetSize({128, 128});
		black_->SetTextureHandle(black);
		black_->Draw();
		//隠す2
		black2_->SetSize({128, 128});
		black2_->SetTextureHandle(black);
		black2_->Draw();
		//隠す3
		black3_->SetSize({128, 128});
		black3_->SetTextureHandle(black);
		black3_->Draw();


}
