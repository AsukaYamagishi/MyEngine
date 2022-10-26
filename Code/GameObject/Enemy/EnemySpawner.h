#pragma once
#include "Enemy.h"
#include "../Player/PlayerBase.h"
#include "../../Manager/GameObjectManager.h"
#include "../../Math/Vector3.h"
#include <queue>

class EnemySpawner :
	public GameObjectBase
{
public:

	EnemySpawner(DirectXCommon* dxCommon,  std::shared_ptr<CollisionManager> collisionManager, PlayerBase* player);
	
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
	std::weak_ptr<CollisionManager> collisionManager;

	void CrossSpown(Vector3 startPos);
	void BoxSpown(Vector3 startPos);
	enum SpownType
	{
		CROSS,
		BOX,
		MAX,
	};
};

