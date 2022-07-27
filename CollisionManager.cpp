#include "CollisionManager.h"
#include "Collision.h"

void CollisionManager::Update()
{
	for (int i = 0; i < colliders.size(); ++i)
	{
		if (colliders[i].lock() == nullptr) {
			colliders.erase(colliders.begin() + i);
		}
	}
	for (int i = 0; i < colliders.size(); ++i) {
		colliders[i].lock()->Update();
	}
}

bool CollisionManager::CheckHit(BaseCollider *a, BaseCollider *b)
{
	int collisions = static_cast<int>(a->GetShapeType()) | static_cast<int>(b->GetShapeType());
	
	//‹…‚Æ‹…
	if (collisions == static_cast<int>(CollisionShapeType::SHAPE_SPHERE)) {
		auto sphereA = dynamic_cast<Sphere*>(a);
		auto sphereB = dynamic_cast<Sphere*>(b);

		if (Collision::IsBallToBallCollision(*sphereA, *sphereB)) {
			return true;
		}
		return false;
	}

	return false;
}

void CollisionManager::CheckHitColliders()
{
	Update();
	std::vector<std::weak_ptr<BaseCollider>>::const_iterator colliderIteA;
	std::vector<std::weak_ptr<BaseCollider>>::const_iterator colliderIteB;

	for (colliderIteA = colliders.begin(); colliderIteA != colliders.end(); ++colliderIteA) {
		colliderIteB = colliderIteA;
		++colliderIteB;
		for (; colliderIteB != colliders.end(); ++colliderIteB) {

			if (CheckHit(colliderIteA->lock().get(), colliderIteB->lock().get())) {

				CollisionInfo infoA;
				infoA.object = colliderIteB->lock()->object;
				infoA.hitName = colliderIteB->lock()->GetCollisionName();

 				CollisionInfo infoB;
				infoB.object = colliderIteA->lock()->object;
				infoB.hitName = colliderIteA->lock()->GetCollisionName();

				colliderIteA->lock().get()->OnCollision(infoA);
				colliderIteA->lock().get()->OnCollision(infoB);
			}

		}
	}
}
