#pragma once
#include "../../GameObject/GameObjectBase.h"
#include "../Code/3d/Obj/ObjDraw.h"
#include "../../Manager/ModelManager.h"
#include "../SphereCollider.h"

class EnemyBullet :
    public GameObjectBase
{

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	EnemyBullet(DirectXCommon* dxCommon, std::weak_ptr<CollisionManager> collisionManager, Vector3 startPos, Vector3 shotVelocity);

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update() override;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw() override;

	void OnCollision(CollisionInfo info) override;
private:
	//�o���b�g���f��
	std::shared_ptr<ObjDraw> bullet;
	//�ړ���
	Vector3 velocity = { 0,0,0 };
};

