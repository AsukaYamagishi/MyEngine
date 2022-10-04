#include "GameObjectBase.h"
#include "../Collision/CollisionManager.h"
#include "../Manager/GameObjectManager.h"

std::weak_ptr<GameObjectManager> GameObjectBase::gameObjectManager;

GameObjectBase::GameObjectBase(DirectXCommon* dxCommon)
{
	// nullptrチェック
	assert(dxCommon);
	this->dxCommon = dxCommon;
}

GameObjectBase::~GameObjectBase()
{
}

void GameObjectBase::SetManager(std::weak_ptr<GameObjectManager> gameObjectManager)
{
	GameObjectBase::gameObjectManager = gameObjectManager;
}

void GameObjectBase::Init()
{
}

void GameObjectBase::Update()
{
}

void GameObjectBase::Draw()
{
}

void GameObjectBase::AddCollider(std::shared_ptr<BaseCollider> collider, std::weak_ptr<CollisionManager> collisionManager)
{
	collider->SetObject(this);
	collisionManager.lock()->AddCollider(collider);
	colliders.emplace_back(collider);
}
