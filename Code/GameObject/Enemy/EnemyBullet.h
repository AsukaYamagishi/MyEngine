#pragma once
#include "../../GameObject/GameObjectBase.h"
#include "../Code/3d/Obj/ObjDraw.h"
#include "../../Manager/ModelManager.h"
#include "../../Collision/Collider/SphereCollider.h"

class EnemyBullet :
    public GameObjectBase
{

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyBullet(DirectXCommon* dxCommon, std::weak_ptr<CollisionManager> collisionManager, Vector3 startPos, Vector3 shotVelocity);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	void OnCollision(CollisionInfo info) override;
private:
	//バレットモデル
	std::shared_ptr<ObjDraw> bullet;
	//移動量
	Vector3 velocity = { 0,0,0 };
};

