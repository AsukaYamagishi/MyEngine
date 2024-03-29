#include "SceneManager.h"

std::stack<AbstructScene*> SceneManager::scenes;
DirectXCommon* SceneManager::dxCommon;
Audio* SceneManager::audio;

void SceneManager::ChangeScene(SceneNo sceneNo, bool sceneStackClear)
{

	if (sceneStackClear) {
		//シーンが空になるまでポップ(取り出す)
		while (scenes.size() != 0) {
			scenes.pop();
		}
	}
	
	//シーン切り替え
	switch (sceneNo)
	{
		case SceneManager::TITLE:
			scenes.push(new TitleScene(dxCommon, audio));
			break;
		case SceneManager::GAMEPLAY:
			scenes.push(new GameScene(dxCommon, audio));
			break;
		case SceneManager::END:
			scenes.push(new EndScene(dxCommon, audio));
			break;
		case SceneManager::MAX:
			break;
		default:
			break;
	}

	//スタックの一番上のみ初期化
	scenes.top()->Init();
}

SceneManager::SceneManager(DirectXCommon* dxCommon, Audio* audio)
{
#pragma region nullptrチェック/代入
	assert(dxCommon);
	assert(audio);

	this->dxCommon = dxCommon;
	this->audio = audio;
#pragma endregion
}

SceneManager::~SceneManager()
{
	
}

void SceneManager::Init()
{
	//ゲーム起動時処理
	ChangeScene(GAMEPLAY);
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
