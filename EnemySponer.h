#pragma once
#include "Enemy.h"
#include "PlayerBase.h"
#include "GameObjectManager.h"
#include "Vector3.h"
#include <queue>
class EnemySponer:
	public GameObject
{
public:

	EnemySponer(DirectXCommon* dxCommon,  std::shared_ptr<CollisionManager> collisionManager, PlayerBase* player);
	
	void Update() override;
private:

	// スポーンデータ構造体
	struct SpownData
	{
		Vector3 spownPos;	// スポーン地点

	};

	std::queue<SpownData> LoadData(const char* filepath);

	std::queue<SpownData> spownDatas;	// スポーンデータコンテナ

	PlayerBase* playerData;
	std::weak_ptr<CollisionManager> collisionManager;
};

