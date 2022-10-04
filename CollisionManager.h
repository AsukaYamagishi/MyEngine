#pragma once
#include "Code/Collision/Collider/BaseCollider.h"
#include <memory>
#include <vector>
class CollisionManager
{
public:
	inline void AddCollider(std::shared_ptr<BaseCollider> collider) {
		colliders.emplace_back(collider);
	}

	void CheckHitColliders();
private:
	void Update();
	bool CheckHit(BaseCollider *a, BaseCollider *b);

	std::vector<std::weak_ptr<BaseCollider>> colliders;
};

