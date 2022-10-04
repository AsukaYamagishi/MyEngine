#pragma once
#include "../../DirectXBase/GameObject.h"
#include "../ModelDraw.h"
#include "../ModelManager.h"
#include "../SphereCollider.h"

class EnemyBullet :
    public GameObject
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
	std::shared_ptr<ModelDraw> bullet;
	//移動量
	Vector3 velocity = { 0,0,0 };
};

