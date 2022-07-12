#pragma once
#include "SafeDelete.h"
#include "DirectXCommon.h"
#include <DirectXMath.h>
#include "Audio.h"
#include "KeyboardInput.h"
#include "Sprite.h"

#include "AbstructScene.h"

using namespace Microsoft::WRL;
using namespace DirectX;

//�Q�[���V�[��
class Title :
	public AbstructScene
{
#pragma region �ϐ�
private: //�ÓI�����o�ϐ�
	

private: //�����o�ϐ�
	DirectXCommon* dxCommon = nullptr;
	KeyboardInput* input = nullptr;
	Audio* audio = nullptr;
	
	//�Q�[���V�[���p
	Sprite* spriteBG = nullptr;

#pragma endregion

#pragma region �ÓI�����o�֐�

private: //�ÓI�����o�֐�
public: //�ÓI�����o�֐�
#pragma endregion

#pragma region �Q�b�^�[/�Z�b�^�[
	//a
#pragma endregion

#pragma region �����o�֐�
public: //�����o�֐�
	//�R���X�g���N�^
	Title();
	//�f�X�g���N�^
	~Title();
	/// <summary>
	/// <para>������</para>
	/// �ł�
	/// </summary>
	/// <param name="dxCommon"></param>
	/// <param name="input">����</param>
	/// <param name="audio"></param>
	void Init(DirectXCommon* dxCommon, KeyboardInput* input, Audio* audio) override;
	//���t���[���X�V����
	void Update() override;
	//�`��
	void Draw() override;
#pragma endregion
};
