#pragma once
#include "Code/GameObject/Enemy/Enemy.h"
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

	// �X�|�[���f�[�^�\����
	struct SpownData
	{
		Vector3 spownPos;	// �X�|�[���n�_

	};

	std::queue<SpownData> LoadData(const char* filepath);

	std::queue<SpownData> spownDatas;	// �X�|�[���f�[�^�R���e�i

	PlayerBase* playerData;
	std::weak_ptr<CollisionManager> collisionManager;
};

