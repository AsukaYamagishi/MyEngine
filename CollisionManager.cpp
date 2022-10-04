#include "CollisionManager.h"
#include "Code/Collision/Collision.h"

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
	
	//���Ƌ�
	if (collisions == static_cast<int>(CollisionShapeType::SHAPE_SPHERE)) {
		Sphere* sphereA = dynamic_cast<Sphere*>(a);
		Sphere* sphereB = dynamic_cast<Sphere*>(b);

		if (Collision::IsBallToBallCollision(*sphereA, *sphereB)) {
			return true;
		}
		return false;
	}
	//����OBB
	if (collisions == (static_cast<int>(CollisionShapeType::SHAPE_SPHERE) | static_cast<int>(CollisionShapeType::SHAPE_OBB))) {
		// �K�؂Ȍ^�ɕϊ�
		Sphere* sphere;
		OBB* obb;
		// a�����ɃL���X�g�ł����b��OBB�ɕϊ�
		if (sphere = dynamic_cast<Sphere*>(a)) {
			obb = dynamic_cast<OBB*>(b);
		}
		// �����łȂ���΋t��
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
	std::vector<std::weak_ptr<BaseCollider>>::const_iterator colliderIteA;	//��ڂ̃C�e���[�^
	std::vector<std::weak_ptr<BaseCollider>>::const_iterator colliderIteB;	//��ڂ̃C�e���[�^

	// �S�ẴR���C�_�[���r
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
				colliderIteB->lock().get()->OnCollision(infoB);
			}

		}
	}
}
