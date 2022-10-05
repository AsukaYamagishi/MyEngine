#pragma once
#include "Code/GameObject/GameObjectBase.h"
#include "Vector3.h"
#include "Code/Manager/GameObjectManager.h"
#include "Code/3d/Obj/ObjDraw.h"
#include "Code/Manager/ModelManager.h"
#include "PlayerBase.h"

class Wall :
    public GameObjectBase
{
public:
    Wall(Vector3 startPos, DirectXCommon* dxCommon, std::shared_ptr<GameObjectManager> gameObjManager, std::shared_ptr<CollisionManager> collisionManager, PlayerBase* player);
    void Update() override;
    void Draw() override;
    void OnCollision(CollisionInfo info) override;
    //ƒ‚ƒfƒ‹
    std::shared_ptr<ObjDraw> wall;

    PlayerBase* player;
};

