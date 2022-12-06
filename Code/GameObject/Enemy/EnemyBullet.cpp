#include "EnemyBullet.h"

EnemyBullet::EnemyBullet(DirectXCommon* dxCommon, std::weak_ptr<CollisionManager> collisionManager, Vector3 startPos, Vector3 shotVelocity):
	GameObjectBase(dxCommon)
{
	//モデルセット
	bullet = std::make_shared<ObjDraw>(*ObjDraw::Create());
	bullet->SetModel(ModelManager::GetIns()->GetModel("EnemyBullet"));


	//各変数セット
	pos = startPos;
	velocity = shotVelocity;
	bullet->SetPos(pos);
	bullet->SetScale({ 0.5f, 0.5f, 0.5f });
	bullet->SetRotation({ 90.0f,0.0f,0.0f });

	//コライダー情報セット
	std::shared_ptr<SphereCollider> sphere = std::make_shared<SphereCollider>();
	sphere.get()->SetName("EnemyBullet");
	sphere.get()->SetRadius(1.5f);
	AddCollider(sphere, collisionManager);
}

void EnemyBullet::Update()
{
	pos = bullet.get()->GetPos();
	pos += velocity;

	//画面外（手前）に来たら消去
	if (pos.z < -10.0f) {
		deleteFlag = true;
	}
	
}

void EnemyBullet::Draw()
{
	bullet->Update();
	bullet->SetPos(pos);

	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

	ObjDraw::PreDraw(cmdList);
	bullet->Draw();
	ObjDraw::PostDraw();
}

void EnemyBullet::OnCollision(CollisionInfo info)
{
	if (info.hitName == "Player" || info.hitName == "Wall") {
		deleteFlag = true;
	}
}
