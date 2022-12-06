#include "Enemy.h"
#include "EnemyBullet.h"
#include "../../Collision/Collider/SphereCollider.h"

Enemy::Enemy(DirectXCommon* dxCommon, std::weak_ptr<GameObjectManager> gameObjManager, std::weak_ptr<CollisionManager> collisionManager, Vector3 startPos, PlayerBase* player, ScoreManager* scoreMan):
	GameObjectBase(dxCommon)
{
	enemy = std::make_shared<ObjDraw>(*ObjDraw::Create());
	enemy->SetModel(ModelManager::GetIns()->GetModel("Enemy"));
	this->gameObjManager = gameObjManager;
	this->collisionManager = collisionManager;
	scoreManager = scoreMan;
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

	//120f‚²‚Æ‚É’e‚ð”­ŽË
	if (liveTime % 120 == 0)
	{
		GameObjectBase::Create<EnemyBullet>(dxCommon, collisionManager, pos + Vector3{ 0,0,-1.0f }, Vector3{ 0.0f,0.0f,-0.7f });
	}

	// ˆê’è‹——£‚ð•Û‚Â
	float playerToEnemy = pos.z - player->GetPos().z;
	if (playerToEnemy < 15.0f)
	{
		pos.z = player->GetPos().z + 15.0f;
	}

	// —£’E
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
	//ƒvƒŒƒCƒ„[’e‚É“–‚½‚Á‚½ŽžÁ‚¦‚é
 	if (info.hitName == "Bullet") {
		scoreManager->AddScore(100);
   		deleteFlag = true;
	}
}

void Enemy::Move()
{
	pos += velocity;
}
