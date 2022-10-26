#include "TitleScene.h"
#include <cassert>
#include "../Input/KeyboardInput.h"
#include "../Input/ControllerInput.h"
#include "../Manager/SceneManager.h"

using namespace DirectX;

TitleScene::TitleScene(DirectXCommon* dxCommon, Audio* audio)
{
#pragma region nullptr�`�F�b�N/���
	assert(dxCommon);
	assert(audio);

	this->dxCommon = dxCommon;
	this->audio = audio;
#pragma endregion
}

TitleScene::~TitleScene()
{
	//safe_delete�͂����ōs��
}

void TitleScene::Init()
{


#pragma region Sprite�����ݒ�
	// �e�N�X�`���ǂݍ���(�P�Ԃɂ���Ƃ悭�킩���G���[�N����)
	if (!Sprite::LoadTexture(2, L"Resources/Title.png")) {
		assert(0);
		return;
	}
	//// �w�i�X�v���C�g����
	spriteBG = Sprite::CreateSprite(2, { 0.0f,0.0f });
#pragma endregion


#pragma region 3D���f��Create�E�����ݒ�
#pragma endregion
	
#pragma region ���y���\�[�X�����ݒ�
#pragma endregion
}

void TitleScene::Update()
{
	//����L�[�ɂ��Q�[���v���C�Ɉړ��i��قǃQ�[���Z���N�g�֕ύX�j
	if (KeyboardInput::GetIns()->PressKeyTrigger(DIK_SPACE)
		|| ControllerInput::GetIns()->IsPadButtonTrigger(XBOX_INPUT_B))
	{
		SceneManager::ChangeScene(SceneManager::GAMEPLAY);
	}
}

void TitleScene::Draw()
{
	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

#pragma region �w�i�X�v���C�g�`��
	// �w�i�X�v���C�g�`��O����
	Sprite::PreDraw(cmdList);

	// �w�i�X�v���C�g�`��
	spriteBG->Draw();

	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();

	// �[�x�o�b�t�@�N���A
	dxCommon->ClearDepthBuffer();
#pragma endregion

#pragma region 3D�I�u�W�F�N�g�`��
	// 3D�I�u�W�F�N�g�`��O����
	//CalculationObject::PreDraw(cmdList);

	// 3D�I�u�N�W�F�N�g�̕`��
	//object3d->Draw();

	// 3D�I�u�W�F�N�g�`��㏈��
	//CalculationObject::PostDraw();
#pragma endregion

#pragma region 3D���f���`��
	
#pragma endregion

#pragma region �O�i�X�v���C�g�`��
	// �O�i�X�v���C�g�`��O����
	//Object2D::PreDraw(cmdList);

	// �f�o�b�O�e�L�X�g�̕`��
	//debugText.DrawAll(cmdList);

	// �X�v���C�g�`��㏈��
	//Object2D::PostDraw();
#pragma endregion
}
