#pragma once
#include "../DirectXBase/SafeDelete.h"
#include "../DirectXBase/DirectXCommon.h"
#include <DirectXMath.h>
#include "../Audio/Audio.h"
#include "../2d/Sprite.h"
#include "AbstructScene.h"


using namespace Microsoft::WRL;
using namespace DirectX;

//�Q�[���V�[��
class TitleScene :
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
	TitleScene(DirectXCommon* dxCommon, Audio* audio);
	//�f�X�g���N�^
	~TitleScene();
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
