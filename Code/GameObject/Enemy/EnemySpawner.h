#pragma once
#include "Enemy.h"
#include "../Player/PlayerBase.h"
#include "../../Manager/GameObjectManager.h"
#include "../../Math/Vector3.h"
#include <queue>
#include "../Other/ScoreManager.h"

class EnemySpawner :
	public GameObjectBase
{
public:

	EnemySpawner(DirectXCommon* dxCommon,  std::shared_ptr<CollisionManager> collisionManager, PlayerBase* player, ScoreManager* scoreMan);
	
	void Update() override;
private:

	// スポーンデータ構造体
	struct SpawnData
	{
		Vector3 spawnPos;	// スポーン地点

	};

	void LoadData(const char* filepath);

	std::queue<SpawnData> spawnDatas;	// スポーンデータコンテナ

	PlayerBase* playerData;
	ScoreManager* scoreManager;
	std::weak_ptr<CollisionManager> collisionManager;

	void CrossSpawn(Vector3 startPos);
	void BoxSpawn(Vector3 startPos);
	enum SpawnType
	{
		CROSS,
		BOX,
		MAX,
	};
};

