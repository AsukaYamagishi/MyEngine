#include "TitleScene.h"
#include <cassert>
#include "../Input/KeyboardInput.h"
#include "../Input/ControllerInput.h"
#include "../Manager/SceneManager.h"

using namespace DirectX;

TitleScene::TitleScene(DirectXCommon* dxCommon, Audio* audio)
{
#pragma region nullptrチェック/代入
	assert(dxCommon);
	assert(audio);

	this->dxCommon = dxCommon;
	this->audio = audio;
#pragma endregion
}

TitleScene::~TitleScene()
{
	//safe_deleteはここで行う
}

void TitleScene::Init()
{


#pragma region Sprite初期設定
	// テクスチャ読み込み(１番にするとよくわからんエラー起こる)
	if (!Sprite::LoadTexture(2, L"Resources/Title.png")) {
		assert(0);
		return;
	}
	//// 背景スプライト生成
	spriteBG = Sprite::CreateSprite(2, { 0.0f,0.0f });
#pragma endregion


#pragma region 3DモデルCreate・初期設定
#pragma endregion
	
#pragma region 音楽リソース初期設定
#pragma endregion
}

void TitleScene::Update()
{
	//特定キーによりゲームプレイに移動（後ほどゲームセレクトへ変更）
	if (KeyboardInput::GetIns()->PressKeyTrigger(DIK_SPACE)
		|| ControllerInput::GetIns()->IsPadButtonTrigger(XBOX_INPUT_B))
	{
		SceneManager::ChangeScene(SceneManager::GAMEPLAY);
	}
}

void TitleScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);

	// 背景スプライト描画
	spriteBG->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();

	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	//CalculationObject::PreDraw(cmdList);

	// 3Dオブクジェクトの描画
	//object3d->Draw();

	// 3Dオブジェクト描画後処理
	//CalculationObject::PostDraw();
#pragma endregion

#pragma region 3Dモデル描画
	
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	//Object2D::PreDraw(cmdList);

	// デバッグテキストの描画
	//debugText.DrawAll(cmdList);

	// スプライト描画後処理
	//Object2D::PostDraw();
#pragma endregion
}
