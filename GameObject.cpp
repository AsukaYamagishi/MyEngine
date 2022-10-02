#include "GameObject.h"
#include "CollisionManager.h"
#include "GameObjectManager.h"

std::weak_ptr<GameObjectManager> GameObject::gameObjectManager;

GameObject::GameObject(DirectXCommon* dxCommon)
{
	// nullptrチェック
	assert(dxCommon);
	this->dxCommon = dxCommon;
}

GameObject::~GameObject()
{
}

void GameObject::SetManager(std::weak_ptr<GameObjectManager> gameObjectManager)
{
	GameObject::gameObjectManager = gameObjectManager;
}

void GameObject::Init()
{
}

void GameObject::Update()
{
}

void GameObject::Draw()
{
}

void GameObject::AddCollider(std::shared_ptr<BaseCollider> collider, std::weak_ptr<CollisionManager> collisionManager)
{
	collider->SetObject(this);
	collisionManager.lock()->AddCollider(collider);
	colliders.emplace_back(collider);
}
