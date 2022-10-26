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

    // スポーンデータ構造体
    struct SpawnData
    {
        Vector3 spawnPos;	// スポーン地点
        Vector3 size;       //サイズ

    };
    std::queue<SpawnData> spawnDatas;	// スポーンデータコンテナ

    PlayerBase* playerData;
    std::weak_ptr<CollisionManager> collisionManager;

};

