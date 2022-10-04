#pragma once
#include "../../DirectXBase/GameObject.h"
#include "../GameObjectManager.h"
#include "../ModelDraw.h"
#include "../ModelManager.h"
#include "../PlayerBase.h"


class Enemy :
    public GameObject
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
	Enemy(DirectXCommon* dxCommon, std::weak_ptr<GameObjectManager> gameObjManager, std::weak_ptr<CollisionManager> collisionManager, Vector3 startPos, PlayerBase* player);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Enemy();

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="dxCommon">��b����</param>
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
private:
	/// <summary>
	/// �ړ�����
	/// </summary>
	void Move();

#pragma endregion

#pragma region �ϐ�
private:
	std::weak_ptr<GameObjectManager> gameObjManager;
	std::weak_ptr<CollisionManager> collisionManager;

	//���f��
	std::shared_ptr<ModelDraw> enemy;
	//1f�̃L�[���͂ɑ΂���ړ���
	float move = -0.1f;
	//1f���ł̍��v�ړ���
	Vector3 velocity = { 0,0,0 };

	PlayerBase* player;

	int liveTime = 0;	//��������
#pragma endregion
};

