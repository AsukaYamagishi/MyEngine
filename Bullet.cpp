#include "Bullet.h"
#include "SphereCollider.h"

Bullet::Bullet(DirectXCommon* dxCommon, std::weak_ptr<CollisionManager> collisionManager, Vector3 startPos, Vector3 shotVelocity):
 	GameObject(dxCommon)
{
	bullet = std::make_shared<ModelDraw>(*ModelDraw::Create());
	bullet->SetModel(ModelManager::GetIns()->GetModel(ModelManager::BULLET));

	pos = startPos;
	velocity = shotVelocity;
	bullet->SetPos(pos);


	std::shared_ptr<SphereCollider> sphere = std::make_shared<SphereCollider>();
	sphere.get()->SetName("Bullet");
	AddCollider(sphere, collisionManager);
}

Bullet::~Bullet()
{
}

void Bullet::Init()
{

}

void Bullet::Update()
{
	pos = bullet.get()->GetPos();
	pos += velocity;
	liveTimer++;
	if (liveTimer >= 120) {
		deleteFlag = true;
	}
}

void Bullet::Draw()
{
	bullet->Update();
	bullet->SetPos(pos);

	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

	ModelDraw::PreDraw(cmdList);
	bullet->Draw();
	ModelDraw::PostDraw();
}
