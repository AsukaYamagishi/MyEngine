#pragma once
#include <stack>
#include "../Scene/TitleScene.h"
#include "../Scene/GameScene.h"
#include "../Scene/EndScene.h"

class SceneManager
{
public:    //�T�u�N���X
	//�V�[���J�ڔԍ�
	enum SceneNo {
		TITLE,
		GAMEPLAY,
		END,

		MAX //�ő吔�Ǘ�
	};

#pragma region �ϐ�
private: //�����o�ϐ�
	static DirectXCommon* dxCommon;
	static Audio* audio;
private: //�ÓI�����o�ϐ�
	static std::stack<AbstructScene *> scenes; //�V�[���X�^�b�N
#pragma endregion

#pragma region �ÓI�����o�֐�
public: //�ÓI�����o�֐�
	/// <summary>
	/// �V�[���`�F���W
	/// </summary>
	/// <param name="sceneNo">�V�[����</param>
	/// <param name="sceneStackClear">�S�ẴV�[�������������邩</param>
	static void ChangeScene(SceneNo sceneNo,bool sceneStackClear = false);
#pragma endregion

#pragma region �����o�֐�
public: //�����o�֐�
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="dxCommon">DirectX��b</param>
	/// <param name="audio">���y���\�[�X</param>
	SceneManager(DirectXCommon* dxCommon, Audio* audio);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~SceneManager();

	/// <summary>
	/// ������
	/// </summary>
	void Init();
	
	/// <summary>
	/// ���t���[���X�V����
	/// </summary>
	void Update();
	
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();
#pragma endregion
};

