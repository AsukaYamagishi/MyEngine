#pragma once
#include <vector>
#include "../GameObject/GameObjectBase.h"

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
	void AddGameObject(GameObjectBase *obj) {
		objects.emplace_back(obj);
	};

#pragma endregion

#pragma region �ϐ�
private:
	DirectXCommon* dxCommon = nullptr;

	//�Q�[���I�u�W�F�N�g
	std::vector<std::shared_ptr<GameObjectBase>> objects;
#pragma endregion
};

