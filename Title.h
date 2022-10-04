#pragma once
#include "SafeDelete.h"
#include "DirectXCommon.h"
#include <DirectXMath.h>
#include "Code/Audio/Audio.h"
#include "KeyboardInput.h"
#include "Sprite.h"

#include "Code/Scene/AbstructScene.h"

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
	Title(DirectXCommon* dxCommon, Audio* audio);
	//�f�X�g���N�^
	~Title();
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="dxCommon">��b</param>
	/// <param name="audio">���y</param>
	void Init() override;
	//���t���[���X�V����
	void Update() override;
	//�`��
	void Draw() override;
#pragma endregion
};
