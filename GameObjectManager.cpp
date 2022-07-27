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
	for (auto& gameObj : objects)
	{
		gameObj->Init();
	}
}

void GameObjectManager::Update()
{
	for (int i = 0; i < objects.size(); ++i)
	{
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
	for (int i = 0; i < objects.size(); ++i) {
		objects[i]->Draw();
	}
}
