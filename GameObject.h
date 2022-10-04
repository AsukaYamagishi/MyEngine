#pragma once
#include "DirectXCommon.h"
#include "Vector3.h"
#include "Code/Collision/CollisionInfo.h"

class CollisionManager;
class GameObjectManager;

class GameObject
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
	GameObject(DirectXCommon* dxCommon);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~GameObject();

	/// <summary>
	/// �}�l�[�W���̃Z�b�g
	/// </summary>
	/// <param name="gameObjectManager"></param>
	static void SetManager(std::weak_ptr<GameObjectManager> gameObjectManager);

	/// <summary>
	/// �I�u�W�F�N�g�����֐�
	/// </summary>
	/// <typeparam name="Object">�����������I�u�W�F�N�g�e���v���[�g</typeparam>
	/// <typeparam name="...Args">�ϒ������e���v���[�g</typeparam>
	/// <returns></returns>
	template<class Object,class ...Args>
	static Object* Create(Args ...args);

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="dxCommon">��b</param>
	virtual void Init();

	/// <summary>
	/// ���t���[������
	/// </summary>
	virtual void Update();

	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw();

	void AddCollider(std::shared_ptr<BaseCollider> collider, std::weak_ptr<CollisionManager>  collisionManager);
	virtual void OnCollision(CollisionInfo info) {	}

	Vector3 GetPos() { return pos; }

	bool GetDeleteFlag() { return deleteFlag; }
#pragma endregion

#pragma region �ϐ�
protected:
	DirectXCommon* dxCommon = nullptr;
	//�폜�t���O
	bool deleteFlag = false;

	//���W
	Vector3 pos = { 0,0,0 };
	
	// �������������Ă���}�l�[�W���[
	static std::weak_ptr<GameObjectManager> gameObjectManager;
	std::vector<std::shared_ptr<BaseCollider>> colliders;

};

template<class Object, class ...Args>
inline Object* GameObject::Create(Args ...args)
{
	Object* obj = new Object(args...);
	gameObjectManager.lock()->AddGameObject(obj);
	return obj;
}
