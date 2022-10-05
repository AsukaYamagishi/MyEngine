#pragma once
#include "../Scene/GameScene.h"
#include "../Scene/TitleScene.h"
#include "../Scene/EndScene.h"

#include <stack>

class SceneManager
{

public:    //�T�u�N���X
	//�V�[���J�ڔԍ�
	enum SceneNo {
		TITLE,
		GAMEPLAY,
		END,

		MAX
	};

#pragma region �ϐ�
private: //�����o�ϐ�
	static DirectXCommon* dxCommon;
	static Audio* audio;
#pragma endregion

#pragma region �ÓI�����o�֐�

private: //�ÓI�����o�֐�
	static std::stack<AbstructScene *> scenes;
public: //�ÓI�����o�֐�
	static void ChangeScene(SceneNo sceneNo,bool sceneStackClear = false);
#pragma endregion

#pragma region �Q�b�^�[/�Z�b�^�[
#pragma endregion

#pragma region �����o�֐�
public: //�����o�֐�
	//�R���X�g���N�^
	SceneManager(DirectXCommon* dxCommon, Audio* audio);
	//�f�X�g���N�^
	~SceneManager();
	//������
	void Init();
	//���t���[���X�V����
	void Update();
	//�`��
	void Draw();
#pragma endregion
};

