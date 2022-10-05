#pragma once
#include "../../DirectXBase/DirectXCommon.h"
#include "../Vector3.h"
#include "../../GameObject/GameObjectBase.h"
#include "../../3d/Obj/ObjDraw.h"
#include "../../Manager/ModelManager.h"

class Bullet
	:public GameObjectBase
{
#pragma region �萔
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
#pragma endregion

#pragma region �֐�
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Bullet(DirectXCommon* dxCommon, std::weak_ptr<CollisionManager> collisionManager, Vector3 startPos, Vector3 shotVelocity);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Bullet();

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="dxCommon">��b</param>
	void Init() override;

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update() override;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw() override;

	void OnCollision(CollisionInfo info) override;
#pragma endregion

#pragma region �ϐ�
private:
	//�o���b�g���f��
	std::shared_ptr<ObjDraw> bullet;
	//�ړ���
	Vector3 velocity = { 0,0,0 };
	//��������
	int liveTimer = 0;

};

