#pragma once
#include "../Code/3d/Obj/ObjDraw.h"
#include "../../GameObject/GameObjectBase.h"
#include "../../Manager/ModelManager.h"
#include "../../Collision/Collider/SphereCollider.h"

class EnemyBullet :
    public GameObjectBase
{

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="dxCommon">DirectX基礎</param>
	/// <param name="collisionManager">衝突マネージャ</param>
	/// <param name="startPos">初期位置</param>
	/// <param name="shotVelocity">弾打ち出し方向</param>
	EnemyBullet(DirectXCommon* dxCommon, std::weak_ptr<CollisionManager> collisionManager, Vector3 startPos, Vector3 shotVelocity);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	/// <summary>
	/// 衝突したときの処理
	/// </summary>
	/// <param name="info">衝突情報</param>
	void OnCollision(CollisionInfo info) override;

private:
	//バレットモデル
	std::shared_ptr<ObjDraw> bullet;
	//移動量
	Vector3 velocity = { 0,0,0 };
};

