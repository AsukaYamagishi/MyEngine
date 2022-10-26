#include "EndScene.h"
#include <cassert>
#include "../Input/KeyboardInput.h"
#include "../Input/ControllerInput.h"
#include "../Manager/SceneManager.h"

using namespace DirectX;

EndScene::EndScene(DirectXCommon* dxCommon, Audio* audio)
{
	// nullptr�`�F�b�N
	assert(dxCommon);
	assert(audio);

	this->dxCommon = dxCommon;
	this->audio = audio;
}

EndScene::~EndScene()
{
	safe_delete(spriteBG);
	//safe_delete(sprite1);
}

void EndScene::Init()
{
	// �e�N�X�`���ǂݍ���(�P�Ԃɂ���Ƃ悭�킩���G���[�N����)
	if (!Sprite::LoadTexture(4, L"Resources/END.png")) {
		assert(0);
		return;
	}
	//// �w�i�X�v���C�g����
	spriteBG = Sprite::CreateSprite(4, { 0.0f,0.0f });
	
}

void EndScene::Update()
{
	//�^�C�g����ʂɖ߂�
	if (KeyboardInput::GetIns()->PressKeyTrigger(DIK_SPACE)
		|| ControllerInput::GetIns()->IsPadButtonTrigger(XBOX_INPUT_B))
	{
		SceneManager::ChangeScene(SceneManager::TITLE);
	}
}

void EndScene::Draw()
{
	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

#pragma region �w�i�X�v���C�g�`��
	// �w�i�X�v���C�g�`��O����
	Sprite::PreDraw(cmdList);
	// �w�i�X�v���C�g�`��
	spriteBG->Draw();

	/// <summary>
	/// �����ɔw�i�X�v���C�g�̕`�揈����ǉ��ł���
	/// </summary>

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

	/// <summary>
	/// ������3D�I�u�W�F�N�g�̕`�揈����ǉ��ł���
	/// </summary>

	// 3D�I�u�W�F�N�g�`��㏈��
	//CalculationObject::PostDraw();
#pragma endregion

#pragma region 3D���f���`��
// 3D���f���`��O����
	//ModelObj::PreDraw(cmdList);

	// 3D�I�u�N�W�F�N�g�̕`��
	//model->Draw();

	/// <summary>
	/// ������3D�I�u�W�F�N�g�̕`�揈����ǉ��ł���
	/// </summary>

	// 3D�I�u�W�F�N�g�`��㏈��
	//ModelObj::PostDraw();
#pragma endregion

#pragma region �O�i�X�v���C�g�`��
	// �O�i�X�v���C�g�`��O����
	Sprite::PreDraw(cmdList);

	/// <summary>
	/// �����ɑO�i�X�v���C�g�̕`�揈����ǉ��ł���

	//AL3 1-2�ǉ�
	//sprite1->Draw();
	//sprite2->Draw();
	
	/// </summary>


	// �f�o�b�O�e�L�X�g�̕`��
	//debugText.DrawAll(cmdList);

	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
#pragma endregion
}
