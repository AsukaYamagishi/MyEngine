#include "Enemy.h"

Enemy::Enemy(DirectXCommon* dxCommon, std::shared_ptr<GameObjectManager> gameObjManager, std::shared_ptr<CollisionManager> collisionManager):
	GameObject(dxCommon)
{
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
}

void Enemy::Update()
{
}

void Enemy::Draw()
{
}

void Enemy::OnCollision(CollisionInfo info)
{
}

void Enemy::Move()
{
}
