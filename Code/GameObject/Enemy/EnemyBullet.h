#pragma once
#include "../Code/3d/Obj/ObjDraw.h"
#include "../../GameObject/GameObjectBase.h"
#include "../../Manager/ModelManager.h"
#include "../../Collision/Collider/SphereCollider.h"

class EnemyBullet :
    public GameObjectBase
{

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="dxCommon">DirectX��b</param>
	/// <param name="collisionManager">�Փ˃}�l�[�W��</param>
	/// <param name="startPos">�����ʒu</param>
	/// <param name="shotVelocity">�e�ł��o������</param>
	EnemyBullet(DirectXCommon* dxCommon, std::weak_ptr<CollisionManager> collisionManager, Vector3 startPos, Vector3 shotVelocity);

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update() override;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw() override;

	/// <summary>
	/// �Փ˂����Ƃ��̏���
	/// </summary>
	/// <param name="info">�Փˏ��</param>
	void OnCollision(CollisionInfo info) override;

private:
	//�o���b�g���f��
	std::shared_ptr<ObjDraw> bullet;
	//�ړ���
	Vector3 velocity = { 0,0,0 };
};

