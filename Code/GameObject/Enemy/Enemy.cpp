#include "Enemy.h"
#include "EnemyBullet.h"
#include "../SphereCollider.h"

Enemy::Enemy(DirectXCommon* dxCommon, std::weak_ptr<GameObjectManager> gameObjManager, std::weak_ptr<CollisionManager> collisionManager, Vector3 startPos, PlayerBase* player):
	GameObject(dxCommon)
{
	enemy = std::make_shared<ModelDraw>(*ModelDraw::Create());
	enemy->SetModel(ModelManager::GetIns()->GetModel(ModelManager::ENEMY));
	this->gameObjManager = gameObjManager;
	this->collisionManager = collisionManager;
	pos = startPos;
	enemy->SetPos(pos);

	this->player = player;

	std::shared_ptr<SphereCollider> sphere = std::make_shared<SphereCollider>();
	sphere.get()->SetName("Enemy");
	sphere.get()->SetRadius(3.0f);
	//sphere.get()->SetOffset({ 0.0f,0.0f,0.0f });
	AddCollider(sphere, collisionManager);
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
}

void Enemy::Update()
{
	Move();
	++liveTime;
	if (liveTime % 120 == 0)
	{
		GameObject::Create<EnemyBullet>(dxCommon, collisionManager, pos + Vector3{ 0,0,-1.0f }, Vector3{ 0.0f,0.0f,-0.7f });
	}
	if (pos.z < player->GetPos().z - 30) {
		deleteFlag = true;
	}
}

void Enemy::Draw()
{
	enemy->Update();
	enemy->SetPos(pos);

	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

	ModelDraw::PreDraw(cmdList);
	enemy->Draw();
	ModelDraw::PostDraw();
}

void Enemy::OnCollision(CollisionInfo info)
{
 	if (info.hitName == "Bullet") {
   		deleteFlag = true;
	}
}

void Enemy::Move()
{
	/*pos = enemy->GetPos();
	if (pos.z >= 10.0f)
	{
		velocity.z = move;
	}
	else
	{
		velocity.z = 0.0f;
	}
	pos += velocity;*/
}
