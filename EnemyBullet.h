#pragma once
#include "GameObject.h"
#include "ModelDraw.h"
#include "ModelManager.h"
#include "SphereCollider.h"

class EnemyBullet :
    public GameObject
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
	std::shared_ptr<ModelDraw> bullet;
	//�ړ���
	Vector3 velocity = { 0,0,0 };
};

