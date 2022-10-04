#pragma once
#include "Enemy.h"
#include "../PlayerBase.h"
#include "../../Manager/GameObjectManager.h"
#include "../Vector3.h"
#include <queue>
class EnemySpawner :
	public GameObjectBase
{
public:

	EnemySpawner(DirectXCommon* dxCommon,  std::shared_ptr<CollisionManager> collisionManager, PlayerBase* player);
	
	void Update() override;
private:

	// スポーンデータ構造体
	struct SpawnData
	{
		Vector3 spawnPos;	// スポーン地点

	};

	std::queue<SpawnData> LoadData(const char* filepath);

	std::queue<SpawnData> spawnDatas;	// スポーンデータコンテナ

	PlayerBase* playerData;
	std::weak_ptr<CollisionManager> collisionManager;
};

