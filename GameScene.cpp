#include "GameScene.h"
#include "ParticleManager.h"
#include <cassert>
#include <time.h>
#include "FbxInput.h"
#include "FbxDraw.h"

#include "SceneManager.h"

using namespace DirectX;


GameScene::GameScene()
{

}

GameScene::~GameScene()
{
	//safe_deleteはここで行う
	safe_delete(particleMan);
	safe_delete(testObject);
}

void GameScene::Init(DirectXCommon *dxCommon, KeyboardInput *input, Audio *audio)
{
#pragma region nullptrチェック/代入
	assert(dxCommon);
	assert(input);
	assert(audio);

	this->dxCommon = dxCommon;
	this->input = input;
	this->audio = audio;
#pragma endregion


	//カメラのせっち
	camera->Init({ 0,30,130 });
	camera = Camera::GetCam();
	//camera->target = { 0 ,50 ,0 };
#pragma endregion

#pragma region デバッグテキスト読み込み
	// デバッグテキスト用テクスチャ読み込み
	if (!Sprite::LoadTexture(debugTextTexNum, L"Resources/DebugText.png")) {
		assert(0);
		return;
	}
	// デバッグテキスト初期化
	debugText.Init(debugTextTexNum);

#pragma endregion

#pragma region Sprite初期設定
	// テクスチャ読み込み(１番にするとよくわからんエラー起こる)
	/*if (!Sprite::LoadTexture(3, L"Resources/white1x1.png")) {
		assert(0);
		return;
	}*/
	// 背景スプライト生成
	//spriteBG = Sprite::CreateSprite(3, { 0.0f,0.0f });
#pragma endregion
	//デバイスをセット
	FbxDraw::SetDevice(dxCommon->GetDevice());
	//カメラをセット
	FbxDraw::SetCamera(camera);
	//グラフィックスパイプライン生成
	FbxDraw::CreateGraphicsPipeline();

#pragma region 3DモデルCreate・初期設定
	//モデルを指定して読み込み
	testModel = FbxInput::GetInstance()->LoadFbxFromFile("boneTest");
	//3Dオブジェクト生成とモデルのセット
	testObject = new FbxDraw();
	testObject->Init();
	testObject->SetModel(testModel.get());
	testObject->SetScale({ 10,10,10 });
	testObject->SetRotation({ 0,45,0 });
	testObject->SetPosition({ -50,-15,3 });
	testObject->PlayAnimation(true);

	boxModel= FbxInput::GetInstance()->LoadFbxFromFile("Box");
	boxObject = new FbxDraw();
	boxObject->Init();
	boxObject->SetModel(boxModel.get());
	boxObject->SetScale({ 0.1,0.1,0.1 });
	boxObject->SetRotation({ 0,30,0 });
	boxObject->SetPosition({ 50,-15,3 });


	stage = new Stage();
	stage->Initialize(dxCommon);
#pragma endregion


#pragma region 音楽リソース初期設定

	//soundData[0] = audio->SoundLoadWave("Resources/musicloop.wav");
	//audio->SoundPlayWave(audio->xAudio2.Get(), soundData[0], Audio::loop);

#pragma endregion

	player = new Player();
	player->Initialize(dxCommon, input, audio);

	

	gameEndFlag = false;
}

void GameScene::Update()
{

	stage->Update();
	
	
	testObject->Update();
	boxObject->Update();
	
	camera->SetCam(camera);
	camera->Update();

	////シーン切り替え
	//if (input->PressKeyTrigger(DIK_0)) {
	//	SceneManager::ChangeScene(SceneManager::SceneNo::titleScene);
	//}

#pragma region デバッグテキスト設定
	
#pragma endregion

}

void GameScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList *cmdList = dxCommon->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	//Sprite::PreDraw(cmdList);

	// 背景スプライト描画
	//spriteBG->Draw();

	// スプライト描画後処理
	//Sprite::PostDraw();

	//深度バッファクリア
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


	//stage->Draw();
	
	
	testObject->Draw(cmdList);
	boxObject->Draw(cmdList);
	
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	//前景スプライト描画
	//sprite->Draw();
	// デバッグテキストの描画
	debugText.DrawAll(cmdList);
	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion
}
