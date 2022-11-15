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

	// �X�|�[���f�[�^�\����
	struct SpawnData
	{
		Vector3 spawnPos;	// �X�|�[���n�_

	};

	void LoadData(const char* filepath);

	std::queue<SpawnData> spawnDatas;	// �X�|�[���f�[�^�R���e�i

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

