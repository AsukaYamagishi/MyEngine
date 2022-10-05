#pragma once
#include "../DirectXBase/SafeDelete.h"
#include "../DirectXBase/DirectXCommon.h"
#include <DirectXMath.h>
#include "../2d/Sprite.h"
#include "../DirectXBase/DebugText.h"
#include "../Audio/Audio.h"
#include "../Input/KeyboardInput.h"
#include "../3d/Obj/ObjDraw.h"

#include "AbstructScene.h"

using namespace Microsoft::WRL;
using namespace DirectX;

//�Q�[���V�[��
class EndScene :
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
	EndScene(DirectXCommon* dxCommon, Audio* audio);
	//�f�X�g���N�^
	~EndScene();
	//������
	void Init() override;
	//���t���[���X�V����
	void Update() override;
	//�`��
	void Draw() override;
#pragma endregion
};

