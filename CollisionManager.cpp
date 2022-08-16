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
	
	//球と球
	if (collisions == static_cast<int>(CollisionShapeType::SHAPE_SPHERE)) {
		Sphere* sphereA = dynamic_cast<Sphere*>(a);
		Sphere* sphereB = dynamic_cast<Sphere*>(b);

		if (Collision::IsBallToBallCollision(*sphereA, *sphereB)) {
			return true;
		}
		return false;
	}
	//球とOBB
	if (collisions == static_cast<int>(CollisionShapeType::SHAPE_SPHERE) | static_cast<int>(CollisionShapeType::SHAPE_OBB)) {
		// 適切な型に変換
		Sphere* sphere;
		OBB* obb;
		// aを球にキャストできればbをOBBに変換
		if (sphere = dynamic_cast<Sphere*>(a)) {
			obb = dynamic_cast<OBB*>(b);
		}
		// そうでなければ逆に
		else {
			obb = dynamic_cast<OBB*>(a);
			sphere = dynamic_cast<Sphere*>(b);
		}

		if (Collision::IsSphereToObb(*sphere, *obb)) {
			return true;
		}
		return false;

	}


	return false;
}

void CollisionManager::CheckHitColliders()
{
	Update();
	std::vector<std::weak_ptr<BaseCollider>>::const_iterator colliderIteA;	//一つ目のイテレータ
	std::vector<std::weak_ptr<BaseCollider>>::const_iterator colliderIteB;	//二つ目のイテレータ

	// 全てのコライダーを比較
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
