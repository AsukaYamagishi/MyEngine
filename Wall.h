#pragma once
#include "Code/GameObject/GameObjectBase.h"
#include "Vector3.h"
#include "Code/Manager/GameObjectManager.h"
#include "ModelDraw.h"
#include "ModelManager.h"
#include "PlayerBase.h"

class Wall :
    public GameObjectBase
{
public:
    Wall(Vector3 startPos, DirectXCommon* dxCommon, std::shared_ptr<GameObjectManager> gameObjManager, std::shared_ptr<CollisionManager> collisionManager, PlayerBase* player);
    void Update() override;
    void Draw() override;
    void OnCollision(CollisionInfo info) override;
    //���f��
    std::shared_ptr<ModelDraw> wall;

    PlayerBase* player;
};

