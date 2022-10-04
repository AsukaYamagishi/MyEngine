#pragma once
#include "SafeDelete.h"
#include "DirectXCommon.h"
#include <DirectXMath.h>
#include "Sprite.h"
#include "Code/DirectXBase/DebugText.h"
#include "Code/Audio/Audio.h"
#include "KeyboardInput.h"
#include "ModelDraw.h"

#include "Code/Scene/AbstructScene.h"

using namespace Microsoft::WRL;
using namespace DirectX;

//�Q�[���V�[��
class EndGame :
	public AbstructScene
{
#pragma region �ϐ�
private: //�ÓI�����o�ϐ�
	

private: //�����o�ϐ�
	DirectXCommon* dxCommon = nullptr;
	Audio* audio = nullptr;
	DebugText debugText;

	//�Q�[���V�[���p
	Sprite* spriteBG = nullptr;
	Sprite* sprite1 = nullptr;

	//Audio::SoundData soundData[2];
#pragma endregion

#pragma region �֐�
public: //�����o�֐�
	//�R���X�g���N�^
	EndGame(DirectXCommon* dxCommon, Audio* audio);
	//�f�X�g���N�^
	~EndGame();
	//������
	void Init() override;
	//���t���[���X�V����
	void Update() override;
	//�`��
	void Draw() override;
#pragma endregion
};

