#pragma once
#include "../GameObjectBase.h"
#include "../../Math/Vector3.h"
#include "../../Manager/GameObjectManager.h"
#include "../../3d/Obj/ObjDraw.h"
#include "../../Manager/ModelManager.h"
#include "../Player/PlayerBase.h"

class Wall :
    public GameObjectBase
{
public:
    Wall(
        Vector3 startPos, 
        DirectXCommon* dxCommon,
        std::weak_ptr<CollisionManager> collisionManager,
        PlayerBase* player, Vector3 length);
    void Update() override;
    void Draw() override;
    void OnCollision(CollisionInfo info) override;
    //ƒ‚ƒfƒ‹
    std::shared_ptr<ObjDraw> wall;

    PlayerBase* player;
};

