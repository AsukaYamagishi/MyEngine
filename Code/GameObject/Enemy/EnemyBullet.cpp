#include "EnemyBullet.h"

EnemyBullet::EnemyBullet(DirectXCommon* dxCommon, std::weak_ptr<CollisionManager> collisionManager, Vector3 startPos, Vector3 shotVelocity):
	GameObjectBase(dxCommon)
{

	bullet = std::make_shared<ModelDraw>(*ModelDraw::Create());
	bullet->SetModel(ModelManager::GetIns()->GetModel(ModelManager::BULLET));

	pos = startPos;
	velocity = shotVelocity;
	bullet->SetPos(pos);
	bullet->SetScale({ 0.5f, 0.5f, 0.5f });


	std::shared_ptr<SphereCollider> sphere = std::make_shared<SphereCollider>();
	sphere.get()->SetName("EnemyBullet");
	sphere.get()->SetRadius(1.0f);
	AddCollider(sphere, collisionManager);
}

void EnemyBullet::Update()
{
	pos = bullet.get()->GetPos();
	pos += velocity;
	
}

void EnemyBullet::Draw()
{
	bullet->Update();
	bullet->SetPos(pos);

	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

	ModelDraw::PreDraw(cmdList);
	bullet->Draw();
	ModelDraw::PostDraw();
}

void EnemyBullet::OnCollision(CollisionInfo info)
{
	if (info.hitName == "Player" || info.hitName == "Wall") {
		deleteFlag = true;
	}
}
