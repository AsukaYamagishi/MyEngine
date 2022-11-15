#include "EndScene.h"
#include <cassert>
#include "../Input/KeyboardInput.h"
#include "../Input/ControllerInput.h"
#include "../Manager/SceneManager.h"

using namespace DirectX;

EndScene::EndScene(DirectXCommon* dxCommon, Audio* audio)
{
	// nullptrチェック
	assert(dxCommon);
	assert(audio);

	this->dxCommon = dxCommon;
	this->audio = audio;
}

EndScene::~EndScene()
{
	safe_delete(spriteBG);
	//safe_delete(sprite1);
}

void EndScene::Init()
{
	// テクスチャ読み込み(１番にするとよくわからんエラー起こる)
	if (!Sprite::LoadTexture(4, L"Resources/END.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(5, L"Resources/Gameover.png")) {
		assert(0);
		return;
	}
	//// 背景スプライト生成
	//spriteBG = Sprite::CreateSprite(4, { 0.0f,0.0f });
	if (GameScene::gameoverFlag == true)
	{
		spriteBG = Sprite::CreateSprite(5, { 0.0f,0.0f });
	}
	else
	{
		spriteBG = Sprite::CreateSprite(4, { 0.0f,0.0f });
	}
	
}

void EndScene::Update()
{
	if (GameScene::gameoverFlag == true)
	{
		//ゲーム画面に戻る
		if (KeyboardInput::GetIns()->PressKeyTrigger(DIK_SPACE)
			|| ControllerInput::GetIns()->IsPadButtonTrigger(XBOX_INPUT_B))
		{
			SceneManager::ChangeScene(SceneManager::GAMEPLAY);
		}
		//タイトル画面に戻る
		else if (KeyboardInput::GetIns()->PressKeyTrigger(DIK_RETURN)
			|| ControllerInput::GetIns()->IsPadButtonTrigger(XBOX_INPUT_A))
		{
			SceneManager::ChangeScene(SceneManager::TITLE);
		}
	}
	else
	{
		//タイトル画面に戻る
		if (KeyboardInput::GetIns()->PressKeyTrigger(DIK_SPACE)
			|| ControllerInput::GetIns()->IsPadButtonTrigger(XBOX_INPUT_B))
		{
			SceneManager::ChangeScene(SceneManager::TITLE);
		}
	}
	
}

void EndScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	// 背景スプライト描画
	spriteBG->Draw();

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

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

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	//CalculationObject::PostDraw();
#pragma endregion

#pragma region 3Dモデル描画
// 3Dモデル描画前処理
	//ModelObj::PreDraw(cmdList);

	// 3Dオブクジェクトの描画
	//model->Draw();

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	//ModelObj::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる

	//AL3 1-2追加
	//sprite1->Draw();
	//sprite2->Draw();
	
	/// </summary>


	// デバッグテキストの描画
	//debugText.DrawAll(cmdList);

	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion
}
