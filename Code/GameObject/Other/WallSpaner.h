#pragma once
#include "../../GameObject/GameObjectBase.h"
#include "../Player/PlayerBase.h"
#include <queue>
class WallSpaner :
    public GameObjectBase
{
public:
    WallSpaner(DirectXCommon* dxCommon, std::shared_ptr<CollisionManager> collisionManager, PlayerBase* player);
    void Update() override;

private:

    void LoadData(const char* filepath);

    // �X�|�[���f�[�^�\����
    struct SpawnData
    {
        Vector3 spawnPos;	// �X�|�[���n�_
        Vector3 size;       //�T�C�Y

    };
    std::queue<SpawnData> spawnDatas;	// �X�|�[���f�[�^�R���e�i

    PlayerBase* playerData;
    std::weak_ptr<CollisionManager> collisionManager;

    void SideSpawn(Vector3 startPos);
    void VerticalSpawn(Vector3 startPos);
    void AroundSpawn(Vector3 startPos);
    void CenterSpawn(Vector3 startPos);
    enum SpawnType
    {
        SIDE,
        VERTICAL,
        AROUND,
        CENTER,
        MAX,
    };


};

