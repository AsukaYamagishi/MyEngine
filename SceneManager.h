#pragma once
#include "GameScene.h"
#include "Title.h"
#include "EndGame.h"

#include <stack>

class SceneManager
{

public:    //�T�u�N���X
	//�V�[���J�ڔԍ�
	enum SceneNo {
		titleScene,
		gameScene,
		endScene,

		MAX
	};

#pragma region �ϐ�
private: //�����o�ϐ�
	static DirectXCommon* dxCommon;
	static KeyboardInput* input;
	static Audio* audio;
#pragma endregion

#pragma region �ÓI�����o�֐�

private: //�ÓI�����o�֐�
	static std::stack<AbstructScene *> scenes;
public: //�ÓI�����o�֐�
	static void ChangeScene(SceneNo sceneNo,bool sceneStackClear = false);
#pragma endregion
#pragma region �Q�b�^�[/�Z�b�^�[
	//a
	void w(int a, int b);
#pragma endregion

#pragma region �����o�֐�
public: //�����o�֐�
	//�R���X�g���N�^
	SceneManager();
	//�f�X�g���N�^
	~SceneManager();
	//������
	void Init(DirectXCommon* dxCommon, KeyboardInput* input, Audio* audio);
	//���t���[���X�V����
	void Update();
	//�`��
	void Draw();
#pragma endregion
};

