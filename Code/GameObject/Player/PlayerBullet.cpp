#include "PlayerBullet.h"
#include "../../Collision/Collider/SphereCollider.h"

Bullet::Bullet(DirectXCommon* dxCommon, std::weak_ptr<CollisionManager> collisionManager, Vector3 startPos, Vector3 shotVelocity):
 	GameObjectBase(dxCommon)
{
	bullet = std::make_shared<ObjDraw>(*ObjDraw::Create());
	bullet->SetModel(ModelManager::GetIns()->GetModel(ModelManager::BULLET));

	pos = startPos;
	velocity = shotVelocity;
	bullet->SetPos(pos);
	bullet->SetScale({ 0.5f, 0.5f, 0.5f });


	std::shared_ptr<SphereCollider> sphere = std::make_shared<SphereCollider>();
	sphere.get()->SetName("Bullet");
	sphere.get()->SetRadius(1.0f);
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

	ObjDraw::PreDraw(cmdList);
	bullet->Draw();
	ObjDraw::PostDraw();
}

void Bullet::OnCollision(CollisionInfo info)
{
 	if (info.hitName == "Enemy" || info.hitName == "Wall") {
		deleteFlag = true;
	}
}
