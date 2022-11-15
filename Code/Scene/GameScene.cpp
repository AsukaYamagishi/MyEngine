#include "GameScene.h"
#include "../GameObject/Other/Wall.h"
#include "../Manager/SceneManager.h"
#include "../Collision/Collider/BaseCollider.h"
#include "../2d/Particle/ParticleManager.h"
#include "../3d/Fbx/FbxLoader.h"
#include "../3d/Fbx/FbxDraw.h"
#include <cassert>
#include <time.h>
#include "../Input/KeyboardInput.h"
#include "../Input/ControllerInput.h"
#include "../GameObject/Other/ScoreManager.h"

using namespace DirectX;

bool GameScene::gameoverFlag = false;


GameScene::GameScene(DirectXCommon* dxCommon, Audio* audio)
{
#pragma region nullptrチェック/代入
	assert(dxCommon);
	assert(audio);

	this->dxCommon = dxCommon;
	this->audio = audio;
#pragma endregion

	collisionManager = std::make_shared<CollisionManager>();
	gameObjManager = std::make_shared<GameObjectManager>(dxCommon);
	GameObjectBase::SetManager(gameObjManager);
	auto scoreManager = GameObjectBase::Create<ScoreManager>(dxCommon, &debugText);
	player = GameObjectBase::Create<PlayerBase>(dxCommon, collisionManager, PlayerType::SHOT, &debugText);
	GameObjectBase::Create<EnemySpawner>(dxCommon, collisionManager, player, scoreManager);
	GameObjectBase::Create<WallSpaner>(dxCommon, collisionManager, player);
	GameObjectBase::Create<Stage>(dxCommon, player);
	srand(time(NULL));
}

GameScene::~GameScene()
{
	//safe_deleteはここで行う
}

void GameScene::Init()
{
	//カメラのせっち
	camera->Init({ 0,0,-30 });
	camera = Camera::GetCam();
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
	
	
#pragma endregion


#pragma region 音楽リソース初期設定

	//soundData[0] = audio->SoundLoadWave("Resources/musicloop.wav");
	//audio->SoundPlayWave(audio->xAudio2.Get(), soundData[0], Audio::loop);

#pragma endregion

	gameObjManager->Init();
	gameEndFlag = false;
	gameoverFlag = false;
}

void GameScene::Update()
{
	//カメラの更新
	camera->eye.z = player->GetPos().z - 30;
	camera->target.z = camera->eye.z + 1.0f;

	gameObjManager->Update();
	collisionManager->CheckHitColliders();
	camera->SetCam(camera);
	camera->Update();

	if (player->GetPos().z > 500.0f)
	{
		gameEndFlag = true;
	}

	if (player->hp <= 0)
	{
		gameoverFlag = true;
	}


	//ゲームエンドシーンに移行(ゴールする or ENDキー)
	if (gameEndFlag || gameoverFlag || KeyboardInput::GetIns()->PressKeyTrigger(DIK_END))
	{
		SceneManager::ChangeScene(SceneManager::END);
	}

#pragma region デバッグテキスト設定
	//debugText.PrintDebugText("test012", 0.0f, 0.0f, 2.0f);
#pragma endregion

	//ゲーム中タイマー加算
	++timer;
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
	
	gameObjManager->Draw();

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
