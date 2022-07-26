#include "SceneManager.h"
std::stack<AbstructScene*> SceneManager::scenes;

DirectXCommon* SceneManager::dxCommon;
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
	scenes.top()->Init(dxCommon, audio);
}

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	
}

void SceneManager::Init(DirectXCommon* dxCommon, Audio* audio)
{
#pragma region nullptrチェック/代入
	assert(dxCommon);
	assert(audio);

	this->dxCommon = dxCommon;
	this->audio = audio;
#pragma endregion

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
