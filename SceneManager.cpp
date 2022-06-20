#include "SceneManager.h"
std::stack<AbstructScene*> SceneManager::scenes;

DirectXCommon* SceneManager::dxCommon;
KeyboardInput* SceneManager::input;
Audio* SceneManager::audio;

void SceneManager::ChangeScene(SceneNo sceneNo, bool sceneStackClear)
{

	if (sceneStackClear) {
		//シーンが空になるまでポップ
		while (scenes.size() != 0) {
			scenes.pop();
		}
	}
	
	//シーン切り替え
	switch (sceneNo)
	{
		case SceneManager::titleScene:
			scenes.push(new Title());
			break;
		case SceneManager::gameScene:
			scenes.push(new GameScene());
			break;
		case SceneManager::endScene:
			scenes.push(new EndGame());
			break;
		case SceneManager::MAX:
			break;
		default:
			break;
	}
	scenes.top()->Init(dxCommon, input, audio);
}

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	
}

void SceneManager::Init(DirectXCommon* dxCommon, KeyboardInput* input, Audio* audio)
{
#pragma region nullptrチェック/代入
	assert(dxCommon);
	assert(input);
	assert(audio);

	this->dxCommon = dxCommon;
	this->input = input;
	this->audio = audio;
#pragma endregion

	//各シーン生成/最初のシーン初期化
	//title = new Title();
	//title->Init(dxCommon, input, audio);
	//end = new EndGame();
	////end->Init(dxCommon, input, audio);
	//game = new GameScene();
	//game->Init(dxCommon, input, audio);

	//ポストエフェクト用テクスチャ読み込み
	//Sprite::LoadTexture(100, L"Resources/white1x1.png");

	//ゲーム開始シーンの設定
	//sceneNo = gameScene;

	ChangeScene(gameScene);

}

void SceneManager::Update()
{

#pragma region シーンアップデート
	//スタックの一番上をアップデート
	scenes.top()->Update();
#pragma endregion

}

void SceneManager::Draw()
{
	scenes.top()->Draw();
}
