#pragma once
#include "GameObject.h"
#include <vector>

class GameObjectManager
{
#pragma region �֐�
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	GameObjectManager(DirectXCommon* dxCommon);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~GameObjectManager();

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="dxCommon">��b����</param>
	void Init();

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �I�u�W�F�N�g��vector�ɒǉ�
	/// </summary>
	template<class T, class...Args>
	T* AddGameObject(Args... args) {
		T* obj = new T(args...);
		objects.emplace_back(obj);
		return obj;
	};

#pragma endregion

#pragma region �ϐ�
private:
	DirectXCommon* dxCommon = nullptr;

	//�Q�[���I�u�W�F�N�g
	std::vector<std::shared_ptr<GameObject>> objects;
#pragma endregion
};

