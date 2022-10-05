#include "GameObjectManager.h"

GameObjectManager::GameObjectManager(DirectXCommon* dxCommon)
{
	// nullptrチェック
	assert(dxCommon);
	this->dxCommon = dxCommon;
}

GameObjectManager::~GameObjectManager()
{
}

void GameObjectManager::Init()
{
	//追加したオブジェクトの数に応じて自動的に全て初期化
	for (auto& gameObj : objects)
	{
		gameObj->Init();
	}
}

void GameObjectManager::Update()
{
	//オブジェクトのサイズ(数)を参照
	for (int i = 0; i < objects.size(); ++i)
	{
		//deleteFlagがTRUEであればUpdate前に削除
		if (objects[i]->GetDeleteFlag()) {
    			objects.erase(objects.begin() + i);
		}
	}
	for (int i = 0; i < objects.size(); ++i) {
		objects[i]->Update();
	}
}

void GameObjectManager::Draw()
{
	//オブジェクトのサイズ(数)を参照し自動的に描画
	for (int i = 0; i < objects.size(); ++i) {
		objects[i]->Draw();
	}
}
