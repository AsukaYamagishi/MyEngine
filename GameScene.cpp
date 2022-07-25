#include "GameScene.h"
#include "ParticleManager.h"
#include <cassert>
#include <time.h>
#include "FbxInput.h"
#include "FbxDraw.h"

#include "SceneManager.h"

using namespace DirectX;


GameScene::GameScene()
{

}

GameScene::~GameScene()
{
	//safe_delete�͂����ōs��
	safe_delete(particleMan);
	safe_delete(testObject);
}

void GameScene::Init(DirectXCommon *dxCommon, KeyboardInput *input, Audio *audio)
{
#pragma region nullptr�`�F�b�N/���
	assert(dxCommon);
	assert(input);
	assert(audio);

	this->dxCommon = dxCommon;
	this->input = input;
	this->audio = audio;
#pragma endregion


	//�J�����̂�����
	camera->Init({ 0,30,130 });
	camera = Camera::GetCam();
	//camera->target = { 0 ,50 ,0 };
#pragma endregion

#pragma region �f�o�b�O�e�L�X�g�ǂݍ���
	// �f�o�b�O�e�L�X�g�p�e�N�X�`���ǂݍ���
	if (!Sprite::LoadTexture(debugTextTexNum, L"Resources/DebugText.png")) {
		assert(0);
		return;
	}
	// �f�o�b�O�e�L�X�g������
	debugText.Init(debugTextTexNum);

#pragma endregion

#pragma region Sprite�����ݒ�
	// �e�N�X�`���ǂݍ���(�P�Ԃɂ���Ƃ悭�킩���G���[�N����)
	/*if (!Sprite::LoadTexture(3, L"Resources/white1x1.png")) {
		assert(0);
		return;
	}*/
	// �w�i�X�v���C�g����
	//spriteBG = Sprite::CreateSprite(3, { 0.0f,0.0f });
#pragma endregion
	//�f�o�C�X���Z�b�g
	FbxDraw::SetDevice(dxCommon->GetDevice());
	//�J�������Z�b�g
	FbxDraw::SetCamera(camera);
	//�O���t�B�b�N�X�p�C�v���C������
	FbxDraw::CreateGraphicsPipeline();

#pragma region 3D���f��Create�E�����ݒ�
	//���f�����w�肵�ēǂݍ���
	testModel = FbxInput::GetInstance()->LoadFbxFromFile("boneTest");
	//3D�I�u�W�F�N�g�����ƃ��f���̃Z�b�g
	testObject = new FbxDraw();
	testObject->Init();
	testObject->SetModel(testModel.get());
	testObject->SetScale({ 10,10,10 });
	testObject->SetRotation({ 0,45,0 });
	testObject->SetPosition({ -50,-15,3 });
	testObject->PlayAnimation(true);

	boxModel= FbxInput::GetInstance()->LoadFbxFromFile("Box");
	boxObject = new FbxDraw();
	boxObject->Init();
	boxObject->SetModel(boxModel.get());
	boxObject->SetScale({ 0.1,0.1,0.1 });
	boxObject->SetRotation({ 0,30,0 });
	boxObject->SetPosition({ 50,-15,3 });


	stage = new Stage();
	stage->Initialize(dxCommon);
#pragma endregion


#pragma region ���y���\�[�X�����ݒ�

	//soundData[0] = audio->SoundLoadWave("Resources/musicloop.wav");
	//audio->SoundPlayWave(audio->xAudio2.Get(), soundData[0], Audio::loop);

#pragma endregion

	player = new Player();
	player->Init(dxCommon);

	

	gameEndFlag = false;
}

void GameScene::Update()
{

	stage->Update();
	
	
	testObject->Update();
	boxObject->Update();
	
	camera->SetCam(camera);
	camera->Update();

	////�V�[���؂�ւ�
	//if (input->PressKeyTrigger(DIK_0)) {
	//	SceneManager::ChangeScene(SceneManager::SceneNo::titleScene);
	//}

#pragma region �f�o�b�O�e�L�X�g�ݒ�
	
#pragma endregion

}

void GameScene::Draw()
{
	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList *cmdList = dxCommon->GetCommandList();

#pragma region �w�i�X�v���C�g�`��
	// �w�i�X�v���C�g�`��O����
	//Sprite::PreDraw(cmdList);

	// �w�i�X�v���C�g�`��
	//spriteBG->Draw();

	// �X�v���C�g�`��㏈��
	//Sprite::PostDraw();

	//�[�x�o�b�t�@�N���A
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


	//stage->Draw();
	
	
	testObject->Draw(cmdList);
	boxObject->Draw(cmdList);
	
#pragma endregion

#pragma region �O�i�X�v���C�g�`��
	// �O�i�X�v���C�g�`��O����
	Sprite::PreDraw(cmdList);
	//�O�i�X�v���C�g�`��
	//sprite->Draw();
	// �f�o�b�O�e�L�X�g�̕`��
	debugText.DrawAll(cmdList);
	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
#pragma endregion
}
