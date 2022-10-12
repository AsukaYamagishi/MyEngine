#pragma once
#include "Collider/BaseCollider.h"
#include <memory>
#include <vector>

class CollisionManager
{
public:
	/// <summary>
	/// コライダー情報の追加
	/// </summary>
	/// <param name="collider">コライダー</param>
	inline void AddCollider(std::shared_ptr<BaseCollider> collider) {
		colliders.emplace_back(collider);
	}

	void CheckHitColliders();

private:
	void Update();
	bool CheckHit(BaseCollider *a, BaseCollider *b);

	std::vector<std::weak_ptr<BaseCollider>> colliders;
};

