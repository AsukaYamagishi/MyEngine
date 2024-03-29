#include "Enemy.h"
#include "EnemyBullet.h"
#include "../../Collision/Collider/SphereCollider.h"

Enemy::Enemy(DirectXCommon* dxCommon, std::weak_ptr<GameObjectManager> gameObjManager, std::weak_ptr<CollisionManager> collisionManager, Vector3 startPos, PlayerBase* player):
	GameObjectBase(dxCommon)
{
	enemy = std::make_shared<ObjDraw>(*ObjDraw::Create());
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

	//120fごとに弾を発射
	if (liveTime % 120 == 0)
	{
		GameObjectBase::Create<EnemyBullet>(dxCommon, collisionManager, pos + Vector3{ 0,0,-1.0f }, Vector3{ 0.0f,0.0f,-0.7f });
	}

	// 一定距離を保つ
	float playerToEnemy = pos.z - player->GetPos().z;
	if (playerToEnemy < 20.0f)
	{
		pos.z = player->GetPos().z + 20.0f;
	}

	// 離脱
	if (liveTime >= 300)
	{
		velocity.x = 1;
		if (pos.x >= 100)
		{
			deleteFlag = true;
		}
	}
}

void Enemy::Draw()
{
	enemy->Update();
	enemy->SetPos(pos);

	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

	ObjDraw::PreDraw(cmdList);
	enemy->Draw();
	ObjDraw::PostDraw();
}

void Enemy::OnCollision(CollisionInfo info)
{
	//プレイヤー弾に当たった時消える
 	if (info.hitName == "Bullet") {
   		deleteFlag = true;
	}
}

void Enemy::Move()
{
	pos += velocity;
}
